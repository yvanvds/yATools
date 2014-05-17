/*
 * File:   dataDatabaseTest.h
 * Author: yvan
 *
 * Created on May 11, 2014, 4:28:16 PM
 */

#ifndef DATADATABASETEST_H
#define	DATADATABASETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../sqlserver.h"

class dataDatabaseTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(dataDatabaseTest);

  CPPUNIT_TEST(testAddRow);
  CPPUNIT_TEST(testCreateTable);
  CPPUNIT_TEST(testDelRow);
  CPPUNIT_TEST(testDeleteTable);
  CPPUNIT_TEST(testExecute);
  CPPUNIT_TEST(testGetAllRows);
  CPPUNIT_TEST(testGetTables);
  CPPUNIT_TEST(testSetRow);
  CPPUNIT_TEST(testUse);

  CPPUNIT_TEST_SUITE_END();

public:
  dataDatabaseTest();
  virtual ~dataDatabaseTest();
  void setUp();
  void tearDown();

private:
  void testAddRow();
  void testCreateTable();
  void testDelRow();
  void testDeleteTable();
  void testExecute();
  void testGetAllRows();
  void testGetTables();
  void testSetRow();
  void testUse();

  y::data::server server;
};

#endif	/* DATADATABASETEST_H */

