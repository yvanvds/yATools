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


CPPUNIT_TEST_SUITE_REGISTRATION(dataDatabaseTest);

dataDatabaseTest::dataDatabaseTest() {
}

dataDatabaseTest::~dataDatabaseTest() {
  if (y::data::Server().hasDatabase("testdb")) {
    y::data::Server().drop("testdb");
  }
}

void dataDatabaseTest::setUp() {
  y::utils::Config().load();
  
  if (y::data::Server().hasDatabase("testdb")) {
    y::data::Server().drop("testdb");
  }
  y::data::Server().create("testdb");  
}

void dataDatabaseTest::tearDown() {
}

void dataDatabaseTest::testAddRow() {
  y::data::database DB;
  DB.use("testdb");

  y::data::row newRow;
  newRow.addInt("ID");
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool("boolvalue").addChar("charvalue").addShort("shortvalue");
  newRow.addInt("intvalue").addLong("longvalue").addFloat("floatvalue");
  newRow.addDouble("doublevalue").addString8("string8value").addString("stringvalue");
  
  DB.createTable("testtable", newRow);
  
  y::data::row content;
  content.addBool("boolvalue", false);
  content.addChar("charvalue", 34);
  content.addShort("shortvalue", 42);
  content.addInt("intvalue", 535);
  content.addLong("longvalue", 2436089723);
  content.addFloat("floatvalue", 3.14);
  content.addDouble("doublevalue", 5.37347);
  content.addString8("string8value", "name");
  content.addString("stringvalue", u"ëç&æ");
  DB.addRow("testtable", content);
  
  container<y::data::row> results;
  DB.getAllRows("testtable", results);
  if(results.elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  y::data::row & result = results[0];
  
  for(int i = 0; i < result.elms(); i++) {
    result[i].print();
  }
  
  if(result["ID"].asInt() != 1) {
    CPPUNIT_ASSERT(false);
  }
  if(result["boolvalue"].asBool() != content["boolvalue"].asBool()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["charvalue"].asChar() != content["charvalue"].asChar()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["shortvalue"].asShort() != content["shortvalue"].asShort()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["intvalue"].asInt() != content["intvalue"].asInt()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["longvalue"].asLong() != content["longvalue"].asLong()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["floatvalue"].asFloat() != content["floatvalue"].asFloat()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["doublevalue"].asDouble() != content["doublevalue"].asDouble()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["string8value"].asString8() != content["string8value"].asString8()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["stringvalue"].asString() != content["stringvalue"].asString()) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testCreateTable() {
  y::data::database DB;
  DB.use("testdb");
  if(DB.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }

  y::data::row newRow;
  newRow.addInt("ID", 0);
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString8("name", "");
  DB.createTable("testtable", newRow);
  if(!DB.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testDelRow() {

}

void dataDatabaseTest::testDeleteTable() {
  y::data::database DB;
  DB.use("testdb");
  if(DB.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  y::data::row newRow;
  newRow.addInt("ID", 0);
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString8("name", "");
  DB.createTable("testtable", newRow);
  if(!DB.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  DB.deleteTable("testtable");
  if(DB.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testExecute() {

}

void dataDatabaseTest::testGetAllRows() {

}

void dataDatabaseTest::testGetRows() {

}

void dataDatabaseTest::testGetTables() {
  y::data::database DB;
  DB.use("testdb");

  y::data::row newRow;
  newRow.addInt("ID", 0);
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString8("name", "");
  DB.createTable("testtable", newRow);
  DB.createTable("testtable2", newRow);

  container<std::string> tables;
  DB.getTables(tables);
  if(tables.elms() != 2) {
    CPPUNIT_ASSERT(false);
  }
  if(tables[0].compare("testtable") != 0) {
    CPPUNIT_ASSERT(false);
  }
  if(tables[1].compare("testtable2") != 0) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testSetRow() {

}

void dataDatabaseTest::testUse() {
  y::data::database DB;
  if(!DB.use("testdb")) {
    CPPUNIT_ASSERT(false);
  }
  if(DB.use("doesnotexist")) {
    CPPUNIT_ASSERT(false);
  }
  
}

