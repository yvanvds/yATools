/*
 * File:   utilsSecurityTest.h
 * Author: yvan
 *
 * Created on May 8, 2014, 4:46:30 PM
 */

#ifndef UTILSSECURITYTEST_H
#define	UTILSSECURITYTEST_H

#include <cppunit/extensions/HelperMacros.h>

class utilsSecurityTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(utilsSecurityTest);

  CPPUNIT_TEST(testTest);

  CPPUNIT_TEST_SUITE_END();

public:
  utilsSecurityTest();
  virtual ~utilsSecurityTest();
  void setUp();
  void tearDown();

private:
  void testTest();

};

#endif	/* UTILSSECURITYTEST_H */

