/*
 * File:   ldpBaseDataTest.h
 * Author: yvan
 *
 * Created on May 5, 2014, 5:17:21 PM
 */

#ifndef LDPBASEDATATEST_H
#define	LDPBASEDATATEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../data.h"

class ldpBaseDataTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ldpBaseDataTest);

  CPPUNIT_TEST(testData);
  CPPUNIT_TEST(testGetType);
  CPPUNIT_TEST(testGetValue);
  CPPUNIT_TEST(testNameCount);
  CPPUNIT_TEST(testSize);

  CPPUNIT_TEST_SUITE_END();

public:
  ldpBaseDataTest();
  virtual ~ldpBaseDataTest();
  void setUp();
  void tearDown();

private:
  void testData();
  void testGetType();
  void testGetValue();
  void testNameCount();
  void testSize();

  y::ldap::data _data;
};

#endif	/* LDPBASEDATATEST_H */

