/*
 * File:   utilsSecurityTest.cpp
 * Author: yvan
 *
 * Created on May 8, 2014, 4:46:30 PM
 */

#include "utilsSecurityTest.h"
#include "../security.h"
#include "utils/config.h"
#include "utils/convert.h"
#include "ldap/server.h"

using namespace y::utils;

CPPUNIT_TEST_SUITE_REGISTRATION(utilsSecurityTest);

utilsSecurityTest::utilsSecurityTest() {
}

utilsSecurityTest::~utilsSecurityTest() {
}

void utilsSecurityTest::setUp() {
  y::utils::Config().load();
}

void utilsSecurityTest::tearDown() {
}

void utilsSecurityTest::testTest() {
  return; // TODO this test is outdated
  y::ldap::UID uid(y::utils::Config().getLdapTestUID());
  
  y::ldap::account & acc = y::ldap::Server().getAccount(uid);
  
  const std::string & password = str8(y::utils::Config().getLdapTestPassword());
  
  bool result = y::utils::Security().test(acc, password);
  if (!result) {
    CPPUNIT_ASSERT(false);
  }
  const std::string wrongpassword = "abcd";
  result = y::utils::Security().test(acc, wrongpassword);
  if (result) {
    CPPUNIT_ASSERT(false);
  }
}

void utilsSecurityTest::testGoodPassword() {
  if(Security().isGoodPassword("abc") != false) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("abcdefgh") != false) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("abcdeAgh") != false) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("abdc(dlej") != false) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("abcd!0dn") != false) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("p2sSw@rd#l0ngErThisIs2l0ng") != false) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("abc123DEF") != true) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("AJwlje346") != true) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("p2sSw@rd") != true) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("abc#$%GH1") != true) {
    CPPUNIT_ASSERT(false);
  }
  if(Security().isGoodPassword("p2sSw@rd#l0ngEr") != true) {
    CPPUNIT_ASSERT(false);
  }
}

