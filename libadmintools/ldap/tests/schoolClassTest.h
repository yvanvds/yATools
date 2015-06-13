/*
 * File:   schoolClassTest.h
 * Author: yvan
 *
 * Created on Jun 13, 2015, 1:06:40 PM
 */

#ifndef SCHOOLCLASSTEST_H
#define	SCHOOLCLASSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../server.h"

class schoolClassTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(schoolClassTest);

  CPPUNIT_TEST(testAddClass);
  CPPUNIT_TEST(testAddStudent);
  CPPUNIT_TEST(testAdjunct);
  CPPUNIT_TEST(testAdminCode);
  CPPUNIT_TEST(testDescription);
  CPPUNIT_TEST(testSchoolID);
  CPPUNIT_TEST(testTitular);

  CPPUNIT_TEST_SUITE_END();

public:
  schoolClassTest();
  virtual ~schoolClassTest();
  void setUp();
  void tearDown();

private:
  void testAddClass();
  void testAddStudent();
  void testAdjunct();
  void testAdminCode();
  void testDescription();
  void testSchoolID();
  void testTitular();


  void addTestClass(y::ldap::server & server);
  void removeTestClass(y::ldap::server & server);
};

#endif	/* SCHOOLCLASSTEST_H */

