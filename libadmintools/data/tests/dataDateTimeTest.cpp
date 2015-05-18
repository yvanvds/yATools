/*
 * File:   dataDateTimeTest.cpp
 * Author: yvan
 *
 * Created on May 14, 2014, 9:53:36 PM
 */

#include "dataDateTimeTest.h"
#include "../dateTime.h"


CPPUNIT_TEST_SUITE_REGISTRATION(dataDateTimeTest);

dataDateTimeTest::dataDateTimeTest() {
}

dataDateTimeTest::~dataDateTimeTest() {
}

void dataDateTimeTest::setUp() {
}

void dataDateTimeTest::tearDown() {
}

void dataDateTimeTest::testDbFormat() {
  y::data::dateTime d;
  d.day(1);
  d.month(11);
  d.year(1938);
  d.hours(9);
  d.minutes(12);
  d.seconds(3);
  string result = d.dbFormat();
  if (result != "1938-11-01 09:12:03") {
    CPPUNIT_ASSERT(false);
  }
}

void dataDateTimeTest::testDbFormat2() {
  y::data::dateTime d;
  d.dbFormat("1938-11-01 09:12:03");
  
  if (d.day() != 1) {
    CPPUNIT_ASSERT(false);
  }
  if (d.month() != 11) {
    CPPUNIT_ASSERT(false);
  }
  if (d.year() != 1938) {
    CPPUNIT_ASSERT(false);
  }
  if (d.hours() != 9) {
    CPPUNIT_ASSERT(false);
  }
  if (d.minutes() != 12) {
    CPPUNIT_ASSERT(false);
  }
  if (d.seconds() != 3) {
    CPPUNIT_ASSERT(false);
  }
}

