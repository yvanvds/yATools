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
  _data.add(L"name", L"myname");
  _data.add(L"street", L"mystreet");
  _data.add(L"street", L"secondstreet");
  _data.setType(y::ldap::data_type::ADD);
}

void ldpBaseDataTest::tearDown() {
}


void ldpBaseDataTest::testData() {
  y::ldap::data data2(_data);
  if (data2.elms() != 3) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpBaseDataTest::testGetType() {
  if (_data.getType() != y::ldap::data_type::ADD) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpBaseDataTest::testGetValue() {
  if (_data.getValue(L"name", 0).compare(L"myname") != 0) {
    CPPUNIT_ASSERT(false);
  }
  if (_data.getValue(L"street", 0).compare(L"mystreet") != 0) {
    CPPUNIT_ASSERT(false);
  }
  if (_data.getValue(L"street", 1).compare(L"secondstreet") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpBaseDataTest::testNameCount() {
  if (_data.elms(L"name") != 1) {
    CPPUNIT_ASSERT(false);
  }
  if (_data.elms(L"street") != 2) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpBaseDataTest::testSize() {
  int result = _data.elms();
  if (result != 3) {
    CPPUNIT_ASSERT(false);
  }
}
