/*
 * File:   dataDatabaseTest.cpp
 * Author: yvan
 *
 * Created on May 11, 2014, 4:28:16 PM
 */

#include "dataDatabaseTest.h"
#include "../database.h"
#include "utils/config.h"
#include "data/sqlserver.h"
#include "../dateTime.h"
#include "../field.h"


CPPUNIT_TEST_SUITE_REGISTRATION(dataDatabaseTest);

dataDatabaseTest::dataDatabaseTest() {
  y::utils::Config().load();
  server = std::unique_ptr<y::data::server>(new y::data::server);
}

dataDatabaseTest::~dataDatabaseTest() {
  if (server->hasDatabase(L"testdb")) {
    server->drop(L"testdb");
  }
}

void dataDatabaseTest::setUp() {
  
  
  if (server->hasDatabase(L"testdb")) {
    server->drop(L"testdb");
  }
  server->create(L"testdb");  
}

void dataDatabaseTest::tearDown() {
}

void dataDatabaseTest::testAddRow() {
  y::data::database DB(*server);
  DB.use(L"testdb");

  y::data::row newRow;
  newRow.addInt(L"ID");
  newRow[L"ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool(L"boolvalue").addChar(L"charvalue").addShort(L"shortvalue");
  newRow.addInt(L"intvalue").addLong(L"longvalue").addFloat(L"floatvalue");
  newRow.addDouble(L"doublevalue").addString8(L"string8value").addString(L"stringvalue");
  newRow.addDate(L"datevalue");
  DB.createTable(L"testtable", newRow);
  
  y::data::row content;
  content.addBool(L"boolvalue", false);
  content.addChar(L"charvalue", 34);
  content.addShort(L"shortvalue", 42);
  content.addInt(L"intvalue", 535);
  content.addLong(L"longvalue", 2436089723);
  content.addFloat(L"floatvalue", 3.14);
  content.addDouble(L"doublevalue", 5.37347);
  content.addString8(L"string8value", "name");
  content.addString(L"stringvalue", L"ëç&æ");
  content.addDate(L"datevalue", y::data::dateTime(L"1972-08-09 13:06:20"));
  
  DB.addRow(L"testtable", content);
  
  container<y::data::row> results;
  DB.getAllRows(L"testtable", results);
  if(results.elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  y::data::row & result = results[0];
  
  if(result[L"ID"].asInt() != 1) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"boolvalue"].asBool() != content[L"boolvalue"].asBool()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"charvalue"].asChar() != content[L"charvalue"].asChar()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"shortvalue"].asShort() != content[L"shortvalue"].asShort()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"intvalue"].asInt() != content[L"intvalue"].asInt()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"longvalue"].asLong() != content[L"longvalue"].asLong()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"floatvalue"].asFloat() != content[L"floatvalue"].asFloat()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"doublevalue"].asDouble() != content[L"doublevalue"].asDouble()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"string8value"].asString8() != content[L"string8value"].asString8()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"stringvalue"].asString() != content[L"stringvalue"].asString()) {
    CPPUNIT_ASSERT(false);
  }
  if(result[L"datevalue"].asDate().dbFormat().compare(content[L"datevalue"].asDate().dbFormat())) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testCreateTable() {
  y::data::database DB(*server);
  DB.use(L"testdb");
  if(DB.tableExists(L"testtable")) {
    CPPUNIT_ASSERT(false);
  }

  y::data::row newRow;
  newRow.addInt(L"ID", 0);
  newRow[L"ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString8(L"name", "");
  DB.createTable(L"testtable", newRow);
  if(!DB.tableExists(L"testtable")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testDelRow() {
  y::data::database DB(*server);
  DB.use(L"testdb");

  y::data::row newRow;
  newRow.addInt(L"ID");
  newRow[L"ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool(L"boolvalue").addChar(L"charvalue").addShort(L"shortvalue");
  newRow.addInt(L"intvalue").addLong(L"longvalue").addFloat(L"floatvalue");
  newRow.addDouble(L"doublevalue").addString8(L"string8value").addString(L"stringvalue");
  
  DB.createTable(L"testtable", newRow);
  
  y::data::row content;
  content.addBool(L"boolvalue", false);
  content.addChar(L"charvalue", 34);
  content.addShort(L"shortvalue", 42);
  content.addInt(L"intvalue", 535);
  content.addLong(L"longvalue", 2436089723);
  content.addFloat(L"floatvalue", 3.14);
  content.addDouble(L"doublevalue", 5.37347);
  content.addString8(L"string8value", "name");
  content.addString(L"stringvalue", L"ëç&æ");
  DB.addRow(L"testtable", content);
  
  y::data::row content2;
  content2.addBool(L"boolvalue", true);
  content2.addChar(L"charvalue", 7);
  content2.addShort(L"shortvalue", 1);
  content2.addInt(L"intvalue", 297578);
  content2.addLong(L"longvalue", 243608972334578);
  content2.addFloat(L"floatvalue", 3.15);
  content2.addDouble(L"doublevalue", 73578358.33477347);
  content2.addString8(L"string8value", "name2");
  content2.addString(L"stringvalue", L"ëç&æ2");
  DB.addRow(L"testtable", content2);

  y::data::field condition;
  condition.name(L"shortvalue");
  condition.setShort(1);
  container<y::data::row> results;
  DB.getRows(L"testtable", results, condition);
  if(results.elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  DB.delRow(L"testtable", condition);
  results.clear();
  DB.getRows(L"testtable", results, condition);
  if(results.elms() > 0) {
    CPPUNIT_ASSERT(false);
  }	
}

void dataDatabaseTest::testDeleteTable() {
  y::data::database DB(*server);
  DB.use(L"testdb");
  if(DB.tableExists(L"testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  y::data::row newRow;
  newRow.addInt(L"ID", 0);
  newRow[L"ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString8(L"name", "");
  DB.createTable(L"testtable", newRow);
  if(!DB.tableExists(L"testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  DB.deleteTable(L"testtable");
  if(DB.tableExists(L"testtable")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testExecute() {
  y::data::database DB(*server);
  DB.use(L"testdb");
  if(DB.tableExists(L"testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  y::data::row newRow;
  newRow.addInt(L"ID", 0);
  newRow[L"ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString8(L"name", "");
  DB.createTable(L"testtable", newRow);
  if(!DB.tableExists(L"testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  DB.execute(L"DROP TABLE testtable");
  if(DB.tableExists(L"testtable")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testGetAllRows() {
  y::data::database DB(*server);
  DB.use(L"testdb");

  if(DB.tableExists(L"testtable")) {
    DB.deleteTable(L"testtable");
  }

  y::data::row newRow;
  newRow.addInt(L"ID");
  newRow[L"ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool(L"boolvalue").addChar(L"charvalue").addShort(L"shortvalue");
  newRow.addInt(L"intvalue").addLong(L"longvalue").addFloat(L"floatvalue");
  newRow.addDouble(L"doublevalue").addString8(L"string8value").addString(L"stringvalue");
  
  DB.createTable(L"testtable", newRow);
  y::data::row content;
  content.addBool(L"boolvalue", false);
  content.addChar(L"charvalue", 34);
  content.addShort(L"shortvalue", 42);
  content.addInt(L"intvalue", 535);
  content.addLong(L"longvalue", 2436089723);
  content.addFloat(L"floatvalue", 3.14);
  content.addDouble(L"doublevalue", 5.37347);
  content.addString8(L"string8value", "name");
  content.addString(L"stringvalue", L"ëç&æ");
  DB.addRow(L"testtable", content);
  
  y::data::row content2;
  content2.addBool(L"boolvalue", true);
  content2.addChar(L"charvalue", 7);
  content2.addShort(L"shortvalue", 1);
  content2.addInt(L"intvalue", 297578);
  content2.addLong(L"longvalue", 243608972334578);
  content2.addFloat(L"floatvalue", 3.15);
  content2.addDouble(L"doublevalue", 73578358.33477347);
  content2.addString8(L"string8value", "name2");
  content2.addString(L"stringvalue", L"ëç&æ2");
  DB.addRow(L"testtable", content2);

  y::data::field condition;
  condition.name(L"shortvalue");
  condition.setShort(1);
  container<y::data::row> results;
  DB.getRows(L"testtable", results, condition);
  
  if(results.elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  if(results[0][L"longvalue"].asLong() != content2[L"longvalue"].asLong()) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testGetTables() {
  y::data::database DB(*server);
  DB.use(L"testdb");

  y::data::row newRow;
  newRow.addInt(L"ID", 0);
  newRow[L"ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString8(L"name", "");
  DB.createTable(L"testtable", newRow);
  DB.createTable(L"testtable2", newRow);

  container<std::wstring> tables;
  DB.getTables(tables);
  if(tables.elms() != 2) {
    CPPUNIT_ASSERT(false);
  }
  if(tables[0].compare(L"testtable") != 0) {
    CPPUNIT_ASSERT(false);
  }
  if(tables[1].compare(L"testtable2") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testSetRow() {
  y::data::database DB(*server);
  DB.use(L"testdb");

  if(DB.tableExists(L"testtable")) {
    DB.deleteTable(L"testtable");
  }

  y::data::row newRow;
  newRow.addInt(L"ID");
  newRow[L"ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool(L"boolvalue").addChar(L"charvalue").addShort(L"shortvalue");
  newRow.addInt(L"intvalue").addLong(L"longvalue").addFloat(L"floatvalue");
  newRow.addDouble(L"doublevalue").addString8(L"string8value").addString(L"stringvalue");
  
  DB.createTable(L"testtable", newRow);
  y::data::row content;
  content.addBool(L"boolvalue", false);
  content.addChar(L"charvalue", 34);
  content.addShort(L"shortvalue", 42);
  content.addInt(L"intvalue", 535);
  content.addLong(L"longvalue", 2436089723);
  content.addFloat(L"floatvalue", 3.14);
  content.addDouble(L"doublevalue", 5.37347);
  content.addString8(L"string8value", "name");
  content.addString(L"stringvalue", L"ëç&æ");
  DB.addRow(L"testtable", content);

  content.clear();
  content.addDouble(L"doublevalue", 3.004);
  content.addChar(L"charvalue", 1);

  y::data::field condition;
  condition.name(L"charvalue");
  condition.setChar(34);
  
  DB.setRow(L"testtable", content, condition);

  condition.name(L"shortvalue");
  condition.setString8("42");
  container<y::data::row> results;
  DB.getRows(L"testtable", results, condition);
  
  if(!results.elms()) {
    CPPUNIT_ASSERT(false);
  }
  y::data::row & result = results[0];
  if(result[L"doublevalue"].asDouble() != content[L"doublevalue"].asDouble()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result[L"charvalue"].asChar() != content[L"charvalue"].asChar()) {
    CPPUNIT_ASSERT(false);
  }
  DB.deleteTable(L"testtable");
}

void dataDatabaseTest::testUse() {
  y::data::database DB(*server);
  if(!DB.use(L"testdb")) {
    CPPUNIT_ASSERT(false);
  }
  if(DB.use(L"doesnotexist")) {
    CPPUNIT_ASSERT(false);
  }
  
}

