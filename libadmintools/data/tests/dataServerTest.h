/*
 * File:   dataServerTest.h
 * Author: yvan
 *
 * Created on May 8, 2014, 7:47:44 PM
 */

#ifndef DATASERVERTEST_H
#define	DATASERVERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../sqlserver.h"

class dataServerTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(dataServerTest);

  CPPUNIT_TEST(testCreate);
  CPPUNIT_TEST(testDrop);
  CPPUNIT_TEST(testHasDatabase);

  CPPUNIT_TEST_SUITE_END();

public:
  dataServerTest();
  virtual ~dataServerTest();
  void setUp();
  void tearDown();

private:
  void testCreate();
  void testDrop();
  void testHasDatabase();

  y::data::server server;
};

#endif	/* DATASERVERTEST_H */

