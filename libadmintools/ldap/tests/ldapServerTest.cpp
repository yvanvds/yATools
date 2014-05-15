/*
 * File:   ldapServerTest.cpp
 * Author: yvan
 *
 * Created on May 6, 2014, 10:44:36 PM
 */

#include "ldapServerTest.h"
#include "../server.h"
#include "utils/config.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ldapServerTest);

ldapServerTest::ldapServerTest() {
}

ldapServerTest::~ldapServerTest() {
}

void ldapServerTest::setUp() {
  // these tests will only work with a valid config file
  // at /etc/yATools.cfg and a working ldap server
  y::utils::Config().load();
  
}

void ldapServerTest::tearDown() {
}

void ldapServerTest::testCommitChanges() {

}

void ldapServerTest::testGetAccount() {
  // these tests will only work with a valid config file
  // at /etc/yATools.cfg and a working ldap server
  y::ldap::account & a = y::ldap::Server().getAccount(y::ldap::UID(y::utils::Config().getLdapTestUID()));
  if(a.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::account & a2 = y::ldap::Server().getAccount(y::ldap::UID(y::utils::Config().getLdapTestUID()));
  if(a2.isNew()) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapServerTest::testAuth() {
  y::ldap::account & a = y::ldap::Server().getAccount(y::ldap::UID(y::utils::Config().getLdapTestUID()));
  if(a.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  
  bool result = y::ldap::Server().auth(a.dn(), y::ldap::PASSWORD(y::utils::Config().getLdapTestPassword()));
  if(!result) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::account & a2 = y::ldap::Server().getAccount(y::ldap::UID(y::utils::Config().getLdapTestUID()));
  if(a2.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  
  result = y::ldap::Server().auth(a2.dn(), y::ldap::PASSWORD(y::utils::Config().getLdapTestPassword()));
  if(!result) {
    CPPUNIT_ASSERT(false);
  }
  
  result = y::ldap::Server().auth(a2.dn(), y::ldap::PASSWORD("wrongpassword"));
  if(result) {
    CPPUNIT_ASSERT(false);
  }
    
  result = y::ldap::Server().auth(a2.dn(), y::ldap::PASSWORD(y::utils::Config().getLdapTestPassword()));
  if(!result) {
    CPPUNIT_ASSERT(false);
  }
    
  result = y::ldap::Server().auth(a2.dn(), y::ldap::PASSWORD("wrongpassword"));
  if(result) {
    CPPUNIT_ASSERT(false);
  }  
    
  result = y::ldap::Server().auth(a2.dn(), y::ldap::PASSWORD(y::utils::Config().getLdapTestPassword()));
  if(!result) {
    CPPUNIT_ASSERT(false);
  }  
  
}

void ldapServerTest::testGetAccount3() {

}

void ldapServerTest::testGetAccounts() {

}

void ldapServerTest::testGetGroup() {

}

void ldapServerTest::testGetGroup2() {

}

void ldapServerTest::testGetGroups() {

}
