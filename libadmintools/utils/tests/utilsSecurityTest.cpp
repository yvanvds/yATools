/*
 * File:   utilsSecurityTest.cpp
 * Author: yvan
 *
 * Created on May 8, 2014, 4:46:30 PM
 */

#include "utilsSecurityTest.h"
#include "../security.h"
#include "utils/config.h"
#include "ldap/server.h"


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
  y::ldap::UID uid(y::utils::Config().getLdapTestUID());
  
  y::ldap::account & acc = y::ldap::Server().getAccount(uid);
  
  const std::string & password = y::utils::Config().getLdapTestPassword();
  
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

