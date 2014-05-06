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
  y::ldap::DN dn("cn=name,dc=domain,dc=com");
  y::ldap::DN dn2("cn=name,dc=domain,dc=com");
  y::ldap::DN dn3("cn=name2,dc=domain,dc=com");
  
  // test if we can get the string back
  if(dn().compare("cn=name,dc=domain,dc=com") != 0) {
    CPPUNIT_ASSERT(false);
  }
  
  if(dn != dn2) { // should be equal
    CPPUNIT_ASSERT(false);
  }
  
  if(dn == dn3) { // should be different
    CPPUNIT_ASSERT(false);
  }
  
  dn = dn3;
  if(dn != dn3) { // should be equal
    CPPUNIT_ASSERT(false);
  }
}

void ldpAttributesTest::testFULL_NAME() {

}

void ldpAttributesTest::testAsString() {

}

void ldpAttributesTest::testGetDay() {

}

void ldpAttributesTest::testGetMonth() {

}

void ldpAttributesTest::testGetYear() {

}

