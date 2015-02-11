/* 
 * File:   server.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 12:39 PM
 */

#include "ldap/server.h"
#include <string>
#include <ldap.h>
#include <vector>
#include "utils/log.h"
#include "utils/config.h"
#include <iostream>

// global object
y::ldap::server & y::ldap::Server() {
  static y::ldap::server s;
  return s;
}

y::ldap::server::server() : _connected(false), _ldapMode(LDAP_MODE_NONE) {
  // set timeout values
  timeOut.tv_sec = 300L;
  timeOut.tv_usec = 0L;
  if(ldap_initialize(&_server, y::utils::Config().getLdapHost().c_str())) {
    y::utils::Log().add("y::ldap::server::server() : unable to initialize LDAP");
    return;
  }
  
  int version = LDAP_VERSION3;
  ldap_set_option(_server, LDAP_OPT_PROTOCOL_VERSION, &version);
  
  // log in as admin
  BerValue credentials;
  // BerValue doesn't take a const char *
  credentials.bv_val = const_cast<char*>(utils::Config().getLdapPasswd().c_str());
  credentials.bv_len = strlen(utils::Config().getLdapPasswd().c_str());
  
  BerValue * serverCred;
  int result = ldap_sasl_bind_s(_server, 
          y::utils::Config().getLdapAdminDN().c_str(), 
          NULL, &credentials, NULL, NULL, &serverCred);
  
  // check login result
  if(result != LDAP_SUCCESS) {
    y::utils::Log().add("y::ldap::server::server() : unable to bind to LDAP");
    return;
  }
  //y::utils::Log().add("y::ldap::server::server() : connected to LDAP server");
  _base = utils::Config().getLdapBaseDN();
  

}

y::ldap::server::~server() {
  ldap_unbind_ext(_server, NULL, NULL);
}

bool y::ldap::server::getData(y::ldap::dataset& rs) {
  std::string base(rs.directory);
  if(rs.directory.size()) base.append(",");
  base.append(_base);
  LDAPMessage * result;
  if(ldap_search_ext_s(
          _server, 
          base.c_str(), 
          LDAP_SCOPE_SUBTREE, 
          rs.filter.c_str(), 
          NULL, 
          0, 
          NULL, 
          NULL, 
          &timeOut, 
          LDAP_NO_LIMIT, 
          &result) != LDAP_SUCCESS) {
    // no results
    ldap_msgfree(result);
    return false; 
  }
  
  
  if(ldap_count_entries(_server, result) == 0) {
    ldap_msgfree(result);
    return false;
  }
  
  LDAPMessage * entry;
  
  for (entry = ldap_first_entry(_server, result); 
       entry != NULL; 
       entry = ldap_next_entry(_server, entry)) {
    data & d = rs.New(data_type::RESULT);
    
    // add DN
    char * dn = ldap_get_dn(_server, entry);
    d.add("DN", dn);
    ldap_memfree(dn);
    
    // parse attributes
    char * attr;
    BerElement * ber = NULL;
    BerValue ** values = NULL;
    
    for (attr = ldap_first_attribute(_server, entry, &ber); 
         attr != NULL; 
         attr = ldap_next_attribute(_server, entry, ber)) {      
      
      if((values = ldap_get_values_len(_server, entry, attr)) != NULL) {
        for (int i = 0; values[i] != NULL; i++) {
          d.add(attr, values[i]->bv_val);
        }
      }
      
      ldap_memfree(attr);
    }
    ber_free(ber, 0);
    
  } 
  ldap_msgfree(result);
  return true;
}

y::ldap::account & y::ldap::server::getAccount(const UID & id) {
  // make sure we're in single mode
  if(_ldapMode == LDAP_MODE_NONE) _ldapMode = LDAP_MODE_SINGLE;
  assert(_ldapMode == LDAP_MODE_SINGLE);
  
  // first check if already in memory
  for(int i = 0; i < _accounts.elms(); i++) {
    if(_accounts[i].uid() == id) {
      return _accounts[i];
    }
  }
  
  account & a = _accounts.New();
  a.load(id);
  return a;
}

y::ldap::account & y::ldap::server::getAccount(UID_NUMBER id) {
  // make sure we're in single mode
  if(_ldapMode == LDAP_MODE_NONE) _ldapMode = LDAP_MODE_SINGLE;
  assert(_ldapMode == LDAP_MODE_SINGLE);
  
  // first check if already in memory
  for(int i = 0; i < _accounts.elms(); i++) {
    if(_accounts[i].uidNumber() == id) {
      return _accounts[i];
    }
  }
  
  account & a = _accounts.New();
  a.load(id);
  return a;
}

y::ldap::account & y::ldap::server::getAccount(const DN & id) {
  // make sure we're in single mode
  if(_ldapMode == LDAP_MODE_NONE) _ldapMode = LDAP_MODE_SINGLE;
  assert(_ldapMode == LDAP_MODE_SINGLE);
  
  // first check if already in memory
  for(int i = 0; i < _accounts.elms(); i++) {
    if(_accounts[i].dn() == id) {
      return _accounts[i];
    }
  }
  
  account & a = _accounts.New();
  a.load(id);
  return a;
}

y::ldap::group & y::ldap::server::getGroup(const DN& id) {
  // make sure we're in single mode
  if(_ldapMode == LDAP_MODE_NONE) _ldapMode = LDAP_MODE_SINGLE;
  assert(_ldapMode == LDAP_MODE_SINGLE);
  
  for(int i = 0; i < _groups.elms(); i++) {
    if(_groups[i].dn() == id) {
      return _groups[i];
    }
  }
  
  group & g = _groups.New();
  g.load(id);
  return g;
}

y::ldap::group & y::ldap::server::getGroup(const CN& id) {
  // make sure we're in single mode
  if(_ldapMode == LDAP_MODE_NONE) _ldapMode = LDAP_MODE_SINGLE;
  assert(_ldapMode == LDAP_MODE_SINGLE);
  
  for(int i = 0; i < _groups.elms(); i++) {
    if(_groups[i].cn() == id) {
      return _groups[i];
    }
  }
  
  group & g = _groups.New();
  g.load(id);
  return g;
}

container<y::ldap::account> & y::ldap::server::getAccounts() {
  // make sure we're in full mode
  if(_ldapMode == LDAP_MODE_NONE) _ldapMode = LDAP_MODE_FULL;
  assert(_ldapMode == LDAP_MODE_FULL);
  
  // make sure the accounts are not loaded yet
  assert(_accounts.empty());
  
  dataset d;
  d.create("objectClass=*", "ou=people");
  for(int i = 0; i < d.elms(); i++) {
    account & a = _accounts.New();
    a.load(d.get(i));
  }
  
  return _accounts;
}

container<y::ldap::group> & y::ldap::server::getGroups() {
  // make sure we're in full mode
  if(_ldapMode == LDAP_MODE_NONE) _ldapMode = LDAP_MODE_FULL;
  assert(_ldapMode == LDAP_MODE_FULL);
  
  // make sure the accounts are not loaded yet
  assert(_groups.empty());
  
  {
    dataset d;
    d.create("objectClass=*", "ou=mailGroups");
    for(int i = 0; i < d.elms(); i++) {
      group & g = _groups.New();
      g.load(d.get(i));
    }
  }
  {
    dataset d;
    d.create("objectClass=*", "ou=editableMailGroups");
    for(int i = 0; i < d.elms(); i++) {
      group & g = _groups.New();
      g.load(d.get(i));
    }
  }
  
  return _groups;
}

bool y::ldap::server::auth(const DN& dn, const PASSWORD& password) { 
  // setup second connection for auth function
  if(ldap_initialize(&_authServer, y::utils::Config().getLdapHost().c_str())) {
    y::utils::Log().add("y::ldap::server::server() : unable to initialize LDAP for auth function");
    return false;
  }
  
  int version = LDAP_VERSION3;
  ldap_set_option(_authServer, LDAP_OPT_PROTOCOL_VERSION, &version);
  
  BerValue credentials;
  // BerValue doesn't take a const char *
  credentials.bv_val = const_cast<char*>(password().c_str());
  credentials.bv_len = strlen(password().c_str());
  
  BerValue * serverCred;
  int result = ldap_sasl_bind_s(_authServer, 
          dn().c_str(), 
          NULL, &credentials, NULL, NULL, &serverCred);
  ldap_unbind_ext(_authServer, NULL, NULL);
  
  // check login result
  if(result == LDAP_SUCCESS) {
    
    return true;
  }
  return false;
}

void y::ldap::server::setData(const DN & dn, dataset & values) {
  LDAPMod ** mods = new LDAPMod*[values.elms() + 1];
  mods[values.elms()] = NULL;
  
  for(int i = 0; i < values.elms(); i++) {
    mods[i] = new LDAPMod;
    data & d = values.get(i);
    
    switch (d.getType()) {
      case ADD: mods[i]->mod_op = LDAP_MOD_ADD; break;
      case MODIFY: mods[i]->mod_op = LDAP_MOD_REPLACE; break;
      case DELETE: mods[i]->mod_op = LDAP_MOD_DELETE; break;
      default: assert(false);
    }
    
    std::string type = d.getValue("type");
    mods[i]->mod_type = new char[type.size() + 1];
    std::copy(type.begin(), type.end(), mods[i]->mod_type);
    mods[i]->mod_type[type.size()] = '\0';
    
    mods[i]->mod_vals.modv_strvals = new char*[d.elms("values") + 1];
    for(int j = 0; j < d.elms("values"); j++) {
      std::string value = d.getValue("values", j);
      mods[i]->mod_vals.modv_strvals[j] = new char[value.size() + 1];
      std::copy(value.begin(), value.end(), mods[i]->mod_vals.modv_strvals[j]);
      mods[i]->mod_vals.modv_strvals[j][value.size()] = '\0';
    }
    
    mods[i]->mod_vals.modv_strvals[d.elms("values")] = NULL;
  }
  
  if(int result = ldap_modify_ext_s(_server, dn().c_str(), mods, NULL, NULL) != LDAP_SUCCESS) {
    std::string message;
    message.append("y::ldap::server::setData() : ");
    message.append(ldap_err2string(result));
    y::utils::Log().add(message);
  }
  
  // release memory
  for(int i = 0; i < values.elms(); i++) {
    delete[] mods[i]->mod_type;
    for(int j = 0; j < values.get(i).elms("values"); j++) {
      delete[] mods[i]->mod_vals.modv_strvals[j];
    }
    delete[] mods[i]->mod_vals.modv_strvals;
    delete mods[i];
  }
  delete[] mods;
}

int y::ldap::server::findAccounts(const std::string& query, std::vector<UID_NUMBER> & results) {
  dataset rs;
  rs.filter = query;
  rs.directory = "ou=people";
  
  if(getData(rs)) {
    for(int i = 0; i < rs.elms(); i++) {
      data & d = rs.get(i);
      bool found = false;
      
      // search if this account is already loaded in memory
      for(int j = 0; j < _accounts.elms(); j++) {
        if(std::stoi(d.getValue("uidNumber")) == _accounts[j].uidNumber()()) {
          found = true;
          results.push_back(_accounts[j].uidNumber());
          break;
        }
      }
      
      if(!found) {
        account & a = _accounts.New();
        a.load(d);
        results.push_back(a.uidNumber());
      }
      
    }
  }
  
  return results.size();
}

y::ldap::UID y::ldap::server::createUID(const std::string& cn, const std::string& sn) {
  int pos = 0;
  if(sn.find("de"    ) == 0) pos = 2;
  if(sn.find("ver"   ) == 0) pos = 3;
  if(sn.find("van"   ) == 0) pos = 3;
  if(sn.find("vande" ) == 0) pos = 5;
  if(sn.find("vander") == 0) pos = 6;
  
  std::string id = sn.substr(pos, 5);
  id += cn.substr(0, 1);
  int counter = 0;
  std::vector<UID_NUMBER> result;
  std::string test_id(id);
  
  while (true) {
    std::string query;
    query += "uid=";
    query += test_id;
    
    if(!findAccounts(query, result)) {     
      return UID(test_id);
    }
    
    counter++;
    test_id = id;
    test_id.append(std::to_string(counter));
    result.clear();
  }
}

y::ldap::MAIL y::ldap::server::createMail(const std::string& cn, const std::string& sn) {
  std::string mail = cn;
  mail += "."; mail += sn;
  mail += "@"; mail += y::utils::Config().getDomain();
  
  std::string query;
  query = "(mail="; query += mail; query += ")";
  std::vector<UID_NUMBER> result;
  int counter = 0;
  
  while(findAccounts(query, result) > 0) {
    result.clear();
    counter++;
    mail = cn;
    mail += "."; mail += sn; mail += std::to_string(counter);
    mail += "@"; mail += y::utils::Config().getDomain();   
    query = "(mail="; query += mail; query += ")";
  }
  
  return MAIL(mail);
}

bool y::ldap::server::commitChanges() {
  bool result = false;
  for(int i = 0; i < _accounts.elms(); i++) {
    if(_accounts[i].save()) result = true;
  }
  
  return result;
}