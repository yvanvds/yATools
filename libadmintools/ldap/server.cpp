/* 
 * File:   server.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 12:39 PM
 */

#include "ldap/server.h"
#include <string>
#include <ldap.h>
#include <ldap_utf8.h>
#include <locale.h>
#include <libintl.h>
#include <vector>
#include "utils/log.h"
#include "utils/config.h"
#include "utils/convert.h"
#include "utils/stringFunctions.h"
#include <iostream>
#include <boost/locale.hpp>
#include "defines.h"
#include "group.h"
#include "attributes.h"


y::ldap::server::server() : _accounts(this), _groups(this), _classes(this)
  , _connected(false), _allAccountsLoaded(false)
  , _allGroupsLoaded(false), _allClassesLoaded(false) {
  setlocale(LC_MESSAGES, "");
  
  // set timeout values
  timeOut.tv_sec = 300L;
  timeOut.tv_usec = 0L;
  if(ldap_initialize(&_server, y::utils::Config().getLdapHost().ldap())) {
    y::utils::Log().add("y::ldap::server::server() : unable to initialize LDAP");
    return;
  }
  
  int version = LDAP_VERSION3;
  ldap_set_option(_server, LDAP_OPT_PROTOCOL_VERSION, &version);
  
  // log in as admin
  BerValue credentials;
  credentials.bv_val = const_cast<char*>(utils::Config().getLdapPasswd().ldap());
  credentials.bv_len = utils::Config().getLdapPasswd().size();

  BerValue * serverCred;
  int result = ldap_sasl_bind_s(_server, 
          y::utils::Config().getLdapAdminDN().ldap(), 
          NULL, &credentials, NULL, NULL, &serverCred);
  
  // check login result
  if(result != LDAP_SUCCESS) {
    y::utils::Log().add("y::ldap::server::server() : unable to bind to LDAP");
    y::utils::Log().add(ldap_err2string(result));
    return;
  }
  _base = utils::Config().getLdapBaseDN();
}

y::ldap::server::~server() {
  ldap_unbind_ext(_server, NULL, NULL);
}

bool y::ldap::server::getData(y::ldap::dataset& rs, bool isDN) {
  string base(rs.directory);
  if(!isDN) {
    if(rs.directory.size()) base += ",";
    base += _base;
  }
  LDAPMessage * result;
  //ber_int_t scope = LDAP_SCOPE_SUBTREE;
  //if(isDN) scope = LDAP_SCOPE_BASE;
  
  if(ldap_search_ext_s(
          _server, 
          base.ldap(), 
          LDAP_SCOPE_SUBTREE, 
          rs.filter.ldap(), 
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
    d.add("DN", string(dn));
    ldap_memfree(dn);
    
    
    // parse attributesldap
    char * attr;
    BerElement * ber = NULL;
    BerValue ** values = NULL;
    
    for (attr = ldap_first_attribute(_server, entry, &ber); 
         attr != NULL; 
         attr = ldap_next_attribute(_server, entry, ber)) {      
      
      if((values = ldap_get_values_len(_server, entry, attr)) != NULL) {
        for (int i = 0; values[i] != NULL; i++) {
          d.add(string(attr), string(values[i]->bv_val));
        }
        ldap_value_free_len(values);
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

y::ldap::account & y::ldap::server::getAccount(const WISA_NAME& id) {
  for(int i = 0; i < _accounts.elms(); i++) {
    if(_accounts[i].wisaName() == id) {
      return _accounts[i];
    }
  }
  
  account & a = _accounts.New();
  a.load(id);
  return a;
}

y::ldap::account & y::ldap::server::getAccount(const UID_NUMBER & id) {
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

bool y::ldap::server::hasAccount(const DN & id) {
  for(int i = 0; i < _accounts.elms(); i++) {
    if(_accounts[i].dn() == id) {
      return true;
    }
  }
  return false;
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

y::ldap::group & y::ldap::server::getGroup(const CN & cn, bool editable) {  
  for(int i = 0; i < _groups.elms(); i++) {
    if(_groups[i].cn() == cn && _groups[i].editable() == editable) {
      return _groups[i];
    }
  }
  
  group & g = _groups.New();
  g.editable(editable);
  g.load(cn);
  return g;
}

y::ldap::schoolClass & y::ldap::server::getClass(const DN& id) {
  for(int i = 0; i < _classes.elms(); i++) {
    if(_classes[i].dn() == id) {
      return _classes[i];
    }
  }
  
  schoolClass & s = _classes.New();
  s.load(id);
  return s;
}

y::ldap::schoolClass & y::ldap::server::getClass(const CN & cn) {
  for(int i = 0; i < _classes.elms(); i++) {
    if(_classes[i].cn() == cn) {
      return _classes[i];
    }
  }
  schoolClass & s = _classes.New();
  s.load(cn);
  return s;
} 

ACCOUNTS & y::ldap::server::getAccounts() {
  // don't do this twice
  if(_allAccountsLoaded) return _accounts;
  
  // keep track of accounts we've already loaded
  container<string> loaded;
  for(int i = 0; i < _accounts.elms(); i++) {
    loaded.New() = _accounts[i].uid().get();
  }
  
  dataset d(this);
  d.create("objectClass=*", "ou=people");
  for(int i = 0; i < d.elms(); i++) {
    data & temp = d.get(i);
    // if data has no uid, it's not an account
    if(temp.getValue(TYPE_UID).size() && temp.getValue(TYPE_UIDNUMBER).asInt() > 500) {
      bool found = false;
      for (int i = 0; i < loaded.elms(); i++) {
        if(loaded[i] == temp.getValue(TYPE_UID)) {
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

GROUPS & y::ldap::server::getGroups() {
  // don't do this twice
  if(_allGroupsLoaded) return _groups;
  
  // keep track of groups we've already loaded
  container<string> loaded;
  for(int i = 0; i < _groups.elms(); i++) {
    loaded.New() = _groups[i].cn().get();
  }
  
  {
    dataset d(this);
    d.create("objectClass=*", "ou=mailGroups");
    for(int i = 0; i < d.elms(); i++) {
      data & temp = d.get(i);
      bool found = false;
      for (int i = 0; i < loaded.elms(); i++) {
        if(loaded[i] == temp.getValue(TYPE_CN)) {
          found = true;
          break;
        }
      }
      if(!found) {
        group & g = _groups.New();
        g.loadData(d.get(i));
      }
    }
  }
  {
    dataset d(this);
    d.create("objectClass=*", "ou=editableMailGroups");
    for(int i = 0; i < d.elms(); i++) {
      data & temp = d.get(i);
      bool found = false;
      for (int i = 0; i < loaded.elms(); i++) {
        if(loaded[i] == temp.getValue(TYPE_CN)) {
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

CLASSES & y::ldap::server::getClasses() {
  // don't do this twice
  if(_allClassesLoaded) return _classes;
  
  // keep track of classes we've already loaded
  container<string> loaded;
  for(int i = 0; i < _classes.elms(); i++) {
    loaded.New() = _classes[i].cn().get();
  }
  
  {
    dataset d(this);
    d.create("objectClass=*", "ou=classes");
    for(int i = 0; i < d.elms(); i++) {
      data & temp = d.get(i);
      bool found = false;
      for (int i = 0; i < loaded.elms(); i++) {
        if(loaded[i] == temp.getValue(TYPE_CN)) {
          found = true;
          break;
        }
      }
      if(!found) {
        schoolClass & g = _classes.New();
        g.load(d.get(i));
        if(g.cn().get().empty()) {
          // this is not a class!
          for(int i = _classes.elms() - 1; i <= 0; i--) {
            if(_classes[i].dn() == g.dn()) {
              _classes.remove(i);
              break;
            }
          }
        }
      }
    }
  }
  
  _allClassesLoaded = true;
  
  return _classes;
}


bool y::ldap::server::auth(const DN& dn, const PASSWORD& password) { 
  // setup second connection for auth function
  if(ldap_initialize(&_authServer, y::utils::Config().getLdapHost().ldap())) {
    y::utils::Log().add("y::ldap::server::server() : unable to initialize LDAP for auth function");
    return false;
  }
  
  int version = LDAP_VERSION3;
  ldap_set_option(_authServer, LDAP_OPT_PROTOCOL_VERSION, &version);
  
  BerValue credentials;
  credentials.bv_val = const_cast<char*>(password.get().ldap());
  credentials.bv_len = strlen(password.get().ldap());
  
  BerValue * serverCred;
  int result = ldap_sasl_bind_s(_authServer, 
         dn.get().ldap(), 
          NULL, &credentials, NULL, NULL, &serverCred);
  ldap_unbind_ext(_authServer, NULL, NULL);
  
  // check login result
  if(result == LDAP_SUCCESS) {
    
    return true;
  }
  return false;
}

void y::ldap::server::printMods(LDAPMod** mods) {
  std::stringstream out;
  for(int i = 0; mods[i] != NULL; i++) {
    
    out << "mod" << i << " (";
    switch (mods[i]->mod_op) {
      case LDAP_MOD_ADD | LDAP_MOD_BVALUES: out << "ADD)" << std::endl; break;
      case LDAP_MOD_REPLACE | LDAP_MOD_BVALUES: out << "REPLACE)" << std::endl; break;
      case LDAP_MOD_DELETE | LDAP_MOD_BVALUES: out << "DELETE)" << std::endl; break;
    }
    out << "  type: " << mods[i]->mod_type << std::endl;
    for (int j = 0; mods[i]->mod_bvalues[j] != NULL; j++) {
      out << "  value: " << mods[i]->mod_bvalues[j]->bv_val << std::endl;
    }
  }
  y::utils::Log().add(string(out.str()));
}


void y::ldap::server::toLdapModify(const DN & dn, LDAPMod** mods) {
  std::ofstream out;
  out.open("/tmp/tempMods", std::ofstream::out | std::ofstream::trunc);
  out << "dn: " << dn.get().utf8() << std::endl;
  out << "changetype: modify" << std::endl;
  
  for(int i = 0; mods[i] != NULL; i++) {  
    switch (mods[i]->mod_op) {
      case LDAP_MOD_ADD | LDAP_MOD_BVALUES: out << "add: "; break;
      case LDAP_MOD_REPLACE | LDAP_MOD_BVALUES: out << "replace: "; break;
      case LDAP_MOD_DELETE | LDAP_MOD_BVALUES: out << "delete: "; break;
    }
    out << mods[i]->mod_type << std::endl;
    for (int j = 0; mods[i]->mod_bvalues[j] != NULL; j++) {
      out << mods[i]->mod_type << ": " << mods[i]->mod_bvalues[j]->bv_val << std::endl;
    }
    out << "-" << std::endl;
  }
  out.close();
  string command("ldapmodify -a -D ");
  command += y::utils::Config().getLdapAdminDN();
  command += " -w ";
  command += y::utils::Config().getLdapPasswd();
  command += " -f /tmp/tempMods";
  command.execute();
}

LDAPMod ** y::ldap::server::createMods(dataset& values) {
  LDAPMod ** mods = new LDAPMod*[values.elms() + 1];
  mods[values.elms()] = NULL;
  
  for(int i = 0; i < values.elms(); i++) {
    mods[i] = new LDAPMod;
    data & d = values.get(i);
    
    switch (d.getType()) {
      case NEW: mods[i]->mod_op = 0 | LDAP_MOD_BVALUES; break;
      case ADD: mods[i]->mod_op = LDAP_MOD_ADD | LDAP_MOD_BVALUES; break;
      case MODIFY: mods[i]->mod_op = LDAP_MOD_REPLACE | LDAP_MOD_BVALUES; break;
      case DELETE: mods[i]->mod_op = LDAP_MOD_DELETE | LDAP_MOD_BVALUES; break;
      default: assert(false);
    }
    mods[i]->mod_type = NULL;
    
    std::string type(d.getValue("type").ldap());
    mods[i]->mod_type = new char[type.size() + 1];
    std::copy(type.begin(), type.end(), mods[i]->mod_type);
    mods[i]->mod_type[type.size()] = '\0';
    
    mods[i]->mod_bvalues = new berval*[d.elms("values") + 1];
    for(int j = 0; j < d.elms("values"); j++) {
      std::string value(d.getValue("values", j).ldap());
      int size = value.size();
      mods[i]->mod_bvalues[j] = new berval; 
      mods[i]->mod_bvalues[j]->bv_val = new char[size + 1];
      std::copy(value.begin(), value.end(), mods[i]->mod_bvalues[j]->bv_val);
      mods[i]->mod_bvalues[j]->bv_val[size] = '\0';
      mods[i]->mod_bvalues[j]->bv_len = size;
    }
    
    mods[i]->mod_bvalues[d.elms("values")] = NULL;
  }
  
  return mods;
}

void y::ldap::server::releaseMods(LDAPMod** mods) {
  for(int i = 0; mods[i] != nullptr; i++) {
    delete[] mods[i]->mod_type;
    for(int j = 0; mods[i]->mod_bvalues[j] != nullptr; j++) {
      delete[] mods[i]->mod_bvalues[j]->bv_val;
      delete mods[i]->mod_bvalues[j];
    }
    delete[] mods[i]->mod_bvalues;
    delete mods[i];
  }
  delete[] mods;
}

void y::ldap::server::modify(const DN & dn, dataset & values) {
  LDAPMod ** mods = createMods(values);

  if(int result = ldap_modify_ext_s(_server, dn.get().ldap(), mods, NULL, NULL) != LDAP_SUCCESS) {
    if(result == LDAP_OPERATIONS_ERROR) {
      y::utils::Log().add("Possible utf8 mismatch detected. Trying again with ldapmodify.");
      toLdapModify(dn, mods);
    } else {
      string message("Error on DN: " + dn.get());
      y::utils::Log().add(message);
      message = "y::ldap::server::modify() : ";
      message += ldap_err2string(result);
      y::utils::Log().add(message);
      printMods(mods);
    }
  }
  
  releaseMods(mods);
}
 
void y::ldap::server::add(const DN& dn, dataset& values) {
  LDAPMod ** mods = createMods(values);

  if(int result = ldap_add_ext_s(_server, dn.get().ldap(), mods, NULL, NULL) != LDAP_SUCCESS) {
    y::utils::Log().add(string("Error on DN: " + dn.get()));
    string message("y::ldap::server::add() : ");
    message += ldap_err2string(result);
    y::utils::Log().add(message);
    printMods(mods);
  }
  
  // release memory
  releaseMods(mods);
}

void y::ldap::server::remove(const DN& dn) {
  if(int result = ldap_delete_ext_s(_server, dn.get().ldap(), NULL, NULL) != LDAP_SUCCESS) {
    string message("y::ldap::server::removeEntry() : ");
    message += ldap_err2string(result);
    y::utils::Log().add(message);
  }
}

int y::ldap::server::findAccounts(const string& query, std::vector<UID_NUMBER> & results) {
  dataset rs(this);
  rs.filter = query;
  rs.directory = "ou=people";
  
  if(getData(rs)) {
    for(int i = 0; i < rs.elms(); i++) {
      data & d = rs.get(i);
      bool found = false;
      
      // search if this account is already loaded in memory
      for(int j = 0; j < _accounts.elms(); j++) {
        if(d.getValue("uidNumber").asInt() == _accounts[j].uidNumber().get()) {
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

UID y::ldap::server::createUID(const CN & cn, const SN & sn) {
  boost::locale::generator gen;
  std::locale loc = gen("en_US.UTF-8");
  std::locale::global(loc);
  
  // To lowercase
  string first = cn.get();
  string last  = sn.get();
  
  first.toLower().replaceUTF8().keeponlyChars();
  last.toLower().replaceUTF8().keeponlyChars();
  
  int pos = 0;
  if(last.utf8().find("de"    ) == 0) pos = 2;
  if(last.utf8().find("ver"   ) == 0) pos = 3;
  if(last.utf8().find("van"   ) == 0) pos = 3;
  if(last.utf8().find("vande" ) == 0) pos = 5;
  if(last.utf8().find("vander") == 0) pos = 6;
  
  string id(last.utf8().substr(pos, 5));
  id += first[0];
  int counter = 0;
  std::vector<UID_NUMBER> result;
  string test_id(id);
  
  while (true) {
    string query("uid=" + test_id);
    
    if(!findAccounts(query, result)) {     
      return UID(test_id);
    }
    
    counter++;
    test_id = id + counter;
    result.clear();
  }
}

MAIL y::ldap::server::createMail(const CN & cn, const SN & sn) {
  boost::locale::generator gen;
  std::locale loc = gen("en_US.UTF-8");
  std::locale::global(loc);
  
  // To lowercase
  string first(cn.get());
  string last (sn.get());
  
  first.toLower().replaceUTF8().keeponlyChars();
  last.toLower().replaceUTF8().keeponlyChars();
  
  string mail = first;
  mail += "."; mail += last;
  mail += "@"; mail += y::utils::Config().getDomain();
  
  string query;
  query = "(mail="; query += mail; query += ")";
  std::vector<UID_NUMBER> result;
  int counter = 0;
  
  while(findAccounts(query, result) > 0) {
    result.clear();
    counter++;
    mail = first;
    mail += "."; mail += last; mail += counter;
    mail += "@"; mail += y::utils::Config().getDomain();   
    query = "(mail="; query += mail; query += ")";
  }
  
  return MAIL(mail);
}

bool y::ldap::server::commitChanges() {
  bool result = false;
  
  for(int i = _groups.elms()-1; i >=0 ; i--) {
    if(_groups[i].save()) result = true;
    if(_groups[i].flaggedForRemoval()) {
      _groups.remove(i);
    }
  }
 
  for(int i = _accounts.elms() - 1; i >= 0; i--) {
    if(_accounts[i].save()) result = true;
    if(_accounts[i].flaggedForRemoval()) {
      _accounts.remove(i);
    }
  }
  
  for(int i = _classes.elms() -1; i >= 0 ; i--) {
    if(_classes[i].save()) result = true;
    if(_classes[i].flaggedForRemoval()) {
      _classes.remove(i);
    }
  }
 
  return result;
}

void y::ldap::server::clear() {
  clearAccounts();
  clearGroups();
  clearClasses();
}

void y::ldap::server::clearAccounts() {
  _accounts.clear();
  _allAccountsLoaded = false;
}

void y::ldap::server::clearGroups() {
  _groups.clear();
  _allGroupsLoaded = false;
}

void y::ldap::server::clearClasses() {
  _classes.clear();
  _allClassesLoaded = false;
}

