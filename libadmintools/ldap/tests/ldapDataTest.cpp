/*
 * File:   ldapDataTest.cpp
 * Author: yvan
 *
 * Created on May 7, 2014, 8:34:07 PM
 */

#include "ldapDataTest.h"
#include "../data.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ldapDataTest);

ldapDataTest::ldapDataTest() {
}

ldapDataTest::~ldapDataTest() {
}

void ldapDataTest::setUp() {
}

void ldapDataTest::tearDown() {
}

void ldapDataTest::testAdd() {
  y::ldap::data _data;
  _data.add("key", "value");
  if (_data.getValue("key").compare("value") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapDataTest::testData() {
  y::ldap::data item1;
  item1.setType(y::ldap::data_type::RESULT);
  item1.add("key", "value");
  y::ldap::data item2(item1);
  
  if (item2.getType() != y::ldap::data_type::RESULT) {
    CPPUNIT_ASSERT(false);
  }
  
  if (item2.getValue("key").compare("value") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapDataTest::testGetType() {
  y::ldap::data _data;
  
  if (_data.getType() != y::ldap::data_type::NONE) {
    CPPUNIT_ASSERT(false);
  }
  
  _data.setType(y::ldap::data_type::DELETE);
  if (_data.getType() != y::ldap::data_type::DELETE) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapDataTest::testGetValue() {
  y::ldap::data _data;
  _data.add("key", "value");
  if (_data.getValue("key").compare("value") != 0) {
    CPPUNIT_ASSERT(false);
  }
  _data.add("key", "value2");
  if (_data.getValue("key", 1).compare("value2") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapDataTest::testNameCount() {
  y::ldap::data _data;
  _data.add("key", "value");
  _data.add("key", "value2");
  if (_data.nameCount("key") != 2) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapDataTest::testSize() {
  y::ldap::data _data;
  if (_data.size() != 0) {
    CPPUNIT_ASSERT(false);
  }
  _data.add("key", "value");
  if (_data.size() != 1) {
    CPPUNIT_ASSERT(false);
  }
  _data.add("key2", "value");
  if (_data.size() != 2) {
    CPPUNIT_ASSERT(false);
  }
  _data.add("key2", "value2");
  if (_data.size() != 3) {
    CPPUNIT_ASSERT(false);
  }
}

void ldapDataTest::testData2() {
  y::ldap::data _data(y::ldap::data_type::DELETE);
  if (_data.getType() != y::ldap::data_type::DELETE) {
    CPPUNIT_ASSERT(false);
  }
}

