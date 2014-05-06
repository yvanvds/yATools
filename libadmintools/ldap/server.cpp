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

// global object
ldp::server & ldp::Server() {
  static ldp::server s;
  return s;
}

ldp::server::server() : _connected(false) {
  if(ldap_initialize(&_server, "ldap://sauron")) {
    Log().add("ldp::server::server() : unable to initialize LDAP");
    return;
  }
  int version = LDAP_VERSION3;
  ldap_set_option(_server, LDAP_OPT_PROTOCOL_VERSION, &version);
  berval credentials;
  credentials.bv_val = "***REMOVED***";
  credentials.bv_len = strlen("***REMOVED***");
  berval * serverCred;
  int result = ldap_sasl_bind_s(_server, 
          "cn=admin,dc=sanctamaria-aarschot.dc=be", 
          NULL, &credentials, NULL, NULL, &serverCred);
  
  if(result != LDAP_SUCCESS) {
    Log().add("ldp::server::server() : unable to bind to LDAP");
    return;
  }
  Log().add("ldp::server::server() : connected to LDAP server");
  _base = "dc=sanctamaria-aarschot,dc=be";
}

ldp::server::~server() {
  ldap_unbind_ext(_server, NULL, NULL);
}

void ldp::server::getData(ldp::dataset& rs) {
  LDAPMessage * result;
  if(ldap_search_ext_s(_server, _base, LDAP_SCOPE_SUBTREE, rs.filter, NULL, 0, &result) != LDAP_SUCCESS) {
    return; // no results
  }
  
  LDAPMessage * entry;
  for (entry = ldap_first_entry(_server, result); entry != NULL; entry = ldap_next_entry(_server, entry)) {
    data d;
    
    // add DN
    char * dn = ldap_get_dn(_server, entry);
    d.add("DN", dn);
    ldap_memfree(dn);
    
    // parse attributes
    char * attr;
    BerElement * ber;
    
    for (attr = ldap_first_attribute(_server, entry, &ber); attr != NULL; attr = ldap_next_attribute(_server, entry, ber)) {
      char ** values;
      if((values = ldap_get_values(_server, entry, attr)) != NULL) {
        for (int i = 0; values[i] != NULL; i++) {
          d.add(attr, values[i]);
        }
        ldap_memvfree(values);
      }
      
      ldap_memfree(attr);
    }
    ber_free(ber, 0);
    
  }
  
  ldap_msgfree(result);
}

