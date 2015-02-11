/*
 * File:   ldapGroupTest.cpp
 * Author: yvan
 *
 * Created on Feb 11, 2015, 8:50:25 PM
 */

#include "ldapGroupTest.h"
#include "../group.h"
#include "utils/config.h"
#include "ldap/server.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ldapGroupTest);

ldapGroupTest::ldapGroupTest() {
}

ldapGroupTest::~ldapGroupTest() {
}

void ldapGroupTest::setUp() {
  // these tests will only work with a valid config file
  // at /etc/yATools.cfg and a working ldap server
  y::utils::Config().load();
}

void ldapGroupTest::tearDown() {
}

void ldapGroupTest::testCn() {
  y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN("6INF1"));
  if (group.cn()().compare("6INF1") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testDn() {
  y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN("6INF1"));
  if (group.dn()().compare("cn=6INF1,ou=mailGroups,dc=sanctamaria-aarschot,dc=be") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testEditable() {
  y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN("6INF1"));
  if (group.editable()) {
    CPPUNIT_ASSERT(false);
  }
  y::ldap::group  & group2 = y::ldap::Server().getGroup(y::ldap::CN("directie"));
  if (!group2.editable()) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testFlagForCommit() {
  y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN("6INF1"));
  container<std::string> & members = group.members();
  members.New() = y::utils::Config().getLdapTestDN();
  if(y::ldap::Server().commitChanges()) {
    // not flagged for commit, so this should not succeed
    CPPUNIT_ASSERT(false);
  }
  
  group.flagForCommit();
  if(!y::ldap::Server().commitChanges()) {
    CPPUNIT_ASSERT(false);
  }
  
  // restore list to previous state
  y::ldap::Server().clear();
  y::ldap::group  & group2 = y::ldap::Server().getGroup(y::ldap::CN("6INF1"));
  container<std::string> & members2 = group2.members();
  for(int i = 0; i < members2.elms(); i++)  {
    if(members2[i].compare(y::utils::Config().getLdapTestDN()) == 0) {
      members2.remove(i);
      break;
    }
  }
  group2.flagForCommit();
  y::ldap::Server().commitChanges();
}

void ldapGroupTest::testMembers() {
  
}

void ldapGroupTest::testOwners() {

}

void ldapGroupTest::testSave() {

}

