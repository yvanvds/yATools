/*
 * File:   ldapDataTest.h
 * Author: yvan
 *
 * Created on May 7, 2014, 8:34:07 PM
 */

#ifndef LDAPDATATEST_H
#define	LDAPDATATEST_H

#include <cppunit/extensions/HelperMacros.h>

class ldapDataTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ldapDataTest);

  CPPUNIT_TEST(testAdd);
  CPPUNIT_TEST(testData);
  CPPUNIT_TEST(testGetType);
  CPPUNIT_TEST(testGetValue);
  CPPUNIT_TEST(testNameCount);
  CPPUNIT_TEST(testSize);
  CPPUNIT_TEST(testData2);

  CPPUNIT_TEST_SUITE_END();

public:
  ldapDataTest();
  virtual ~ldapDataTest();
  void setUp();
  void tearDown();

private:
  void testAdd();
  void testData();
  void testGetType();
  void testGetValue();
  void testNameCount();
  void testSize();
  void testData2();

};

#endif	/* LDAPDATATEST_H */

