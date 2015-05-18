/*
 * File:   dataServerTest.cpp
 * Author: yvan
 *
 * Created on May 8, 2014, 7:47:44 PM
 */

#include "dataServerTest.h"
#include "../sqlserver.h"
#include "../../utils/config.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dataServerTest);

dataServerTest::dataServerTest() {
  y::utils::Config().load();
  server = std::unique_ptr<y::data::server>(new y::data::server);
}

dataServerTest::~dataServerTest() {
}

void dataServerTest::setUp() {
  
}

void dataServerTest::tearDown() {
}

void dataServerTest::testCreate() {
  if(server->hasDatabase("serverUnitTest")) {
    server->drop("serverUnitTest");
  }
  if (server->hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  
  server->create("serverUnitTest");
  
  if (!server->hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  server->drop("serverUnitTest");
}

void dataServerTest::testDrop() {
  if(!server->hasDatabase("serverUnitTest")) {
    server->create("serverUnitTest");
  }
  if (!server->hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  server->drop("serverUnitTest");
  if (server->hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataServerTest::testHasDatabase() {
  server->create("serverUnitTest");
  if (!server->hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  
  server->drop("serverUnitTest");
  if (server->hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
}

