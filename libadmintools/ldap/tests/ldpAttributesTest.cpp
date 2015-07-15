/*
 * File:   ldpAttributesTest.cpp
 * Author: yvan
 *
 * Created on May 5, 2014, 10:45:54 PM
 */

#include "../attributes.h"
#include "ldpAttributesTest.h"



CPPUNIT_TEST_SUITE_REGISTRATION(ldpAttributesTest);

ldpAttributesTest::ldpAttributesTest() {
}

ldpAttributesTest::~ldpAttributesTest() {
}

void ldpAttributesTest::setUp() {
}

void ldpAttributesTest::tearDown() {
}

void ldpAttributesTest::testDN() {
  DN item1("cn=name,dc=domain,dc=com");
  DN item2("cn=name,dc=domain,dc=com");
  DN item3("cn=name2,dc=domain,dc=com");
  
  // test if we can get the string back
  if(item1.get() != "cn=name,dc=domain,dc=com") {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}

void ldpAttributesTest::testUID_NUMBER() {
  UID_NUMBER item1(300);
  UID_NUMBER item2(300);
  UID_NUMBER item3(301);
  
  // test if we can get an int back
  if(item1.get() != 300) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}
void ldpAttributesTest::testUID() {
  UID item1("user1");
  UID item2("user1");
  UID item3("user2");
  
  // test if we can get the string back
  if(item1.get() != "user1") {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}


void ldpAttributesTest::testFULL_NAME() {
  FULL_NAME item1("yvan vander sanden");
  FULL_NAME item2("yvan vander sanden");
  FULL_NAME item3("firstname surname");
  
  // test if we can get the string back
  if(item1.get() != "yvan vander sanden") {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  } 
  
  FULL_NAME item4("yvan", "vander sanden");
  if(item2 != item4) {
    CPPUNIT_ASSERT(false);
  }
}
void ldpAttributesTest::testGID() {
  ROLE item1(ROLE::ADMIN);
  ROLE item2(ROLE::ADMIN);
  ROLE item3(ROLE::SUPPORT);
  
  // test if we can get the value back
  if(item1.get() != ROLE::ADMIN) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }  
}
void ldpAttributesTest::testGID_NUMBER() {
  GID_NUMBER item1(300);
  GID_NUMBER item2(300);
  GID_NUMBER item3(301);
  
  // test if we can get an int back
  if(item1.get() != 300) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}
void ldpAttributesTest::testWISA_ID() {
  WISA_ID item1(300);
  WISA_ID item2(300);
  WISA_ID item3(301);
  
  // test if we can get an int back
  if(item1.get() != 300) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}
void ldpAttributesTest::testMAIL() {
  MAIL item1("user1@gmail.com");
  MAIL item2("user1@gmail.com");
  MAIL item3("user2@gmail.com");
  
  // test if we can get the string back
  if(item1.get() != "user1@gmail.com") {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}
void ldpAttributesTest::testPASSWORD() {
  PASSWORD item1("secret1");
  PASSWORD item2("secret1");
  PASSWORD item3("secret2");
  
  // test if we can get the string back
  if(item1.get() != "secret1") {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}
void ldpAttributesTest::testDAY() {
  DAY item1(1);
  DAY item2(1);
  DAY item3(31);
  
  // test if we can get an int back
  if(item1.get() != 1) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }  
  
  // test wrong day values
  DAY item4(0);
  DAY item5(-20);
  DAY item6(32);

  if(item4.get() != 1) {
    CPPUNIT_ASSERT(false);
  }

  if(item5.get() != 1) {
    CPPUNIT_ASSERT(false);
  }

  if(item6.get() != 31) {
    CPPUNIT_ASSERT(false);
  }
}


void ldpAttributesTest::testMONTH() {
  MONTH item1(1);
  MONTH item2(1);
  MONTH item3(12);
  
  // test if we can get an int back
  if(item1.get() != 1) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }  
  
  // test wrong month values
  MONTH item4(0);
  MONTH item5(-20);
  MONTH item6(13);

  if(item4.get() != 1) {
    CPPUNIT_ASSERT(false);
  }

  if(item5.get() != 1) {
    CPPUNIT_ASSERT(false);
  }

  if(item6.get() != 12) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpAttributesTest::testYEAR() {
  YEAR item1(1980);
  YEAR item2(1980);
  YEAR item3(2001);
  
  // test if we can get an int back
  if(item1.get() != 1980) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }  
}

void ldpAttributesTest::testDATE() {
  DATE item1(DAY(2), MONTH(4), YEAR(1980));
  DATE item2(DAY(2), MONTH(4), YEAR(1980));
  DATE item3(DAY(2), MONTH(5), YEAR(1980));
  
  // test if we can get an int back
  if(item1.asInt() != 19800402) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }  
  
  if(item2.get() != "2 april 1980") {
    CPPUNIT_ASSERT(false);
  }
  
  if(item2.getDay() != 2) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item2.getMonth() != 4) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item2.getYear() != 1980) {
    CPPUNIT_ASSERT(false);
  }
  
  // test for ldap date conversion
  item1 = DATE("19720809");
   if(item1.getDay() != 9) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1.getMonth() != 8) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1.getYear() != 1972) {
    CPPUNIT_ASSERT(false);
  } 
  
  // test wisa conversion
  item1 = DATE("9/8/1972", true);
  std::cout << item1.get() << std::endl;
  if(item1.getDay() != 9) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1.getMonth() != 8) {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1.getYear() != 1972) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpAttributesTest::testHOMEDIR() {
  HOMEDIR item1("/home/user1");
  HOMEDIR item2("/home/user1");
  HOMEDIR item3("/home/user2");
  
  // test if we can get the string back
  if(item1.get() != "/home/user1") {
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 != item2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(item1 == item3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  item1 = item3;
  if(item1 != item3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}
