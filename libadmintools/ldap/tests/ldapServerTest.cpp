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
  y::ldap::server Server;
  Server.clear();
  // these tests will only work with a valid config file
  // at /etc/yATools.cfg and a working ldap server
  y::ldap::account & a = Server.getAccount(UID(y::utils::Config().getLdapTestUID()));
  if(a.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::account & a2 = Server.getAccount(UID(y::utils::Config().getLdapTestUID()));
  if(a2.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::account & a3 = Server.getAccount(UID_NUMBER(y::utils::Config().getLdapTestUidNumber().asInt()));
  if(a3.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  if(a3.uidNumber().get() != y::utils::Config().getLdapTestUidNumber().asInt()) {
    CPPUNIT_ASSERT(false);
  }
  
  Server.clear();
  y::ldap::account & a4 = Server.getAccount(DN(y::utils::Config().getLdapTestDN()));
  if(a4.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  if(a4.uidNumber().get() != y::utils::Config().getLdapTestUidNumber().asInt()) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapServerTest::testAuth() {
  y::ldap::server Server;
  y::ldap::account & a = Server.getAccount(UID(y::utils::Config().getLdapTestUID()));
  if(a.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  
  bool result = Server.auth(a.dn(), PASSWORD(y::utils::Config().getLdapTestPassword()));
  if(!result) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::account & a2 = Server.getAccount(UID(y::utils::Config().getLdapTestUID()));
  if(a2.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  
  result = Server.auth(a2.dn(), PASSWORD(y::utils::Config().getLdapTestPassword()));
  if(!result) {
    CPPUNIT_ASSERT(false);
  }
  
  result = Server.auth(a2.dn(), PASSWORD("wrongpassword"));
  if(result) {
    CPPUNIT_ASSERT(false);
  }
    
  result = Server.auth(a2.dn(), PASSWORD(y::utils::Config().getLdapTestPassword()));
  if(!result) {
    CPPUNIT_ASSERT(false);
  }
    
  result = Server.auth(a2.dn(), PASSWORD("wrongpassword"));
  if(result) {
    CPPUNIT_ASSERT(false);
  }  
    
  result = Server.auth(a2.dn(), PASSWORD(y::utils::Config().getLdapTestPassword()));
  if(!result) {
    CPPUNIT_ASSERT(false);
  }  
  
}

void ldapServerTest::testGetAccount3() {

}

void ldapServerTest::testGetAccounts() {
  y::ldap::server Server;
  Server.clear();
  ACCOUNTS & accounts = Server.getAccounts();
  if(accounts.elms() < 500) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapServerTest::testGetGroup() {
  y::ldap::server Server;
  Server.clear();
  // get mailgroup
  y::ldap::group & mailgroup = Server.getGroup(CN("6IT"), false);
  if(mailgroup.members().elms() != 21) {
    CPPUNIT_ASSERT(false);
  }
  if(mailgroup.owners().elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::group & newgroup = Server.getGroup(CN("no group"), false);
  if(newgroup.members().elms()) {
    CPPUNIT_ASSERT(false);
  }
  if(newgroup.owners().elms()) {
    CPPUNIT_ASSERT(false);
  }
  
  // get editable mailgroup
  y::ldap::group & mailgroup2 = Server.getGroup(CN("directie"), true);
  if(mailgroup2.members().elms() != 4) {
    CPPUNIT_ASSERT(false);
  }
  if(mailgroup2.owners().elms() != 4) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapServerTest::testGetGroup2() {
  y::ldap::server Server;
  Server.clear();
  // get mailgroup
  y::ldap::group & mailgroup = Server.getGroup(DN("cn=6IT,ou=mailGroups,dc=sanctamaria-aarschot,dc=be"));
  if(mailgroup.members().elms() != 21) {
    CPPUNIT_ASSERT(false);
  }
  if(mailgroup.owners().elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  
  y::ldap::group & newgroup = Server.getGroup(DN("cn=6INF4,ou=mailGroups,dc=sanctamaria-aarschot,dc=be"));
  if(newgroup.members().elms()) {
    CPPUNIT_ASSERT(false);
  }
  if(newgroup.owners().elms()) {
    CPPUNIT_ASSERT(false);
  }
  
  // get editable mailgroup
  y::ldap::group & mailgroup2 = Server.getGroup(DN("cn=directie,ou=editableMailGroups,dc=sanctamaria-aarschot,dc=be"));
  if(mailgroup2.members().elms() != 4) {
    CPPUNIT_ASSERT(false);
  }
  if(mailgroup2.owners().elms() != 4) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapServerTest::testGetGroups() {
  y::ldap::server Server;
  Server.clear();
  GROUPS & groups = Server.getGroups();
  if(groups.elms() < 100) {
    CPPUNIT_ASSERT(false);
  }
}
