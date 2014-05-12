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
  
  y::data::row content2;
  content2.addBool("boolvalue", true);
  content2.addChar("charvalue", 7);
  content2.addShort("shortvalue", 1);
  content2.addInt("intvalue", 297578);
  content2.addLong("longvalue", 243608972334578);
  content2.addFloat("floatvalue", 3.15);
  content2.addDouble("doublevalue", 73578358.33477347);
  content2.addString8("string8value", "name2");
  content2.addString("stringvalue", u"ëç&æ2");
  DB.addRow("testtable", content2);

  container<y::data::row> results;
  DB.getRows("testtable", "shortvalue=1", results);
  if(results.elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  DB.delRow("testtable", "shortvalue=1");
  results.clear();
  DB.getRows("testtable", "shortvalue=1", results);
  if(results.elms() > 0) {
    CPPUNIT_ASSERT(false);
  }	
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
  
  DB.execute("DROP TABLE testtable");
  if(DB.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
}

void dataDatabaseTest::testGetAllRows() {
  y::data::database DB;
  DB.use("testdb");

  if(DB.tableExists("testtable")) {
    DB.deleteTable("testtable");
  }

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
  
  y::data::row content2;
  content2.addBool("boolvalue", true);
  content2.addChar("charvalue", 7);
  content2.addShort("shortvalue", 1);
  content2.addInt("intvalue", 297578);
  content2.addLong("longvalue", 243608972334578);
  content2.addFloat("floatvalue", 3.15);
  content2.addDouble("doublevalue", 73578358.33477347);
  content2.addString8("string8value", "name2");
  content2.addString("stringvalue", u"ëç&æ2");
  DB.addRow("testtable", content2);

  container<y::data::row> results;
  DB.getRows("testtable", "shortvalue=1", results);
  if(results.elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  if(results[0]["longvalue"].asLong() != content2["longvalue"].asLong()) {
    CPPUNIT_ASSERT(false);
  }
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
  y::data::database DB;
  DB.use("testdb");

  if(DB.tableExists("testtable")) {
    DB.deleteTable("testtable");
  }

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

  content.clear();
  content.addDouble("doublevalue", 3.004);
  content.addChar("charvalue", 1);

  DB.setRow("testtable", "charvalue=34", content);

  container<y::data::row> results;
  DB.getRows("testtable", "shortvalue=42", results);
  
  if(!results.elms()) {
    CPPUNIT_ASSERT(false);
  }
  y::data::row & result = results[0];
  if(result["doublevalue"].asDouble() != content["doublevalue"].asDouble()) {
    CPPUNIT_ASSERT(false);
  }
  
  if(result["charvalue"].asChar() != content["charvalue"].asChar()) {
    CPPUNIT_ASSERT(false);
  }
  DB.deleteTable("testtable");
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

