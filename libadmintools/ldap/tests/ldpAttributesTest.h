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
  CPPUNIT_TEST(testUID_NUMBER);
  CPPUNIT_TEST(testUID);
  CPPUNIT_TEST(testFULL_NAME);
  CPPUNIT_TEST(testGID);
  CPPUNIT_TEST(testGID_NUMBER);
  CPPUNIT_TEST(testWISA_ID);
  CPPUNIT_TEST(testMAIL);
  CPPUNIT_TEST(testPASSWORD);
  CPPUNIT_TEST(testDAY);
  CPPUNIT_TEST(testMONTH);
  CPPUNIT_TEST(testYEAR);
  CPPUNIT_TEST(testDATE);
  CPPUNIT_TEST(testHOMEDIR);

  CPPUNIT_TEST_SUITE_END();

public:
  ldpAttributesTest();
  virtual ~ldpAttributesTest();
  void setUp();
  void tearDown();

private:
  void testDN();
  void testUID_NUMBER();
  void testUID();
  void testFULL_NAME();
  void testGID();
  void testGID_NUMBER();
  void testWISA_ID();
  void testMAIL();
  void testPASSWORD();
  void testDAY();
  void testMONTH();
  void testYEAR();
  void testDATE();
  void testHOMEDIR();
};

#endif	/* LDPATTRIBUTESTEST_H */

