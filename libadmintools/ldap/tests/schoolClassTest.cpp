/*
 * File:   schoolClassTest.cpp
 * Author: yvan
 *
 * Created on Jun 13, 2015, 1:06:40 PM
 */

#include "schoolClassTest.h"
#include "../schoolClass.h"
#include "utils/config.h"
#include "ldap/server.h"


CPPUNIT_TEST_SUITE_REGISTRATION(schoolClassTest);

schoolClassTest::schoolClassTest() {
}

schoolClassTest::~schoolClassTest() {
}

void schoolClassTest::setUp() {
  y::utils::Config().load();
}

void schoolClassTest::tearDown() {
}

void schoolClassTest::addTestClass(y::ldap::server& server) {
  server.clear();
  y::ldap::schoolClass & tempClass = server.getClass(CN("tempClass"));
  if(tempClass.isNew()) {
    tempClass.description(DESCRIPTION("class for unit testing"));
    tempClass.schoolID(SCHOOL_ID(125252));
    tempClass.adminGroup(ADMINGROUP(32931));

    tempClass.flagForCommit();
    server.commitChanges();
  }
}

void schoolClassTest::removeTestClass(y::ldap::server& server) {
  server.clear();
  y::ldap::schoolClass & tempClass = server.getClass(CN("tempClass"));
  if(!tempClass.isNew()) {
    tempClass.flagForRemoval();
    server.commitChanges();
  }
}

void schoolClassTest::testAddClass() {
  y::ldap::server Server;
  removeTestClass(Server);
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    if(!tempClass.isNew()) {
      // class should not have existed
      CPPUNIT_ASSERT(false);
    }
    
    tempClass.description(DESCRIPTION("class for unit testing"));
    tempClass.schoolID(SCHOOL_ID(125252));
    tempClass.adminGroup(ADMINGROUP(32931));
    
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    if(tempClass.isNew()) {
      // class is still new, should have existed
      CPPUNIT_ASSERT(false);
    }
    
    tempClass.flagForRemoval();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    if(!tempClass.isNew()) {
      // class exists, but should be new
      CPPUNIT_ASSERT(false);
    }
  }
  
}

void schoolClassTest::testAddStudent() {
  y::ldap::server Server;
  addTestClass(Server);
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    tempClass.addStudent(DN(y::utils::Config().getLdapTestDN()));
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    container<string> & students = tempClass.students();
    bool found = false;
    for(int i = 0; i < students.elms(); i++) {
      if(students[i] == y::utils::Config().getLdapTestDN()) {
        found = true;
        break;
      }
    }
    if(!found) {
      CPPUNIT_ASSERT(false);
    }
    
    tempClass.removeStudent(DN(y::utils::Config().getLdapTestDN()));
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    container<string> & students = tempClass.students();
    bool found = false;
    for(int i = 0; i < students.elms(); i++) {
      if(students[i] == y::utils::Config().getLdapTestDN()) {
        found = true;
        break;
      }
    }
    if(found) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  removeTestClass(Server);
}

void schoolClassTest::testAdjunct() {
  y::ldap::server Server;
  addTestClass(Server);
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    tempClass.adjunct(ADJUNCT(DN(y::utils::Config().getLdapTestDN())));
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    if(tempClass.adjunct().get() != DN(y::utils::Config().getLdapTestDN())) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  removeTestClass(Server);
}


void schoolClassTest::testAdminCode() {
  y::ldap::server server;
  addTestClass(server);
  
  {
    server.clear();
    y::ldap::schoolClass & tempClass = server.getClass(CN("tempClass"));
    if(tempClass.adminGroup() != ADMINGROUP(32931)) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  removeTestClass(server);
}


void schoolClassTest::testDescription() {
  y::ldap::server server;
  addTestClass(server);
  
  {
    server.clear();
    y::ldap::schoolClass & tempClass = server.getClass(CN("tempClass"));
    if(tempClass.cn() != CN("tempClass")) {
      CPPUNIT_ASSERT(false);
    }
    if(tempClass.description() != DESCRIPTION("class for unit testing")) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  removeTestClass(server);
}

void schoolClassTest::testSchoolID() {
y::ldap::server server;
  addTestClass(server);
  
  {
    server.clear();
    y::ldap::schoolClass & tempClass = server.getClass(CN("tempClass"));
    if(tempClass.schoolID() != SCHOOL_ID(125252)) {
      CPPUNIT_ASSERT(false);
    }
    
  }
  
  removeTestClass(server);
}

void schoolClassTest::testTitular() {
  y::ldap::server Server;
  addTestClass(Server);
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    tempClass.titular(TITULAR(DN(y::utils::Config().getLdapTestDN())));
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass(CN("tempClass"));
    if(tempClass.titular().get() != DN(y::utils::Config().getLdapTestDN())) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  removeTestClass(Server);
}

