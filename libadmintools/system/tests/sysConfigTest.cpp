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
  const std::wstring& result = y::utils::Config().getLdapAdminDN();
  if (result.compare(L"cn=admin,dc=domain,dc=com") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapBaseDN() {
  const std::wstring& result = y::utils::Config().getLdapBaseDN();
  if (result.compare(L"dc=domain,dc=com") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapHost() {
  const std::wstring& result = y::utils::Config().getLdapHost();
  if (result.compare(L"ldap://localhost") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapPasswd() {
  const std::wstring& result = y::utils::Config().getLdapPasswd();
  if (result.compare(L"secret") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapTestUID() {
  const std::wstring& result = y::utils::Config().getLdapTestUID();
  if (result.compare(L"testname") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapTestPassword() {
  const std::wstring& result = y::utils::Config().getLdapTestPassword();
  if (result.compare(L"secret2") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapTestUidNumber() {
  const std::wstring& result = y::utils::Config().getLdapTestUidNumber();
  if (result.compare(L"1972") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetLdapTestDN() {
  const std::wstring& result = y::utils::Config().getLdapTestDN();
  if (result.compare(L"uid=user,dc=domain,dc=com") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void sysConfigTest::testGetMysqlPassword() {
  const std::wstring& result = y::utils::Config().getMysqlPassword();
  if (result.compare(L"secret3") != 0) {
    CPPUNIT_ASSERT(false);
  }
}