/*
 * File:   systemProcessTest.cpp
 * Author: yvan
 *
 * Created on May 16, 2014, 10:50:25 AM
 */

#include "systemProcessTest.h"
#include "../process.h"
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(systemProcessTest);

systemProcessTest::systemProcessTest() {
}

systemProcessTest::~systemProcessTest() {
}

void systemProcessTest::setUp() {
}

void systemProcessTest::tearDown() {
}

void systemProcessTest::testArg() {
  y::sys::process _process("ls");
  _process.arg("-al");
  _process.run(y::sys::stdOut);
  if (!_process.success()) {
    CPPUNIT_ASSERT(false);
  }
}

void systemProcessTest::testError() {

}

void systemProcessTest::testProcess() {
  y::sys::process _process("ls");
}

void systemProcessTest::testRun() {

}

void systemProcessTest::testSuccess() {

}

void systemProcessTest::testExec() {
  if(!y::sys::Exec("ls", y::sys::stdOut)) {
    CPPUNIT_ASSERT(false);
  }
}

void systemProcessTest::testStdOut() {

}

