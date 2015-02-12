/*
 * File:   ldapGroupTest.h
 * Author: yvan
 *
 * Created on Feb 11, 2015, 8:50:24 PM
 */

#ifndef LDAPGROUPTEST_H
#define	LDAPGROUPTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ldapGroupTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ldapGroupTest);

  CPPUNIT_TEST(testCn);
  CPPUNIT_TEST(testDn);
  CPPUNIT_TEST(testEditable);
  CPPUNIT_TEST(testFlagForCommit);
  CPPUNIT_TEST(testMembers);
  CPPUNIT_TEST(testOwners);
  CPPUNIT_TEST(testSave);

  CPPUNIT_TEST_SUITE_END();

public:
  ldapGroupTest();
  virtual ~ldapGroupTest();
  void setUp();
  void tearDown();

private:
  void testCn();
  void testDn();
  void testEditable();
  void testFlagForCommit();
  void testMembers();
  void testOwners();
  void testSave();

};

#endif	/* LDAPGROUPTEST_H */

