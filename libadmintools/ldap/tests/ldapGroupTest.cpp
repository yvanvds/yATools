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
  y::ldap::server Server;
  y::ldap::group  & group = Server.getGroup("6IT", false);
  if (group.cn() != "6IT") {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testDn() {
  y::ldap::server Server;
  y::ldap::group  & group = Server.getGroup("6IT", false);
  if (group.dn()() != "cn=6IT,ou=mailGroups,dc=sanctamaria-aarschot,dc=be") {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testEditable() {
  y::ldap::server Server;
  y::ldap::group  & group = Server.getGroup("6IT", false);
  if (group.editable()) {
    CPPUNIT_ASSERT(false);
  }
  y::ldap::group  & group2 = Server.getGroup("directie", true);
  if (!group2.editable()) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapGroupTest::testFlagForCommit() {
  y::ldap::server Server;
  y::ldap::group  & group = Server.getGroup("6IT", false);
  container<string> & members = group.members();
  members.New() = y::utils::Config().getLdapTestDN();
  if(Server.commitChanges()) {
    // not flagged for commit, so this should not succeed
    CPPUNIT_ASSERT(false);
  }
  
  group.flagForCommit();
  if(!Server.commitChanges()) {
    CPPUNIT_ASSERT(false);
  }
  
  // restore list to previous state
  Server.clear();
  y::ldap::group  & group2 = Server.getGroup("6IT", false);
  container<string> & members2 = group2.members();
  bool found = false;
  for(int i = 0; i < members2.elms(); i++)  {
    if(members2[i] == y::utils::Config().getLdapTestDN()) {
      members2.remove(i);
      found = true;
      break;
    }
  }
  if(!found) CPPUNIT_ASSERT(false);
  group2.flagForCommit();
  Server.commitChanges();
}

void ldapGroupTest::testMembers() {
  y::ldap::server Server;
  int memberCount;
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("6IT", false);
    container<string> & members = group.members();
    memberCount = members.elms();
    members.New() = y::utils::Config().getLdapTestDN();  
    group.flagForCommit();
    Server.commitChanges();
  }
  
  // reload list
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("6IT", false);
    container<string> & members = group.members();
    if(members.elms() != memberCount + 1) {
      CPPUNIT_ASSERT(false);
    }
    
    for(int i = 0; i < members.elms(); i++)  {
      if(members[i] == y::utils::Config().getLdapTestDN()) {
        members.remove(i);
        break;
      }
    }
    
    group.flagForCommit();
    Server.commitChanges();
  }
  
  // reload again
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("6IT", false);
    container<string> & members = group.members();
    if(members.elms() != memberCount) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  // now do the same test with an editable group
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("directie", true);
    container<string> & members = group.members();
    memberCount = members.elms();
    members.New() = "yvan@sanctamaria-aarschot.be"; 
    group.flagForCommit();
    Server.commitChanges();
  }
  
  // reload list
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("directie", true);
    container<string> & members = group.members();
    if(members.elms() != memberCount + 1) {
      CPPUNIT_ASSERT(false);
    }
    
    for(int i = 0; i < members.elms(); i++)  {
      if(members[i] == "yvan@sanctamaria-aarschot.be") {
        members.remove(i);
        break;
      }
    }
    
    group.flagForCommit();
    Server.commitChanges();
  }
  
  // reload again
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("directie", true);
    container<string> & members = group.members();
    if(members.elms() != memberCount) {
      CPPUNIT_ASSERT(false);
    }
  }
}

void ldapGroupTest::testOwners() {
  y::ldap::server Server;
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("6IT", false);
    container<string> & owners = group.owners();
    owners.New() = y::utils::Config().getLdapTestDN();  
    group.flagForCommit();
    Server.commitChanges();
  }
  
  // reload list
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("6IT", false);
    container<string> & owners = group.owners();
    if(owners.elms() != 2) {
      CPPUNIT_ASSERT(false);
    }
    
    for(int i = 0; i < owners.elms(); i++)  {
      if(owners[i] == y::utils::Config().getLdapTestDN()) {
        owners.remove(i);
        break;
      }
    }
    
    group.flagForCommit();
    Server.commitChanges();
  }
  
  // reload again
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("6IT", false);
    container<string> & owners = group.owners();
    if(owners.elms() != 1) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  // now do the same test with an editable group
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("directie", true);
    container<string> & owners = group.owners();
    owners.New() = "yvan@sanctamaria-aarschot.be"; 
    group.flagForCommit();
    Server.commitChanges();
  }
  
  // reload list
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("directie", true);
    container<string> & owners = group.owners();
    if(owners.elms() != 4) {
      CPPUNIT_ASSERT(false);
    }
    
    for(int i = 0; i < owners.elms(); i++)  {
      if(owners[i] == "yvan@sanctamaria-aarschot.be") {
        owners.remove(i);
        break;
      }
    }
    
    group.flagForCommit();
    Server.commitChanges();
  }
  
  // reload again
  {
    Server.clear();
    y::ldap::group  & group = Server.getGroup("directie", true);
    container<string> & owners = group.owners();
    if(owners.elms() != 3) {
      CPPUNIT_ASSERT(false);
    }
  }
}

void ldapGroupTest::testSave() {
  y::ldap::server Server;
  // create a new group
  {
    Server.clear();
    y::ldap::group & group = Server.getGroup("newgroup", false);
    if(!group.isNew()) {
      // this should be a new group
      CPPUNIT_ASSERT(false);
    }

    group.editable(false);
    group.members().New() = y::utils::Config().getLdapTestDN();
    group.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::group & group = Server.getGroup("newgroup", false);
    if(group.isNew()) {
      CPPUNIT_ASSERT(false);
    }
    group.flagForRemoval();
    Server.commitChanges();
  }
  
  {
    // check if it's gone
    Server.clear();
    y::ldap::group & group = Server.getGroup("newgroup", false);
    if(!group.isNew()) {
      // this should be a new group
      CPPUNIT_ASSERT(false);
    }
  }
  
  // create a new editable group
  {
    Server.clear();
    y::ldap::group & group = Server.getGroup("newgroup", true);
    if(!group.isNew()) {
      // this should be a new group
      CPPUNIT_ASSERT(false);
    }

    group.owners().New() = "boss@sanctamaria-aarschot.be";
    group.members().New() = "yvan@sanctamaria-aarschot.be";
    group.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::group & group = Server.getGroup("newgroup", true);
    if(group.isNew()) {
      CPPUNIT_ASSERT(false);
    }
    group.flagForRemoval();
    Server.commitChanges();
  }
  
  {
    // check if it's gone
    Server.clear();
    y::ldap::group & group = Server.getGroup("newgroup", true);
    if(!group.isNew()) {
      // this should be a new group
      CPPUNIT_ASSERT(false);
    }
  }
}

