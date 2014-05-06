/*
 * File:   sysConfigTest.h
 * Author: yvan
 *
 * Created on May 6, 2014, 9:06:27 PM
 */

#ifndef SYSCONFIGTEST_H
#define	SYSCONFIGTEST_H

#include <cppunit/extensions/HelperMacros.h>

class sysConfigTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(sysConfigTest);

  CPPUNIT_TEST(testGetLdapAdminDN);
  CPPUNIT_TEST(testGetLdapBaseDN);
  CPPUNIT_TEST(testGetLdapHost);
  CPPUNIT_TEST(testGetLdapPasswd);

  CPPUNIT_TEST_SUITE_END();

public:
  sysConfigTest();
  virtual ~sysConfigTest();
  void setUp();
  void tearDown();

private:
  void testGetLdapAdminDN();
  void testGetLdapBaseDN();
  void testGetLdapHost();
  void testGetLdapPasswd();

};

#endif	/* SYSCONFIGTEST_H */

