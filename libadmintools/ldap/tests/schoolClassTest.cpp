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
  y::ldap::schoolClass & tempClass = server.getClass("tempClass");
  if(tempClass.isNew()) {
    tempClass.description("class for unit testing");
    tempClass.schoolID(125252);
    tempClass.adminCode(32931);

    tempClass.flagForCommit();
    server.commitChanges();
  }
}

void schoolClassTest::removeTestClass(y::ldap::server& server) {
  server.clear();
  y::ldap::schoolClass & tempClass = server.getClass("tempClass");
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
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
    if(!tempClass.isNew()) {
      // class should not have existed
      CPPUNIT_ASSERT(false);
    }
    
    tempClass.description("class for unit testing");
    tempClass.schoolID(125252);
    tempClass.adminCode(32931);
    
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
    if(tempClass.isNew()) {
      // class is still new, should have existed
      CPPUNIT_ASSERT(false);
    }
    
    tempClass.flagForRemoval();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
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
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
    tempClass.addStudent(y::ldap::DN(y::utils::Config().getLdapTestDN()));
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
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
    
    tempClass.removeStudent(y::ldap::DN(y::utils::Config().getLdapTestDN()));
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
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
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
    tempClass.adjunct(y::ldap::DN(y::utils::Config().getLdapTestDN()));
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
    if(tempClass.adjunct()() != y::utils::Config().getLdapTestDN()) {
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
    y::ldap::schoolClass & tempClass = server.getClass("tempClass");
    if(tempClass.adminCode() != 32931) {
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
    y::ldap::schoolClass & tempClass = server.getClass("tempClass");
    if(tempClass.cn() != "tempClass") {
      CPPUNIT_ASSERT(false);
    }
    if(tempClass.description() != "class for unit testing") {
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
    y::ldap::schoolClass & tempClass = server.getClass("tempClass");
    if(tempClass.schoolID() != 125252) {
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
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
    tempClass.titular(y::ldap::DN(y::utils::Config().getLdapTestDN()));
    tempClass.flagForCommit();
    Server.commitChanges();
  }
  
  {
    Server.clear();
    y::ldap::schoolClass & tempClass = Server.getClass("tempClass");
    if(tempClass.titular()() != y::utils::Config().getLdapTestDN()) {
      CPPUNIT_ASSERT(false);
    }
  }
  
  removeTestClass(Server);
}

