/*
 * File:   dataRowTest.cpp
 * Author: yvan
 *
 * Created on May 11, 2014, 3:22:46 PM
 */

#include "dataRowTest.h"
#include "../row.h"


CPPUNIT_TEST_SUITE_REGISTRATION(dataRowTest);

dataRowTest::dataRowTest() {
}

dataRowTest::~dataRowTest() {
}

void dataRowTest::setUp() {
}

void dataRowTest::tearDown() {
}

void dataRowTest::testAddBool() {
  y::data::row _row;
 _row.addBool("field1", true);
  if (!_row["field1"].asBool()) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testAddChar() {
  char value = 45;
  y::data::row _row;
 _row.addChar("field1", value);
  if (_row["field1"].asChar() != 45) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testAddDouble() {
  double value = 45.6;
  y::data::row _row;
 _row.addDouble("field1", value);
  if (_row["field1"].asDouble() != 45.6) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testAddFloat() {
  float value = 3.14;
  y::data::row _row;
 _row.addFloat("field1", value);
  if (_row["field1"].asFloat() != value) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testAddInt() {
  int value = 42;
  y::data::row _row;
 _row.addInt("field1", value);
  if (_row["field1"].asInt() != value) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testAddLong() {
  long value = 42;
  y::data::row _row;
 _row.addLong("field1", value);
  if (_row["field1"].asLong() != value) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testAddShort() {
  short value = 42;
  y::data::row _row;
 _row.addShort("field1", value);
  if (_row["field1"].asShort() != value) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testAddString() {
  string value = "test";
  y::data::row _row;
 _row.addString("field1", value);
  if (_row["field1"].asString() != value) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testClear() {
  y::data::row _row;
  _row.addInt("field1", 1);
  _row.addInt("field2", 1);
  _row.addInt("field3", 1);
  _row.clear();
  if (_row.elms()) {
    CPPUNIT_ASSERT(false);
  }
}

void dataRowTest::testElms() {
  y::data::row _row;
  _row.addInt("field1", 1);
  _row.addInt("field2", 1);
  _row.addInt("field3", 1);
  if (_row.elms() != 3) {
    CPPUNIT_ASSERT(false);
  }
}

