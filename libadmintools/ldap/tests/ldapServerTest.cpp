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
}

void ldapServerTest::testGetAccount2() {

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

void ldapServerTest::testAuth() {
  y::ldap::UID uid(y::utils::Config().getLdapTestUID());
  y::ldap::account & a = y::ldap::Server().getAccount(uid);
  y::ldap::DN dn(a.dn());
  y::ldap::PASSWORD pwd(y::utils::Config().getLdapTestPassword());
  
  if(!y::ldap::Server().auth(dn, pwd)) {
    CPPUNIT_ASSERT(false);
  }
  
  if(y::ldap::Server().auth(dn, y::ldap::PASSWORD(""))) {
    CPPUNIT_ASSERT(false);
  }
}