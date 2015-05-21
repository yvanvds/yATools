/*
 * File:   dataDatabaseTest.cpp
 * Author: yvan
 *
 * Created on May 11, 2014, 4:28:16 PM
 */

#include "dataDatabaseTest.h"
#include "../database.h"
#include "utils/config.h"
#include "../dateTime.h"
#include "../field.h"


CPPUNIT_TEST_SUITE_REGISTRATION(dataDatabaseTest);

dataDatabaseTest::dataDatabaseTest() {
  y::utils::Config().load();
}

dataDatabaseTest::~dataDatabaseTest() {
  y::data::database db;
  db.open();
  
  if (db.has("testdb")) {
    db.drop("testdb");
  }
  db.close();
}

void dataDatabaseTest::setUp() {
  y::data::database db;
  db.open();
  
  if (db.has("testdb")) {
    db.drop("testdb");
  }
  db.create("testdb");
  db.close();
}

void dataDatabaseTest::tearDown() {
}

void dataDatabaseTest::testCreate() {
  y::data::database db;
  db.open();
  if(db.has("serverUnitTest")) {
    db.drop("serverUnitTest");
  }
  if (db.has("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  
  db.create("serverUnitTest");
  
  if (!db.has("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  db.drop("serverUnitTest");
  db.close();
}

void dataDatabaseTest::testDrop() {
  y::data::database db;
  db.open();
  if(!db.has("serverUnitTest")) {
    db.create("serverUnitTest");
  }
  if (!db.has("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  db.drop("serverUnitTest");
  if (db.has("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  db.close();
}

void dataDatabaseTest::testHas() {
  y::data::database db;
  db.open();
  db.create("serverUnitTest");
  if (!db.has("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  
  db.drop("serverUnitTest");
  if (db.has("serverUnitTest")) {
    CPPUNIT_ASSERT(false);
  }
  db.close();
}

void dataDatabaseTest::testAddRow() {
  y::data::database db;
  db.open();
  db.use("testdb");

  y::data::row newRow;
  newRow.addInt("ID");
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool("boolvalue").addChar("charvalue").addShort("shortvalue");
  newRow.addInt("intvalue").addLong("longvalue").addFloat("floatvalue");
  newRow.addDouble("doublevalue").addString("stringvalue");
  newRow.addDate("datevalue");
  db.createTable("testtable", newRow);
  
  y::data::row content;
  content.addBool("boolvalue", false);
  content.addChar("charvalue", 34);
  content.addShort("shortvalue", 42);
  content.addInt("intvalue", 535);
  content.addLong("longvalue", 2436089723);
  content.addFloat("floatvalue", 3.14);
  content.addDouble("doublevalue", 5.37347);
  content.addString("stringvalue", "ëç&æ");
  content.addDate("datevalue", y::data::dateTime("1972-08-09 13:06:20"));
  
  db.addRow("testtable", content);
  
  container<y::data::row> results;
  db.getAllRows("testtable", results);
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
  if(result["stringvalue"].asString() != content["stringvalue"].asString()) {
    CPPUNIT_ASSERT(false);
  }
  if(result["datevalue"].asDate().dbFormat() != content["datevalue"].asDate().dbFormat()) {
    CPPUNIT_ASSERT(false);
  }
  
  db.close();
}

void dataDatabaseTest::testCreateTable() {
  y::data::database db;
  db.open();
  db.use("testdb");
  if(db.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }

  y::data::row newRow;
  newRow.addInt("ID", 0);
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString("name", "");
  db.createTable("testtable", newRow);
  if(!db.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  db.close();
}

void dataDatabaseTest::testDelRow() {
  y::data::database db;
  db.open();
  db.use("testdb");

  y::data::row newRow;
  newRow.addInt("ID");
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool("boolvalue").addChar("charvalue").addShort("shortvalue");
  newRow.addInt("intvalue").addLong("longvalue").addFloat("floatvalue");
  newRow.addDouble("doublevalue").addString("stringvalue");
  
  db.createTable("testtable", newRow);
  
  y::data::row content;
  content.addBool("boolvalue", false);
  content.addChar("charvalue", 34);
  content.addShort("shortvalue", 42);
  content.addInt("intvalue", 535);
  content.addLong("longvalue", 2436089723);
  content.addFloat("floatvalue", 3.14);
  content.addDouble("doublevalue", 5.37347);
  content.addString("stringvalue", "ëç&æ");
  db.addRow("testtable", content);
  
  y::data::row content2;
  content2.addBool("boolvalue", true);
  content2.addChar("charvalue", 7);
  content2.addShort("shortvalue", 1);
  content2.addInt("intvalue", 297578);
  content2.addLong("longvalue", 243608972334578);
  content2.addFloat("floatvalue", 3.15);
  content2.addDouble("doublevalue", 73578358.33477347);
  content2.addString("stringvalue", "ëç&æ2");
  db.addRow("testtable", content2);

  y::data::field condition;
  condition.name("shortvalue");
  condition.setShort(1);
  container<y::data::row> results;
  db.getRows("testtable", results, condition);
  if(results.elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  db.delRow("testtable", condition);
  results.clear();
  db.getRows("testtable", results, condition);
  if(results.elms() > 0) {
    CPPUNIT_ASSERT(false);
  }	
  db.close();
}

void dataDatabaseTest::testDeleteTable() {
  y::data::database db;
  db.open();
  db.use("testdb");
  if(db.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  y::data::row newRow;
  newRow.addInt("ID", 0);
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString("name", "");
  db.createTable("testtable", newRow);
  if(!db.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  db.deleteTable("testtable");
  if(db.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  db.close();
}

void dataDatabaseTest::testExecute() {
  y::data::database db;
  db.open();
  db.use("testdb");
  if(db.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  y::data::row newRow;
  newRow.addInt("ID", 0);
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString("name", "");
  db.createTable("testtable", newRow);
  if(!db.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  
  db.execute("DROP TABLE testtable");
  if(db.tableExists("testtable")) {
    CPPUNIT_ASSERT(false);
  }
  db.close();
}

void dataDatabaseTest::testGetAllRows() {
  y::data::database db;
  db.open();
  db.use("testdb");

  if(db.tableExists("testtable")) {
    db.deleteTable("testtable");
  }

  y::data::row newRow;
  newRow.addInt("ID");
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool("boolvalue").addChar("charvalue").addShort("shortvalue");
  newRow.addInt("intvalue").addLong("longvalue").addFloat("floatvalue");
  newRow.addDouble("doublevalue").addString("stringvalue");
  
  db.createTable("testtable", newRow);
  y::data::row content;
  content.addBool("boolvalue", false);
  content.addChar("charvalue", 34);
  content.addShort("shortvalue", 42);
  content.addInt("intvalue", 535);
  content.addLong("longvalue", 2436089723);
  content.addFloat("floatvalue", 3.14);
  content.addDouble("doublevalue", 5.37347);
  content.addString("stringvalue", "ëç&æ");
  db.addRow("testtable", content);
  
  y::data::row content2;
  content2.addBool("boolvalue", true);
  content2.addChar("charvalue", 7);
  content2.addShort("shortvalue", 1);
  content2.addInt("intvalue", 297578);
  content2.addLong("longvalue", 243608972334578);
  content2.addFloat("floatvalue", 3.15);
  content2.addDouble("doublevalue", 73578358.33477347);
  content2.addString("stringvalue", "ëç&æ2");
  db.addRow("testtable", content2);

  y::data::field condition;
  condition.name("shortvalue");
  condition.setShort(1);
  container<y::data::row> results;
  db.getRows("testtable", results, condition);
  
  if(results.elms() != 1) {
    CPPUNIT_ASSERT(false);
  }
  if(results[0]["longvalue"].asLong() != content2["longvalue"].asLong()) {
    CPPUNIT_ASSERT(false);
  }
  db.close();
}

void dataDatabaseTest::testGetTables() {
  y::data::database db;
  db.open();
  db.use("testdb");

  y::data::row newRow;
  newRow.addInt("ID", 0);
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addString("name", "");
  db.createTable("testtable", newRow);
  db.createTable("testtable2", newRow);

  container<string> tables;
  db.getTables(tables);
  if(tables.elms() != 2) {
    CPPUNIT_ASSERT(false);
  }
  if(tables[0] != "testtable") {
    CPPUNIT_ASSERT(false);
  }
  if(tables[1] != "testtable2") {
    CPPUNIT_ASSERT(false);
  }
  db.close();
}

void dataDatabaseTest::testSetRow() {
  y::data::database db;
  db.open();
  db.use("testdb");

  if(db.tableExists("testtable")) {
    db.deleteTable("testtable");
  }

  y::data::row newRow;
  newRow.addInt("ID");
  newRow["ID"].primaryKey(true).autoIncrement(true).required(true);
  newRow.addBool("boolvalue").addChar("charvalue").addShort("shortvalue");
  newRow.addInt("intvalue").addLong("longvalue").addFloat("floatvalue");
  newRow.addDouble("doublevalue").addString("stringvalue");
  
  db.createTable("testtable", newRow);
  y::data::row content;
  content.addBool("boolvalue", false);
  content.addChar("charvalue", 34);
  content.addShort("shortvalue", 42);
  content.addInt("intvalue", 535);
  content.addLong("longvalue", 2436089723);
  content.addFloat("floatvalue", 3.14);
  content.addDouble("doublevalue", 5.37347);
  content.addString("stringvalue", "ëç&æ");
  db.addRow("testtable", content);

  content.clear();
  content.addDouble("doublevalue", 3.004);
  content.addChar("charvalue", 1);

  y::data::field condition;
  condition.name("charvalue");
  condition.setChar(34);
  
  db.setRow("testtable", content, condition);

  condition.name("shortvalue");
  condition.setString("42");
  container<y::data::row> results;
  db.getRows("testtable", results, condition);
  
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
  db.deleteTable("testtable");
  db.close();
}

void dataDatabaseTest::testUse() {
  y::data::database db;
  if(db.use("testdb")) {
    // db is not open!
    CPPUNIT_ASSERT(false);
  }
  db.open();
  if(!db.use("testdb")) {
    CPPUNIT_ASSERT(false);
  }
  if(db.use("doesnotexist")) {
    CPPUNIT_ASSERT(false);
  }
  db.close();
}

