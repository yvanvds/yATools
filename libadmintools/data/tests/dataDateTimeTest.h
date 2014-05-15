/*
 * File:   dataDateTimeTest.h
 * Author: yvan
 *
 * Created on May 14, 2014, 9:53:36 PM
 */

#ifndef DATADATETIMETEST_H
#define	DATADATETIMETEST_H

#include <cppunit/extensions/HelperMacros.h>

class dataDateTimeTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(dataDateTimeTest);

  CPPUNIT_TEST(testDbFormat);
  CPPUNIT_TEST(testDbFormat2);

  CPPUNIT_TEST_SUITE_END();

public:
  dataDateTimeTest();
  virtual ~dataDateTimeTest();
  void setUp();
  void tearDown();

private:
  void testDbFormat();
  void testDbFormat2();

};

#endif	/* DATADATETIMETEST_H */

