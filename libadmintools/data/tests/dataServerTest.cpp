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
}

dataServerTest::~dataServerTest() {
}

void dataServerTest::setUp() {
  y::utils::Config().load();
}

void dataServerTest::tearDown() {
}

void dataServerTest::testCreate() {
  if(y::data::Server().hasDatabase("serverUnitTest")) {
    y::data::Server().drop("serverUnitTest");
  }
  if (y::data::Server().hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  
  y::data::Server().create("serverUnitTest");
  
  if (!y::data::Server().hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  y::data::Server().drop("serverUnitTest");
}

void dataServerTest::testDrop() {
  if(!y::data::Server().hasDatabase("serverUnitTest")) {
    y::data::Server().create("serverUnitTest");
  }
  if (!y::data::Server().hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  y::data::Server().drop("serverUnitTest");
  if (y::data::Server().hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataServerTest::testHasDatabase() {
  y::data::Server().create("serverUnitTest");
  if (!y::data::Server().hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  
  y::data::Server().drop("serverUnitTest");
  if (y::data::Server().hasDatabase("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
}

