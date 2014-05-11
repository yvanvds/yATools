/*
 * File:   dataFieldTest.cpp
 * Author: yvan
 *
 * Created on May 9, 2014, 3:44:14 PM
 */

#include "dataFieldTest.h"
#include "field.h"
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
}

void dataFieldTest::testAsChar() {
  y::data::field _field;
  char result = _field.asChar();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsDouble() {
  y::data::field _field;
  double result = _field.asDouble();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsFloat() {
  y::data::field _field;
  float result = _field.asFloat();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsInt() {
  y::data::field _field;
  int result = _field.asInt();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsLong() {
  y::data::field _field;
  long result = _field.asLong();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsShort() {
  y::data::field _field;
  short result = _field.asShort();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsString() {
  y::data::field _field;
  const std::u16string& result = _field.asString();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAsString8() {
  y::data::field _field;
  const std::string& result = _field.asString8();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAutoIncrement() {
  bool value;
  y::data::field _field;
  field& result = _field.autoIncrement(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testAutoIncrement2() {
  y::data::field _field;
  bool result = _field.autoIncrement();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField() {
  y::data::field _field();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField2() {
  const std::string& name;
  bool value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField3() {
  const std::string& name;
  char value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField4() {
  const std::string& name;
  short value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField5() {
  const std::string& name;
  int value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField6() {
  const std::string& name;
  long value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField7() {
  const std::string& name;
  float value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField8() {
  const std::string& name;
  double value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField9() {
  const std::string& name;
  const std::string& value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testField10() {
  const std::string& name;
  const std::u16string& value;
  y::data::field _field(name, value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testGetType() {
  y::data::field _field;
  FIELD_TYPE result = _field.getType();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testName() {
  y::data::field _field;
  const std::string& result = _field.name();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testName2() {
  const std::string& fieldName;
  y::data::field _field;
  field& result = _field.name(fieldName);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testPrimaryKey() {
  bool value;
  y::data::field _field;
  field& result = _field.primaryKey(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testPrimaryKey2() {
  y::data::field _field;
  bool result = _field.primaryKey();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testRequired() {
  bool value;
  y::data::field _field;
  field& result = _field.required(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testRequired2() {
  y::data::field _field;
  bool result = _field.required();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetBool() {
  bool value;
  y::data::field _field;
  field& result = _field.setBool(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetChar() {
  char value;
  y::data::field _field;
  field& result = _field.setChar(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetDouble() {
  double value;
  y::data::field _field;
  field& result = _field.setDouble(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetFloat() {
  float value;
  y::data::field _field;
  field& result = _field.setFloat(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetInt() {
  int value;
  y::data::field _field;
  field& result = _field.setInt(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetLong() {
  long value;
  y::data::field _field;
  field& result = _field.setLong(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetShort() {
  short value;
  y::data::field _field;
  field& result = _field.setShort(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetString() {
  const std::u16string& value;
  y::data::field _field;
  field& result = _field.setString(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testSetString8() {
  const std::string& value;
  y::data::field _field;
  field& result = _field.setString8(value);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testStringLength() {
  int length;
  y::data::field _field;
  field& result = _field.stringLength(length);
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

void dataFieldTest::testStringLength2() {
  y::data::field _field;
  int result = _field.stringLength();
  if (true /*check result*/) {
    CPPUNIT_ASSERT(false);
  }
}

