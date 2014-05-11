/*
 * File:   dataFieldTest.h
 * Author: yvan
 *
 * Created on May 9, 2014, 3:44:13 PM
 */

#ifndef DATAFIELDTEST_H
#define	DATAFIELDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class dataFieldTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(dataFieldTest);

  CPPUNIT_TEST(testAsBool);
  CPPUNIT_TEST(testAsChar);
  CPPUNIT_TEST(testAsDouble);
  CPPUNIT_TEST(testAsFloat);
  CPPUNIT_TEST(testAsInt);
  CPPUNIT_TEST(testAsLong);
  CPPUNIT_TEST(testAsShort);
  CPPUNIT_TEST(testAsString);
  CPPUNIT_TEST(testAsString8);
  CPPUNIT_TEST(testAutoIncrement);
  CPPUNIT_TEST(testGetType);
  CPPUNIT_TEST(testName);
  CPPUNIT_TEST(testName2);
  CPPUNIT_TEST(testPrimaryKey);
  CPPUNIT_TEST(testRequired);
  CPPUNIT_TEST(testSetBool);
  CPPUNIT_TEST(testSetChar);
  CPPUNIT_TEST(testSetDouble);
  CPPUNIT_TEST(testSetFloat);
  CPPUNIT_TEST(testSetInt);
  CPPUNIT_TEST(testSetLong);
  CPPUNIT_TEST(testSetShort);
  CPPUNIT_TEST(testSetString);
  CPPUNIT_TEST(testSetString8);
  CPPUNIT_TEST(testStringLength);

  CPPUNIT_TEST_SUITE_END();

public:
  dataFieldTest();
  virtual ~dataFieldTest();
  void setUp();
  void tearDown();

private:
  void testAsBool();
  void testAsChar();
  void testAsDouble();
  void testAsFloat();
  void testAsInt();
  void testAsLong();
  void testAsShort();
  void testAsString();
  void testAsString8();
  void testAutoIncrement();
  void testGetType();
  void testName();
  void testName2();
  void testPrimaryKey();
  void testRequired();
  void testSetBool();
  void testSetChar();
  void testSetDouble();
  void testSetFloat();
  void testSetInt();
  void testSetLong();
  void testSetShort();
  void testSetString();
  void testSetString8();
  void testStringLength();

};

#endif	/* DATAFIELDTEST_H */

