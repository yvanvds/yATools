/*
 * File:   systemProcessTest.h
 * Author: yvan
 *
 * Created on May 16, 2014, 10:50:25 AM
 */

#ifndef SYSTEMPROCESSTEST_H
#define	SYSTEMPROCESSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class systemProcessTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(systemProcessTest);

  CPPUNIT_TEST(testArg);
  CPPUNIT_TEST(testError);
  CPPUNIT_TEST(testProcess);
  CPPUNIT_TEST(testRun);
  CPPUNIT_TEST(testSuccess);
  CPPUNIT_TEST(testExec);
  CPPUNIT_TEST(testStdOut);

  CPPUNIT_TEST_SUITE_END();

public:
  systemProcessTest();
  virtual ~systemProcessTest();
  void setUp();
  void tearDown();

private:
  void testArg();
  void testError();
  void testProcess();
  void testRun();
  void testSuccess();
  void testExec();
  void testStdOut();

};

#endif	/* SYSTEMPROCESSTEST_H */

