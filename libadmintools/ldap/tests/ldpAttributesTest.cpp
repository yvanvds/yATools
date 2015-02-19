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
  y::ldap::DN item1(L"cn=name,dc=domain,dc=com");
  y::ldap::DN item2(L"cn=name,dc=domain,dc=com");
  y::ldap::DN item3(L"cn=name2,dc=domain,dc=com");
  
  // test if we can get the string back
  if(item1().compare(L"cn=name,dc=domain,dc=com") != 0) {
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
  y::ldap::UID_NUMBER item1(300);
  y::ldap::UID_NUMBER item2(300);
  y::ldap::UID_NUMBER item3(301);
  
  // test if we can get an int back
  if(item1() != 300) {
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
  y::ldap::UID item1(L"user1");
  y::ldap::UID item2(L"user1");
  y::ldap::UID item3(L"user2");
  
  // test if we can get the string back
  if(item1().compare(L"user1") != 0) {
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
void ldpAttributesTest::testCN() {
  y::ldap::CN item1(L"user1");
  y::ldap::CN item2(L"user1");
  y::ldap::CN item3(L"user2");
  
  // test if we can get the string back
  if(item1().compare(L"user1") != 0) {
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
void ldpAttributesTest::testSN() {
  y::ldap::SN item1(L"user1");
  y::ldap::SN item2(L"user1");
  y::ldap::SN item3(L"user2");
  
  // test if we can get the string back
  if(item1().compare(L"user1") != 0) {
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
  y::ldap::FULL_NAME item1(L"yvan vander sanden");
  y::ldap::FULL_NAME item2(L"yvan vander sanden");
  y::ldap::FULL_NAME item3(L"firstname surname");
  
  // test if we can get the string back
  if(item1().compare(L"yvan vander sanden") != 0) {
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
  
  y::ldap::FULL_NAME item4(y::ldap::CN(L"yvan"), y::ldap::SN(L"vander sanden"));
  if(item2 != item4) {
    CPPUNIT_ASSERT(false);
  }
}
void ldpAttributesTest::testGID() {
  y::ldap::GID item1(L"group1");
  y::ldap::GID item2(L"group1");
  y::ldap::GID item3(L"group2");
  
  // test if we can get the string back
  if(item1().compare(L"group1") != 0) {
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
  y::ldap::GID_NUMBER item1(300);
  y::ldap::GID_NUMBER item2(300);
  y::ldap::GID_NUMBER item3(301);
  
  // test if we can get an int back
  if(item1() != 300) {
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
  y::ldap::WISA_ID item1(300);
  y::ldap::WISA_ID item2(300);
  y::ldap::WISA_ID item3(301);
  
  // test if we can get an int back
  if(item1() != 300) {
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
  y::ldap::MAIL item1(L"user1@gmail.com");
  y::ldap::MAIL item2(L"user1@gmail.com");
  y::ldap::MAIL item3(L"user2@gmail.com");
  
  // test if we can get the string back
  if(item1().compare(L"user1@gmail.com") != 0) {
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
  y::ldap::PASSWORD item1(L"secret1");
  y::ldap::PASSWORD item2(L"secret1");
  y::ldap::PASSWORD item3(L"secret2");
  
  // test if we can get the string back
  if(item1().compare(L"secret1") != 0) {
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
  y::ldap::DAY item1(1);
  y::ldap::DAY item2(1);
  y::ldap::DAY item3(31);
  
  // test if we can get an int back
  if(item1() != 1) {
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
  y::ldap::DAY item4(0);
  y::ldap::DAY item5(-20);
  y::ldap::DAY item6(32);

  if(item4() != 1) {
    CPPUNIT_ASSERT(false);
  }

  if(item5() != 1) {
    CPPUNIT_ASSERT(false);
  }

  if(item6() != 31) {
    CPPUNIT_ASSERT(false);
  }
}


void ldpAttributesTest::testMONTH() {
  y::ldap::MONTH item1(1);
  y::ldap::MONTH item2(1);
  y::ldap::MONTH item3(12);
  
  // test if we can get an int back
  if(item1() != 1) {
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
  y::ldap::MONTH item4(0);
  y::ldap::MONTH item5(-20);
  y::ldap::MONTH item6(13);

  if(item4() != 1) {
    CPPUNIT_ASSERT(false);
  }

  if(item5() != 1) {
    CPPUNIT_ASSERT(false);
  }

  if(item6() != 12) {
    CPPUNIT_ASSERT(false);
  }
}

void ldpAttributesTest::testYEAR() {
  y::ldap::YEAR item1(1980);
  y::ldap::YEAR item2(1980);
  y::ldap::YEAR item3(2001);
  
  // test if we can get an int back
  if(item1() != 1980) {
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
  y::ldap::DATE item1(y::ldap::DAY(2), y::ldap::MONTH(4), y::ldap::YEAR(1980));
  y::ldap::DATE item2(y::ldap::DAY(2), y::ldap::MONTH(4), y::ldap::YEAR(1980));
  y::ldap::DATE item3(y::ldap::DAY(2), y::ldap::MONTH(5), y::ldap::YEAR(1980));
  
  // test if we can get an int back
  if(item1() != 19800402) {
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
  
  if(item2.asString().compare(L"2 april 1980") != 0) {
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
  item1 = y::ldap::DATE(L"19720809");
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
  y::ldap::HOMEDIR item1(L"/home/user1");
  y::ldap::HOMEDIR item2(L"/home/user1");
  y::ldap::HOMEDIR item3(L"/home/user2");
  
  // test if we can get the string back
  if(item1().compare(L"/home/user1") != 0) {
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
