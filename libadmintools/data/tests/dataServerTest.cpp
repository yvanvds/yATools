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
  if(server->hasDatabase(L"serverUnitTest")) {
    server->drop(L"serverUnitTest");
  }
  if (server->hasDatabase(L"serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  
  server->create(L"serverUnitTest");
  
  if (!server->hasDatabase(L"serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  server->drop(L"serverUnitTest");
}

void dataServerTest::testDrop() {
  if(!server->hasDatabase(L"serverUnitTest")) {
    server->create(L"serverUnitTest");
  }
  if (!server->hasDatabase(L"serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  server->drop(L"serverUnitTest");
  if (server->hasDatabase(L"serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataServerTest::testHasDatabase() {
  server->create(L"serverUnitTest");
  if (!server->hasDatabase(L"serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  
  server->drop(L"serverUnitTest");
  if (server->hasDatabase(L"serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
}

