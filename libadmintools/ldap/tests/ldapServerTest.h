/*
 * File:   ldapServerTest.h
 * Author: yvan
 *
 * Created on May 6, 2014, 10:44:36 PM
 */

#ifndef LDAPSERVERTEST_H
#define	LDAPSERVERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ldapServerTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ldapServerTest);

  CPPUNIT_TEST(testCommitChanges);
  CPPUNIT_TEST(testGetAccount);
  CPPUNIT_TEST(testGetAccount2);
  CPPUNIT_TEST(testGetAccount3);
  CPPUNIT_TEST(testGetAccounts);
  CPPUNIT_TEST(testGetGroup);
  CPPUNIT_TEST(testGetGroup2);
  CPPUNIT_TEST(testGetGroups);


  CPPUNIT_TEST_SUITE_END();

public:
  ldapServerTest();
  virtual ~ldapServerTest();
  void setUp();
  void tearDown();

private:
  void testCommitChanges();
  void testGetAccount();
  void testGetAccount2();
  void testGetAccount3();
  void testGetAccounts();
  void testGetGroup();
  void testGetGroup2();
  void testGetGroups();


};

#endif	/* LDAPSERVERTEST_H */

