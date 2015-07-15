/*
 * File:   smartschoolTest.h
 * Author: yvan
 *
 * Created on Jul 13, 2015, 5:57:46 PM
 */

#ifndef SMARTSCHOOLTEST_H
#define	SMARTSCHOOLTEST_H

#include <cppunit/extensions/HelperMacros.h>

class smartschoolTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(smartschoolTest);

  CPPUNIT_TEST(testAddCourse);
  CPPUNIT_TEST(testAddUserToGroup);
  CPPUNIT_TEST(testDeleteClass);
  CPPUNIT_TEST(testDeleteUser);
  CPPUNIT_TEST(testErrorToText);
  CPPUNIT_TEST(testGetAbsents);
  CPPUNIT_TEST(testGetAllAccounts);
  CPPUNIT_TEST(testGetAllAccountsExtended);
  CPPUNIT_TEST(testGetAllClasses);
  CPPUNIT_TEST(testGetAllGroupsAndClasses);
  CPPUNIT_TEST(testGetClassTeachers);
  CPPUNIT_TEST(testGetCourses);
  CPPUNIT_TEST(testGetSkoreInfo);
  CPPUNIT_TEST(testGetUserDetails);
  CPPUNIT_TEST(testMoveUserToClass);
  CPPUNIT_TEST(testReplaceWisaID);
  CPPUNIT_TEST(testSaveClass);
  CPPUNIT_TEST(testSaveGroup);
  CPPUNIT_TEST(testSaveNationality);
  CPPUNIT_TEST(testSavePassword);
  CPPUNIT_TEST(testSavePhoto);
  CPPUNIT_TEST(testSaveUser);
  CPPUNIT_TEST(testSendMessage);
  CPPUNIT_TEST(testSetAccountStatus);
  CPPUNIT_TEST(testSetCourseStudents);
  CPPUNIT_TEST(testSetCourseTeachers);
  CPPUNIT_TEST(testUnregister);
  CPPUNIT_TEST(testValidate);

  CPPUNIT_TEST_SUITE_END();

public:
  smartschoolTest();
  virtual ~smartschoolTest();
  void setUp();
  void tearDown();

private:
  void testAddCourse();
  void testAddUserToGroup();
  void testDeleteClass();
  void testDeleteUser();
  void testErrorToText();
  void testGetAbsents();
  void testGetAllAccounts();
  void testGetAllAccountsExtended();
  void testGetAllClasses();
  void testGetAllGroupsAndClasses();
  void testGetClassTeachers();
  void testGetCourses();
  void testGetSkoreInfo();
  void testGetUserDetails();
  void testMoveUserToClass();
  void testReplaceWisaID();
  void testSaveClass();
  void testSaveGroup();
  void testSaveNationality();
  void testSavePassword();
  void testSavePhoto();
  void testSaveUser();
  void testSendMessage();
  void testSetAccountStatus();
  void testSetCourseStudents();
  void testSetCourseTeachers();
  void testUnregister();
  void testValidate();

};

#endif	/* SMARTSCHOOLTEST_H */

