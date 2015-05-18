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
                   "--ldapTestUID",
                   "testname",
                   "--ldapTestPassword",
                   "secret2",
                   "--ldapTestUIDNumber",
                   "1972",
                   "--ldapTestDN",
                   "uid=user,dc=domain,dc=com",
                   "--mysqlRootPassword",
                   "secret3",
                   nullptr};
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
  const string& result = y::utils::Config().getLdapAdminDN();
  if (result != "cn=admin,dc=domain,dc=com") {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapBaseDN() {
  const string& result = y::utils::Config().getLdapBaseDN();
  if (result != "dc=domain,dc=com") {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapHost() {
  const string& result = y::utils::Config().getLdapHost();
  if (result != "ldap://localhost") {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapPasswd() {
  const string& result = y::utils::Config().getLdapPasswd();
  if (result != "secret") {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapTestUID() {
  const string& result = y::utils::Config().getLdapTestUID();
  if (result != "testname") {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapTestPassword() {
  const string& result = y::utils::Config().getLdapTestPassword();
  if (result != "secret2") {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapTestUidNumber() {
  const string& result = y::utils::Config().getLdapTestUidNumber();
  if (result != "1972") {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapTestDN() {
  const string& result = y::utils::Config().getLdapTestDN();
  if (result != "uid=user,dc=domain,dc=com") {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetMysqlPassword() {
  const string& result = y::utils::Config().getMysqlPassword();
  if (result != "secret3") {
    CPPUNIT_ASSERT(false);
  }
}