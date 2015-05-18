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
  y::ldap::Server().clear();
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
  
  y::ldap::account & a3 = y::ldap::Server().getAccount(y::ldap::UID_NUMBER(y::utils::Config().getLdapTestUidNumber().asInt()));
  if(a3.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  if(a3.uidNumber()() != y::utils::Config().getLdapTestUidNumber().asInt()) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::Server().clear();
  y::ldap::account & a4 = y::ldap::Server().getAccount(y::ldap::DN(y::utils::Config().getLdapTestDN()));
  if(a4.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  if(a4.uidNumber()() != y::utils::Config().getLdapTestUidNumber().asInt()) {
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
  y::ldap::Server().clear();
  container<y::ldap::account> & accounts = y::ldap::Server().getAccounts();
  if(accounts.elms() < 500) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapServerTest::testGetGroup() {
  y::ldap::Server().clear();
  // get mailgroup
  y::ldap::group & mailgroup = y::ldap::Server().getGroup("6IT", false);
  if(mailgroup.members().elms() != 22) {
    CPPUNIT_ASSERT(false);
  }
  if(mailgroup.owners().elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::group & newgroup = y::ldap::Server().getGroup("no group", false);
  if(newgroup.members().elms()) {
    CPPUNIT_ASSERT(false);
  }
  if(newgroup.owners().elms()) {
    CPPUNIT_ASSERT(false);
  }
  
  // get editable mailgroup
  y::ldap::group & mailgroup2 = y::ldap::Server().getGroup("directie", true);
  if(mailgroup2.members().elms() != 3) {
    CPPUNIT_ASSERT(false);
  }
  if(mailgroup2.owners().elms() != 3) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapServerTest::testGetGroup2() {
  y::ldap::Server().clear();
  // get mailgroup
  y::ldap::group & mailgroup = y::ldap::Server().getGroup(y::ldap::DN("cn=6IT,ou=mailGroups,dc=sanctamaria-aarschot,dc=be"));
  if(mailgroup.members().elms() != 22) {
    CPPUNIT_ASSERT(false);
  }
  if(mailgroup.owners().elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::group & newgroup = y::ldap::Server().getGroup(y::ldap::DN("cn=6INF4,ou=mailGroups,dc=sanctamaria-aarschot,dc=be"));
  if(newgroup.members().elms()) {
    CPPUNIT_ASSERT(false);
  }
  if(newgroup.owners().elms()) {
    CPPUNIT_ASSERT(false);
  }
  
  // get editable mailgroup
  y::ldap::group & mailgroup2 = y::ldap::Server().getGroup(y::ldap::DN("cn=directie,ou=editableMailGroups,dc=sanctamaria-aarschot,dc=be"));
  if(mailgroup2.members().elms() != 3) {
    CPPUNIT_ASSERT(false);
  }
  if(mailgroup2.owners().elms() != 3) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapServerTest::testGetGroups() {
  y::ldap::Server().clear();
  container<y::ldap::group> & groups = y::ldap::Server().getGroups();
  if(groups.elms() < 100) {
    CPPUNIT_ASSERT(false);
  }
}
