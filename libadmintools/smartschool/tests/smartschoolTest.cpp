/*
 * File:   smartschoolTest.cpp
 * Author: yvan
 *
 * Created on Jul 13, 2015, 5:57:46 PM
 */

#include "smartschoolTest.h"
#include "smartschool/smartschool.h"
#include "utils/config.h"
#include "ldap/account.h"
#include "ldap/server.h"


CPPUNIT_TEST_SUITE_REGISTRATION(smartschoolTest);

string courseName("impossible course name");
string courseDescription("course for unit testing");

smartschoolTest::smartschoolTest() {
}

smartschoolTest::~smartschoolTest() {
}

void smartschoolTest::setUp() {
  y::utils::Config().load();
}

void smartschoolTest::tearDown() {
}


void smartschoolTest::testGetCourses() {
  container<y::smartschool::course> result;
  if(!y::Smartschool().getCourses(result)) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].name.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].description.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].mainTeacher.firstname.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].mainTeacher.lastname.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].mainTeacher.username.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].mainTeacher.wisaID.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].classes.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].classes[0].name.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].classes[0].description.empty()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[0].classes[0].type.empty()) {
    CPPUNIT_ASSERT(false);
  }
}

void smartschoolTest::testAddCourse() {
  // disabled as long as courses cannot be deleted with the smartschool API
//  y::Smartschool().addCourse(courseName, courseDescription);
//  
//  container<y::smartschool::course> result;
//  if(!y::Smartschool().getCourses(result)) {
//    CPPUNIT_ASSERT(false);
//  }
//  
//  bool found = false;
//  for(int i = 0; i < result.elms(); i++) {
//    if(result[i].name == courseName) {
//      found = true;
//      
//      if(result[i].description != courseDescription) {
//        CPPUNIT_ASSERT(false);
//      }
//    }
//  }
//  
//  if(!found) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testAddUserToGroup() {
//  const y::ldap::account& account;
//  const string& group;
//  bool keepCurrent;
//  y::smartschool _smartschool;
//  bool result = _smartschool.addUserToGroup(account, group, keepCurrent);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testDeleteClass() {
//  const y::ldap::schoolClass& group;
//  y::smartschool _smartschool;
//  bool result = _smartschool.deleteClass(group);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testDeleteUser() {
//  const y::ldap::account& account;
//  y::smartschool _smartschool;
//  bool result = _smartschool.deleteUser(account);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testErrorToText() {
//  int code;
//  y::smartschool _smartschool;
//  string result = _smartschool.errorToText(code);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testGetAbsents() {
//  const y::ldap::account& account;
//  int year;
//  container<string>& absents;
//  y::smartschool _smartschool;
//  bool result = _smartschool.getAbsents(account, year, absents);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testGetAllAccounts() {
//  const string& group;
//  bool recursive;
//  container<string>& accounts;
//  y::smartschool _smartschool;
//  bool result = _smartschool.getAllAccounts(group, recursive, accounts);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testGetAllAccountsExtended() {
//  const string& group;
//  bool recursive;
//  container<string>& accounts;
//  y::smartschool _smartschool;
//  bool result = _smartschool.getAllAccountsExtended(group, recursive, accounts);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testGetAllClasses() {
//  container<string>& result;
//  y::smartschool _smartschool;
//  bool result = _smartschool.getAllClasses(result);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testGetAllGroupsAndClasses() {
//  container<string>& result;
//  y::smartschool _smartschool;
//  bool result = _smartschool.getAllGroupsAndClasses(result);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testGetClassTeachers() {
//  container<string>& result;
//  y::smartschool _smartschool;
//  bool result = _smartschool.getClassTeachers(result);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}



void smartschoolTest::testGetSkoreInfo() {
//  container<string>& result;
//  y::smartschool _smartschool;
//  bool result = _smartschool.getSkoreInfo(result);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testGetUserDetails() {
//  const string& name;
//  const string& password;
//  y::data::row& details;
//  y::smartschool _smartschool;
//  bool result = _smartschool.getUserDetails(name, password, details);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testMoveUserToClass() {
//  const y::ldap::account& account;
//  const y::ldap::schoolClass& newClass;
//  y::smartschool _smartschool;
//  bool result = _smartschool.moveUserToClass(account, newClass);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testReplaceWisaID() {
//  const y::ldap::account& account;
//  WISA_ID& oldID;
//  y::smartschool _smartschool;
//  bool result = _smartschool.replaceWisaID(account, oldID);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testSaveClass() {
  y::ldap::server Server;
  y::ldap::schoolClass & group = Server.getClass(CN("1X"));
  group.cn(CN("1X"));
  group.description(DESCRIPTION("1e leerjaar X (test)"));
  group.schoolID(SCHOOL_ID(125261));
  group.adminGroup(ADMINGROUP(6246));
  
  if(!y::Smartschool().saveClass(group)) {
    CPPUNIT_ASSERT(false);
  }
  
  if(!y::Smartschool().deleteClass(group)) {
    CPPUNIT_ASSERT(false);
  }
  
}

void smartschoolTest::testSaveGroup() {
//  const y::ldap::group& group;
//  y::smartschool _smartschool;
//  bool result = _smartschool.saveGroup(group);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testSaveNationality() {
//  const y::ldap::account& account;
//  y::smartschool _smartschool;
//  bool result = _smartschool.saveNationality(account);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testValidate() {
  string username = y::utils::Config().getLdapTestUID();
  string password = y::utils::Config().getLdapTestPassword();
  
  if(!y::Smartschool().validate(username, password)) {
    CPPUNIT_ASSERT(false);
  }
  
  y::utils::Log().add("\n Just testing this error message. It's ok.");
  if(y::Smartschool().validate(username, "bogus")) {
    CPPUNIT_ASSERT(false);
  }
}

void smartschoolTest::testSavePassword() {
  y::ldap::server Server;
  y::ldap::account & a = Server.getAccount(UID(y::utils::Config().getLdapTestUID()));
  a.ssPassword("ABcd!eGf");
  y::Smartschool().savePassword(a);
  
  if(!y::Smartschool().validate(y::utils::Config().getLdapTestUID(), "ABcd!eGf")) {
    CPPUNIT_ASSERT(false);
  }
  
  a.ssPassword(y::utils::Config().getLdapTestPassword());
  y::Smartschool().savePassword(a);
  
  if(!y::Smartschool().validate(y::utils::Config().getLdapTestUID(), y::utils::Config().getLdapTestPassword())) {
    CPPUNIT_ASSERT(false);
  }
}

void smartschoolTest::testSavePhoto() {
//  const y::ldap::account& account;
//  y::smartschool _smartschool;
//  bool result = _smartschool.savePhoto(account);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testSaveUser() {
  y::ldap::server Server;
  y::ldap::account & a = Server.getAccount(UID("unitTest"));
  if(!a.isNew()) {
    CPPUNIT_ASSERT(false);
  }
  a.role(ROLE(ROLE::NONE));
  a.uid(UID("unitTest"));
  a.gender(GENDER(GENDER::MALE));
  a.street(STREET("my street"));
  a.houseNumber(HOUSENUMBER(42));
  a.houseNumberAdd(HOUSENUMBER_ADD("a"));
  a.birthDay(DATE(DAY(9), MONTH(8), YEAR(1972)));
  a.wisaID(WISA_ID(111111111));
  a.password(PASSWORD("ABcd!eGf"));
  a.ssPassword("ABcd!eGf");
  a.cn(CN("unit"));
  a.sn(SN("test"));
  a.birthPlace(BIRTHPLACE("brussels"));
  a.postalCode(POSTAL_CODE("1000"));
  a.city(CITY("brussels"));
  a.country(COUNTRY("belgie"));
  a.mail(MAIL("testunit@sanctamaria-aarschot.be"));
  
  // role is not set!
  if(y::Smartschool().saveUser(a)) {
    CPPUNIT_ASSERT(false);
  }
  
  a.role(ROLE(ROLE::STUDENT));
  if(!y::Smartschool().saveUser(a)) {
    CPPUNIT_ASSERT(false);
  }
  
}

void smartschoolTest::testSendMessage() {
//  const y::ldap::account& account;
//  const string& title;
//  const string& body;
//  y::smartschool _smartschool;
//  bool result = _smartschool.sendMessage(account, title, body);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testSetAccountStatus() {
//  const y::ldap::account& account;
//  y::smartschool _smartschool;
//  bool result = _smartschool.setAccountStatus(account);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testSetCourseStudents() {
//  const string& courseName;
//  const string& courseDescription;
//  const container<string>& classIDs;
//  y::smartschool _smartschool;
//  bool result = _smartschool.setCourseStudents(courseName, courseDescription, classIDs);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testSetCourseTeachers() {
//  const string& courseName;
//  const string& courseDescription;
//  const string& teacher;
//  container<string>* coTeachers;
//  y::smartschool _smartschool;
//  bool result = _smartschool.setCourseTeachers(courseName, courseDescription, teacher, coTeachers);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}

void smartschoolTest::testUnregister() {
//  const y::ldap::account& account;
//  y::smartschool _smartschool;
//  bool result = _smartschool.unregister(account);
//  if (true /*check result*/) {
//    CPPUNIT_ASSERT(false);
//  }
}



