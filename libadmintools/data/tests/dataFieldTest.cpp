/*
 * File:   dataFieldTest.cpp
 * Author: yvan
 *
 * Created on May 9, 2014, 3:44:14 PM
 */

#include "dataFieldTest.h"
#include "../field.h"
#include "utils/config.h"


CPPUNIT_TEST_SUITE_REGISTRATION(dataFieldTest);

dataFieldTest::dataFieldTest() {
  y::utils::Config().load();
}

dataFieldTest::~dataFieldTest() {
}

void dataFieldTest::setUp() {
  
}

void dataFieldTest::tearDown() {
}

void dataFieldTest::testAsBool() {
  y::data::field _field("testbool", true);
  bool result = _field.asBool();
  if (result == false) {
    CPPUNIT_ASSERT(false);
  }
  _field.setBool(false);
  result = _field.asBool();
  if (result == true) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::BOOL) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsChar() {
  char c = 65;
  y::data::field _field("testchar", c);
  char result = _field.asChar();
  if (result != c) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::CHAR) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsDouble() {
  double d = 4.5;
  y::data::field _field("testDouble", d);
  double result = _field.asDouble();
  if (result != d) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::DOUBLE) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsFloat() {
  float f = 4.5;
  y::data::field _field("testFloat", f);
  float result = _field.asFloat();
  if (result != f) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::FLOAT) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsInt() {
  int i = 3;
  y::data::field _field("testInt", i);
  int result = _field.asInt();
  if (i != result) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::INT) {
    CPPUNIT_ASSERT(false);
  }  
}

void dataFieldTest::testAsLong() {
  long l = 4968347;
  y::data::field _field("testLong", l);
  long result = _field.asLong();
  if (l != result) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::LONG) {
    CPPUNIT_ASSERT(false);
  }  
}

void dataFieldTest::testAsShort() {
  short s = 120;
  y::data::field _field("testShort", s);
  short result = _field.asShort();
  if (s != result) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::SHORT) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsString() {
  std::u16string s = u"test";
  y::data::field _field("stringtest", s);
  const std::u16string& result = _field.asString();
  if (result.compare(s) != 0) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::STRING) {
    CPPUNIT_ASSERT(false);
  }  
}

void dataFieldTest::testAsString8() {
  std::string s = "test";
  y::data::field _field("stringtest", s);
  const std::string& result = _field.asString8();
  if (result.compare(s) != 0) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::STRING8) {
    CPPUNIT_ASSERT(false);
  }  
}

void dataFieldTest::testAutoIncrement() {
  y::data::field _field;
  _field.autoIncrement(true);
  if (!_field.autoIncrement()) {
    CPPUNIT_ASSERT(false);
  }
}


void dataFieldTest::testGetType() {
  y::data::field _field;
  y::data::FIELD_TYPE result = _field.getType();
  if (result != y::data::UNKNOWN) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testName() {
  y::data::field _field("fieldname", true);
  const std::string& result = _field.name();
  if (result.compare("fieldname") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testName2() {
  y::data::field _field;
  _field.name("fieldname");
  if (_field.name().compare("fieldname") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testPrimaryKey() {
  y::data::field _field;
   _field.primaryKey(true);
  if (!_field.primaryKey()) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testRequired() {
  y::data::field _field;
  _field.required(true);
  if (!_field.required()) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetBool() {
  y::data::field _field;
  _field.setBool(true);
  if (_field.asBool() != true) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::BOOL) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetChar() {
  char value = 67;
  y::data::field _field;
  _field.setChar(value);
  if (_field.asChar() != value) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::CHAR) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetDouble() {
  double value = 67.5468546;
  y::data::field _field;
  _field.setDouble(value);
  if (_field.asDouble() != value) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::DOUBLE) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetFloat() {
  float value = 67.1;
  y::data::field _field;
  _field.setFloat(value);
  if (_field.asFloat() != value) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::FLOAT) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetInt() {
  int value = 42;
  y::data::field _field;
  _field.setInt(value);
  if (_field.asInt() != value) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::INT) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetLong() {
  long value = 42;
  y::data::field _field;
  _field.setLong(value);
  if (_field.asLong() != value) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::LONG) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetShort() {
  short value = 42;
  y::data::field _field;
  _field.setShort(value);
  if (_field.asShort() != value) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::SHORT) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetString() {
  std::u16string value = u"test";
  y::data::field _field;
  _field.setString(value);
  if (_field.asString().compare(value) != 0) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::STRING) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetString8() {
  std::string value = "test";
  y::data::field _field;
  _field.setString8(value);
  if (_field.asString8().compare(value) != 0) {
    CPPUNIT_ASSERT(false);
  }
  if(_field.getType() != y::data::STRING8) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testStringLength() {
  int length = 18;
  y::data::field _field;
  _field.stringLength(length);
  if (_field.stringLength() != 18) {
    CPPUNIT_ASSERT(false);
  }
}
