/*
 * File:   dataRowTest.h
 * Author: yvan
 *
 * Created on May 11, 2014, 3:22:46 PM
 */

#ifndef DATAROWTEST_H
#define	DATAROWTEST_H

#include <cppunit/extensions/HelperMacros.h>

class dataRowTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(dataRowTest);

  CPPUNIT_TEST(testAddBool);
  CPPUNIT_TEST(testAddChar);
  CPPUNIT_TEST(testAddDouble);
  CPPUNIT_TEST(testAddFloat);
  CPPUNIT_TEST(testAddInt);
  CPPUNIT_TEST(testAddLong);
  CPPUNIT_TEST(testAddShort);
  CPPUNIT_TEST(testAddString);
  CPPUNIT_TEST(testAddString8);
  CPPUNIT_TEST(testClear);
  CPPUNIT_TEST(testElms);

  CPPUNIT_TEST_SUITE_END();

public:
  dataRowTest();
  virtual ~dataRowTest();
  void setUp();
  void tearDown();

private:
  void testAddBool();
  void testAddChar();
  void testAddDouble();
  void testAddFloat();
  void testAddInt();
  void testAddLong();
  void testAddShort();
  void testAddString();
  void testAddString8();
  void testClear();
  void testElms();

};

#endif	/* DATAROWTEST_H */

