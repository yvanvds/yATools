/*
 * File:   ldapServerTest.cpp
 * Author: yvan
 *
 * Created on May 6, 2014, 10:44:36 PM
 */

#include "ldapServerTest.h"
#include "../server.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ldapServerTest);

ldapServerTest::ldapServerTest() {
}

ldapServerTest::~ldapServerTest() {
}

void ldapServerTest::setUp() {
  y::ldap::Server().getAccount(y::ldap::UID("yvan"));
}

void ldapServerTest::tearDown() {
}

void ldapServerTest::testCommitChanges() {

}

void ldapServerTest::testGetAccount() {

}

void ldapServerTest::testGetAccount2() {

}

void ldapServerTest::testGetAccount3() {

}

void ldapServerTest::testGetAccounts() {

}

void ldapServerTest::testGetGroup() {

}

void ldapServerTest::testGetGroup2() {

}

void ldapServerTest::testGetGroups() {

}

