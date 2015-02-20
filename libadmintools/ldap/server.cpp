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
#include "utils/convert.h"
#include "utils/stringFunctions.h"
#include <iostream>
#include <boost/locale.hpp>

// global object
y::ldap::server & y::ldap::Server() {
  static y::ldap::server s;
  return s;
}

y::ldap::server::server() : _connected(false), _allAccountsLoaded(false), _allGroupsLoaded(false) {
  // set timeout values
  timeOut.tv_sec = 300L;
  timeOut.tv_usec = 0L;
  if(ldap_initialize(&_server, str8(y::utils::Config().getLdapHost()).c_str())) {
    y::utils::Log().add(L"y::ldap::server::server() : unable to initialize LDAP");
    return;
  }
  
  int version = LDAP_VERSION3;
  ldap_set_option(_server, LDAP_OPT_PROTOCOL_VERSION, &version);
  
  // log in as admin
  BerValue credentials;
  //TODO for some reason this goes wrong if i delete the next two lines???
  std::string test(str8(utils::Config().getLdapPasswd()));
  std::string test2(test.c_str());
  // BerValue doesn't take a const char *
  credentials.bv_val = const_cast<char*>(test.c_str());
  credentials.bv_len = strlen(str8(utils::Config().getLdapPasswd()).c_str());
  
  BerValue * serverCred;
  int result = ldap_sasl_bind_s(_server, 
          str8(y::utils::Config().getLdapAdminDN()).c_str(), 
          NULL, &credentials, NULL, NULL, &serverCred);
  
  // check login result
  if(result != LDAP_SUCCESS) {
    y::utils::Log().add(L"y::ldap::server::server() : unable to bind to LDAP");
    return;
  }
  //y::utils::Log().add("y::ldap::server::server() : connected to LDAP server");
  _base = str8(utils::Config().getLdapBaseDN());
  

}

y::ldap::server::~server() {
  ldap_unbind_ext(_server, NULL, NULL);
}

bool y::ldap::server::getData(y::ldap::dataset& rs, bool isDN) {
  std::string base(str8(rs.directory));
  if(!isDN) {
    if(rs.directory.size()) base.append(",");
    base.append(_base);
  }
  LDAPMessage * result;
  //ber_int_t scope = LDAP_SCOPE_SUBTREE;
  //if(isDN) scope = LDAP_SCOPE_BASE;
  
  if(ldap_search_ext_s(
          _server, 
          base.c_str(), 
          LDAP_SCOPE_SUBTREE, 
          str8(rs.filter).c_str(), 
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
    d.add(L"DN", strW(dn));
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
          d.add(strW(attr), strW(values[i]->bv_val));
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
  
  for(int i = 0; i < _groups.elms(); i++) {
    if(_groups[i].dn() == id) {
      return _groups[i];
    }
  }
  
  group & g = _groups.New();
  g.load(id);
  return g;
}

y::ldap::group & y::ldap::server::getGroup(const CN& id, bool editable) {  
  for(int i = 0; i < _groups.elms(); i++) {
    if(_groups[i].cn() == id && _groups[i].editable() == editable) {
      return _groups[i];
    }
  }
  
  group & g = _groups.New();
  g.editable(editable);
  g.load(id);
  return g;
}

container<y::ldap::account> & y::ldap::server::getAccounts() {
  // don't do this twice
  if(_allAccountsLoaded) return _accounts;
  
  // keep track of accounts we've already loaded
  container<std::wstring> loaded;
  for(int i = 0; i < _accounts.elms(); i++) {
    loaded.New() = _accounts[i].uid()();
  }
  
  dataset d;
  d.create(L"objectClass=*", L"ou=people");
  for(int i = 0; i < d.elms(); i++) {
    data & temp = d.get(i);
    // if data has no uid, it's not an account
    if(temp.getValue(TYPE_UID).size() && std::stoi(temp.getValue(TYPE_UID_NUMBER)) > 500) {
      bool found = false;
      for (int i = 0; i < loaded.elms(); i++) {
        if(loaded[i].compare(temp.getValue(TYPE_UID)) == 0) {
          found = true;
          break;
        }
      }
      if(!found) {
        account & a = _accounts.New();
        a.load(temp);
      }
    }
  }
  _allAccountsLoaded = true;
  
  return _accounts;
}

container<y::ldap::group> & y::ldap::server::getGroups() {
  // don't do this twice
  if(_allGroupsLoaded) return _groups;
  
  // keep track of groups we've already loaded
  container<std::wstring> loaded;
  for(int i = 0; i < _groups.elms(); i++) {
    loaded.New() = _groups[i].cn()();
  }
  
  {
    dataset d;
    d.create(L"objectClass=*", L"ou=mailGroups");
    for(int i = 0; i < d.elms(); i++) {
      data & temp = d.get(i);
      bool found = false;
      for (int i = 0; i < loaded.elms(); i++) {
        if(loaded[i].compare(temp.getValue(TYPE_CN)) == 0) {
          found = true;
          break;
        }
      }
      if(!found) {
        group & g = _groups.New();
        g.load(d.get(i));
      }
    }
  }
  {
    dataset d;
    d.create(L"objectClass=*", L"ou=editableMailGroups");
    for(int i = 0; i < d.elms(); i++) {
      data & temp = d.get(i);
      bool found = false;
      for (int i = 0; i < loaded.elms(); i++) {
        if(loaded[i].compare(temp.getValue(TYPE_CN)) == 0) {
          found = true;
          break;
        }
      }
      if(!found) {
        group & g = _groups.New();
        g.load(d.get(i));
      }
    }
  }
  _allGroupsLoaded = true;
  
  return _groups;
}

bool y::ldap::server::auth(const DN& dn, const PASSWORD& password) { 
  // setup second connection for auth function
  if(ldap_initialize(&_authServer, str8(y::utils::Config().getLdapHost()).c_str())) {
    y::utils::Log().add(L"y::ldap::server::server() : unable to initialize LDAP for auth function");
    return false;
  }
  
  int version = LDAP_VERSION3;
  ldap_set_option(_authServer, LDAP_OPT_PROTOCOL_VERSION, &version);
  
  BerValue credentials;
  //TODO for some reason this goes wrong if i delete the next two lines???
  std::string test(str8(password()));
  std::string test2(test.c_str());
  // BerValue doesn't take a const char *
  credentials.bv_val = const_cast<char*>(str8(password()).c_str());
  credentials.bv_len = strlen(str8(password()).c_str());
  
  BerValue * serverCred;
  int result = ldap_sasl_bind_s(_authServer, 
          str8(dn()).c_str(), 
          NULL, &credentials, NULL, NULL, &serverCred);
  ldap_unbind_ext(_authServer, NULL, NULL);
  
  // check login result
  if(result == LDAP_SUCCESS) {
    
    return true;
  }
  return false;
}

void y::ldap::server::printMods(LDAPMod** mods) {
  for(int i = 0; mods[i] != NULL; i++) {
    std::cout << "mod" << i << " (";
    switch (mods[i]->mod_op) {
      case LDAP_MOD_ADD: std::cout << "ADD)" << std::endl; break;
      case LDAP_MOD_REPLACE: std::cout << "REPACE)" << std::endl; break;
      case LDAP_MOD_DELETE: std::cout << "DELETE)" << std::endl; break;
    }
    std::cout << "  type: " << mods[i]->mod_type << std::endl;
    for (int j = 0; mods[i]->mod_vals.modv_strvals[j] != NULL; j++) {
      std::cout << "  value: " << mods[i]->mod_vals.modv_strvals[j] << std::endl;
    }
  }
}

LDAPMod ** y::ldap::server::createMods(dataset& values) {
  LDAPMod ** mods = new LDAPMod*[values.elms() + 1];
  mods[values.elms()] = NULL;
  
  for(int i = 0; i < values.elms(); i++) {
    mods[i] = new LDAPMod;
    data & d = values.get(i);
    
    switch (d.getType()) {
      case NEW: mods[i]->mod_op = 0; break;
      case ADD: mods[i]->mod_op = LDAP_MOD_ADD; break;
      case MODIFY: mods[i]->mod_op = LDAP_MOD_REPLACE; break;
      case DELETE: mods[i]->mod_op = LDAP_MOD_DELETE; break;
      default: assert(false);
    }
    
    std::string type = str8(d.getValue(L"type"));
    mods[i]->mod_type = new char[type.size() + 1];
    std::copy(type.begin(), type.end(), mods[i]->mod_type);
    mods[i]->mod_type[type.size()] = '\0';
    
    mods[i]->mod_vals.modv_strvals = new char*[d.elms(L"values") + 1];
    for(int j = 0; j < d.elms(L"values"); j++) {
      std::string value = str8(d.getValue(L"values", j));
      mods[i]->mod_vals.modv_strvals[j] = new char[value.size() + 1];
      std::copy(value.begin(), value.end(), mods[i]->mod_vals.modv_strvals[j]);
      mods[i]->mod_vals.modv_strvals[j][value.size()] = '\0';
    }
    
    mods[i]->mod_vals.modv_strvals[d.elms(L"values")] = NULL;
  }
  
  return mods;
}

void y::ldap::server::releaseMods(LDAPMod** mods) {
    for(int i = 0; mods[i] != nullptr; i++) {
    delete[] mods[i]->mod_type;
    for(int j = 0; mods[i]->mod_vals.modv_strvals[j] != nullptr; j++) {
      delete[] mods[i]->mod_vals.modv_strvals[j];
    }
    delete[] mods[i]->mod_vals.modv_strvals;
    delete mods[i];
  }
  delete[] mods;
}

void y::ldap::server::modify(const DN & dn, dataset & values) {
  LDAPMod ** mods = createMods(values);

  if(int result = ldap_modify_ext_s(_server, str8(dn()).c_str(), mods, NULL, NULL) != LDAP_SUCCESS) {
    std::wstring message;
    message.append(L"y::ldap::server::modify() : ");
    message.append(strW(ldap_err2string(result)));
    y::utils::Log().add(message);
  }
  
  releaseMods(mods);
}
 
void y::ldap::server::add(const DN& dn, dataset& values) {
  LDAPMod ** mods = createMods(values);
  //std::cout << std::endl;
  //std::cout << dn() << std::endl;
  //printMods(mods);

  if(int result = ldap_add_ext_s(_server, str8(dn()).c_str(), mods, NULL, NULL) != LDAP_SUCCESS) {
    std::wstring message;
    message.append(L"y::ldap::server::modify() : ");
    message.append(strW(ldap_err2string(result)));
    y::utils::Log().add(message);
  }
  
  // release memory
  releaseMods(mods);
}

void y::ldap::server::remove(const DN& dn) {
  if(int result = ldap_delete_ext_s(_server, str8(dn()).c_str(), NULL, NULL) != LDAP_SUCCESS) {
    std::wstring message;
    message.append(L"y::ldap::server::removeEntry() : ");
    message.append(strW(ldap_err2string(result)));
    y::utils::Log().add(message);
  }
}

int y::ldap::server::findAccounts(const std::wstring& query, std::vector<UID_NUMBER> & results) {
  dataset rs;
  rs.filter = query;
  rs.directory = L"ou=people";
  
  if(getData(rs)) {
    for(int i = 0; i < rs.elms(); i++) {
      data & d = rs.get(i);
      bool found = false;
      
      // search if this account is already loaded in memory
      for(int j = 0; j < _accounts.elms(); j++) {
        if(std::stoi(str8(d.getValue(L"uidNumber"))) == _accounts[j].uidNumber()()) {
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

y::ldap::UID y::ldap::server::createUID(const std::wstring& cn, const std::wstring& sn) {
  boost::locale::generator gen;
  std::locale loc = gen("en_US.UTF-8");
  std::locale::global(loc);
  
  //std::setlocale(LC_CTYPE, "en_US.UTF-8");
  std::wstring first(boost::locale::to_lower(cn));
  std::wstring last(boost::locale::to_lower(sn));
  
  y::utils::keepOnlyChars(first);
  y::utils::keepOnlyChars(last);
  
  int pos = 0;
  if(last.find(L"de"    ) == 0) pos = 2;
  if(last.find(L"ver"   ) == 0) pos = 3;
  if(last.find(L"van"   ) == 0) pos = 3;
  if(last.find(L"vande" ) == 0) pos = 5;
  if(last.find(L"vander") == 0) pos = 6;
  
  std::wstring id = last.substr(pos, 5);
  id += first.substr(0, 1);
  int counter = 0;
  std::vector<UID_NUMBER> result;
  std::wstring test_id(id);
  
  while (true) {
    std::wstring query;
    query += L"uid=";
    query += test_id;
    
    if(!findAccounts(query, result)) {     
      return UID(test_id);
    }
    
    counter++;
    test_id = id;
    test_id.append(std::to_wstring(counter));
    result.clear();
  }
}

y::ldap::MAIL y::ldap::server::createMail(const std::wstring& cn, const std::wstring& sn) {
  boost::locale::generator gen;
  std::locale loc = gen("en_US.UTF-8");
  std::locale::global(loc);
  
  std::wstring first(boost::locale::to_lower(cn));
  std::wstring last(boost::locale::to_lower(sn));
  
  y::utils::keepOnlyChars(first);
  y::utils::keepOnlyChars(last);
  
  std::wstring mail = first;
  mail += L"."; mail += last;
  mail += L"@"; mail += y::utils::Config().getDomain();
  
  std::wstring query;
  query = L"(mail="; query += mail; query += L")";
  std::vector<UID_NUMBER> result;
  int counter = 0;
  
  while(findAccounts(query, result) > 0) {
    result.clear();
    counter++;
    mail = first;
    mail += L"."; mail += last; mail += std::to_wstring(counter);
    mail += L"@"; mail += y::utils::Config().getDomain();   
    query = L"(mail="; query += mail; query += L")";
  }
  
  return MAIL(mail);
}

bool y::ldap::server::commitChanges() {
  bool result = false;
  for(int i = 0; i < _accounts.elms(); i++) {
    if(_accounts[i].save()) result = true;
  }
  
  for(int i = 0; i < _groups.elms(); i++) {
    if(_groups[i].save()) result = true;
  }
  
  return result;
}

void y::ldap::server::clear() {
  _accounts.clear();
  _groups.clear();
  _allAccountsLoaded = false;
  _allGroupsLoaded = false;
}

