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
  y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
  if (group.cn()().compare(L"6INF1") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testDn() {
  y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
  if (group.dn()().compare(L"cn=6INF1,ou=mailGroups,dc=sanctamaria-aarschot,dc=be") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testEditable() {
  y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
  if (group.editable()) {
    CPPUNIT_ASSERT(false);
  }
  y::ldap::group  & group2 = y::ldap::Server().getGroup(y::ldap::CN(L"directie"), true);
  if (!group2.editable()) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testFlagForCommit() {
  y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
  container<std::wstring> & members = group.members();
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
  y::ldap::group  & group2 = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
  container<std::wstring> & members2 = group2.members();
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
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
    container<std::wstring> & members = group.members();
    members.New() = y::utils::Config().getLdapTestDN();  
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  // reload list
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
    container<std::wstring> & members = group.members();
    if(members.elms() != 14) {
      CPPUNIT_ASSERT(false);
    }
    
    for(int i = 0; i < members.elms(); i++)  {
      if(members[i].compare(y::utils::Config().getLdapTestDN()) == 0) {
        members.remove(i);
        break;
      }
    }
    
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  // reload again
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
    container<std::wstring> & members = group.members();
    if(members.elms() != 13) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  // now do the same test with an editable group
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"directie"), true);
    container<std::wstring> & members = group.members();
    members.New() = L"yvan@sanctamaria-aarschot.be"; 
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  // reload list
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"directie"), true);
    container<std::wstring> & members = group.members();
    if(members.elms() != 4) {
      CPPUNIT_ASSERT(false);
    }
    
    for(int i = 0; i < members.elms(); i++)  {
      if(members[i].compare(L"yvan@sanctamaria-aarschot.be") == 0) {
        members.remove(i);
        break;
      }
    }
    
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  // reload again
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"directie"), true);
    container<std::wstring> & members = group.members();
    if(members.elms() != 3) {
      CPPUNIT_ASSERT(false);
    }
  }
}

void ldapGroupTest::testOwners() {
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
    container<std::wstring> & owners = group.owners();
    owners.New() = y::utils::Config().getLdapTestDN();  
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  // reload list
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
    container<std::wstring> & owners = group.owners();
    if(owners.elms() != 2) {
      CPPUNIT_ASSERT(false);
    }
    
    for(int i = 0; i < owners.elms(); i++)  {
      if(owners[i].compare(y::utils::Config().getLdapTestDN()) == 0) {
        owners.remove(i);
        break;
      }
    }
    
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  // reload again
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"6INF1"), false);
    container<std::wstring> & owners = group.owners();
    if(owners.elms() != 1) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  // now do the same test with an editable group
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"directie"), true);
    container<std::wstring> & owners = group.owners();
    owners.New() = L"yvan@sanctamaria-aarschot.be"; 
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  // reload list
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"directie"), true);
    container<std::wstring> & owners = group.owners();
    if(owners.elms() != 4) {
      CPPUNIT_ASSERT(false);
    }
    
    for(int i = 0; i < owners.elms(); i++)  {
      if(owners[i].compare(L"yvan@sanctamaria-aarschot.be") == 0) {
        owners.remove(i);
        break;
      }
    }
    
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  // reload again
  {
    y::ldap::Server().clear();
    y::ldap::group  & group = y::ldap::Server().getGroup(y::ldap::CN(L"directie"), true);
    container<std::wstring> & owners = group.owners();
    if(owners.elms() != 3) {
      CPPUNIT_ASSERT(false);
    }
  }
}

void ldapGroupTest::testSave() {
  // create a new group
  {
    y::ldap::Server().clear();
    y::ldap::group & group = y::ldap::Server().getGroup(y::ldap::CN(L"newgroup"), false);
    if(!group.isNew()) {
      // this should be a new group
      CPPUNIT_ASSERT(false);
    }

    group.editable(false);
    group.members().New() = y::utils::Config().getLdapTestDN();
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  {
    y::ldap::Server().clear();
    y::ldap::group & group = y::ldap::Server().getGroup(y::ldap::CN(L"newgroup"), false);
    if(group.isNew()) {
      CPPUNIT_ASSERT(false);
    }
    group.flagForDelete();
    y::ldap::Server().commitChanges();
  }
  
  {
    // check if it's gone
    y::ldap::Server().clear();
    y::ldap::group & group = y::ldap::Server().getGroup(y::ldap::CN(L"newgroup"), false);
    if(!group.isNew()) {
      // this should be a new group
      CPPUNIT_ASSERT(false);
    }
  }
  
  // create a new editable group
  {
    y::ldap::Server().clear();
    y::ldap::group & group = y::ldap::Server().getGroup(y::ldap::CN(L"newgroup"), true);
    if(!group.isNew()) {
      // this should be a new group
      CPPUNIT_ASSERT(false);
    }

    group.owners().New() = L"boss@sanctamaria-aarschot.be";
    group.members().New() = L"yvan@sanctamaria-aarschot.be";
    group.flagForCommit();
    y::ldap::Server().commitChanges();
  }
  
  {
    y::ldap::Server().clear();
    y::ldap::group & group = y::ldap::Server().getGroup(y::ldap::CN(L"newgroup"), true);
    if(group.isNew()) {
      CPPUNIT_ASSERT(false);
    }
    group.flagForDelete();
    y::ldap::Server().commitChanges();
  }
  
  {
    // check if it's gone
    y::ldap::Server().clear();
    y::ldap::group & group = y::ldap::Server().getGroup(y::ldap::CN(L"newgroup"), true);
    if(!group.isNew()) {
      // this should be a new group
      CPPUNIT_ASSERT(false);
    }
  }
}

