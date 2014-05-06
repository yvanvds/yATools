/*
 * File:   ldpAttributesTest.h
 * Author: yvan
 *
 * Created on May 5, 2014, 10:45:53 PM
 */

#ifndef LDPATTRIBUTESTEST_H
#define	LDPATTRIBUTESTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ldpAttributesTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ldpAttributesTest);

  CPPUNIT_TEST(testDN);
  CPPUNIT_TEST(testFULL_NAME);
  CPPUNIT_TEST(testAsString);
  CPPUNIT_TEST(testGetDay);
  CPPUNIT_TEST(testGetMonth);
  CPPUNIT_TEST(testGetYear);

  CPPUNIT_TEST_SUITE_END();

public:
  ldpAttributesTest();
  virtual ~ldpAttributesTest();
  void setUp();
  void tearDown();

private:
  void testDN();
  void testFULL_NAME();
  void testAsString();
  void testGetDay();
  void testGetMonth();
  void testGetYear();

};

#endif	/* LDPATTRIBUTESTEST_H */

