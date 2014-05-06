/*
 * File:   ldpBaseDataTest.cpp
 * Author: yvan
 *
 * Created on May 5, 2014, 5:17:21 PM
 */

#include "ldpBaseDataTest.h"
#include "../data.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ldpBaseDataTest);

ldpBaseDataTest::ldpBaseDataTest() {
}

ldpBaseDataTest::~ldpBaseDataTest() {
}

void ldpBaseDataTest::setUp() {
  _data.add("name", "myname");
  _data.add("street", "mystreet");
  _data.setType(ldp::data_type::ADD);
}

void ldpBaseDataTest::tearDown() {
}


void ldpBaseDataTest::testData() {
  ldp::data data2(_data);
  if (data2.size() != 2) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpBaseDataTest::testGetType() {
  if (_data.getType() != ldp::data_type::ADD) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpBaseDataTest::testGetValue() {
  const std::string& result = _data.getValue("name", 0);
  if (result.compare("myname") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpBaseDataTest::testNameCount() {
  int result = _data.nameCount("name");
  if (result != 1) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpBaseDataTest::testSize() {
  int result = _data.size();
  if (result != 2) {
    CPPUNIT_ASSERT(false);
  }
}
