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

// global object
y::ldap::server & y::ldap::Server() {
  static y::ldap::server s;
  return s;
}

y::ldap::server::server() : _connected(false) {
  // set timeout values
  timeOut.tv_sec = 300L;
  timeOut.tv_usec = 0L;
  
  if(ldap_initialize(&_server, utils::Config().getLdapHost().c_str())) {
    y::utils::Log().add("y::ldap::server::server() : unable to initialize LDAP");
    return;
  }
  
  int version = LDAP_VERSION3;
  ldap_set_option(_server, LDAP_OPT_PROTOCOL_VERSION, &version);
  
  // log in as admin
  BerValue credentials;
  // no idea why BerValue doesn't take a const char *
  credentials.bv_val = const_cast<char*>(utils::Config().getLdapPasswd().c_str());
  credentials.bv_len = strlen(utils::Config().getLdapPasswd().c_str());
  BerValue * serverCred;
  int result = ldap_sasl_bind_s(_server, 
          utils::Config().getLdapAdminDN().c_str(), 
          NULL, &credentials, NULL, NULL, &serverCred);
  
  // check login result
  if(result != LDAP_SUCCESS) {
    y::utils::Log().add("y::ldap::server::server() : unable to bind to LDAP");
    return;
  }
  y::utils::Log().add("y::ldap::server::server() : connected to LDAP server");
  _base = utils::Config().getLdapBaseDN();
}

y::ldap::server::~server() {
  ldap_unbind_ext(_server, NULL, NULL);
}

void y::ldap::server::getData(y::ldap::dataset& rs) {
  LDAPMessage * result;
  if(ldap_search_ext_s(
          _server, 
          _base.c_str(), 
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
    return; 
  }
  
  LDAPMessage * entry;
  for (entry = ldap_first_entry(_server, result); 
       entry != NULL; 
       entry = ldap_next_entry(_server, entry)) {
    data d;
    
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

}

y::ldap::account & y::ldap::server::getAccount(const UID & id) {
  return _accounts[0];
}