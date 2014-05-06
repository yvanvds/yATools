/*
 * File:   sysConfigTest.cpp
 * Author: yvan
 *
 * Created on May 6, 2014, 9:06:27 PM
 */

#include "sysConfigTest.h"
#include "../../utils/config.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sysConfigTest);

sysConfigTest::sysConfigTest() {
  // fake config values for testing
  char * argv[] = {"test", 
                   "--ldapPasswd",
                   "secret",
                   "--ldapHost",
                   "ldap://localhost",
                   "--ldapBaseDN",
                   "dc=domain,dc=com",
                   "--ldapAdminDN",
                   "cn=admin,dc=domain,dc=com",
                   NULL};
  int argc = sizeof(argv) / sizeof(char*) - 1;
  y::utils::Config().load(argc, argv);
}

sysConfigTest::~sysConfigTest() {
}

void sysConfigTest::setUp() {
  
}

void sysConfigTest::tearDown() {
}


void sysConfigTest::testGetLdapAdminDN() {
  const std::string& result = y::utils::Config().getLdapAdminDN();
  if (result.compare("cn=admin,dc=domain,dc=com") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapBaseDN() {
  const std::string& result = y::utils::Config().getLdapBaseDN();
  if (result.compare("dc=domain,dc=com") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapHost() {
  const std::string& result = y::utils::Config().getLdapHost();
  if (result.compare("ldap://localhost") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapPasswd() {
  const std::string& result = y::utils::Config().getLdapPasswd();
  if (result.compare("secret") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

