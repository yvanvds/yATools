/* 
 * File:   database.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 7:11 PM
 */

#include "database.h"
#include "sqlserver.h"
#include "row.h"

y::data::database::database() 
: handle(y::data::Server().getStatement()),
  connected(false){
  
}

bool y::data::database::use(const std::string& dbName) {
  connected = handle->execute("USE " + dbName);
  return connected;
}

bool y::data::database::createTable(const std::string& tableName, const row & description) {
  // check if we're in a database
  if (!connected) return false;
  
  // don't create an empty table
  if (!description.elms()) return false;
  
  // there should be exactly one primary key
  int key = 0;
  for (int i = 0; i < description.elms(); i++) {
    if(description[i].primaryKey()) key++;
  }
  if (key != 1) {
    return false;
  }
  
  // form query
  sql::SQLString query;
  query.append("CREATE TABLE ");
  query.append(tableName);
  query.append(" (");
  for(int i = 0; i < description.elms(); i++) {
    // add comma
    if(i>0) query.append(", ");
    
    // add field name
    query.append(description[i].name());
    
    // add field type
    switch(description[i].getType()) {
      case BOOL: {
        query.append(" BIT(1) "); break;
      }
      case CHAR: {
        query.append(" TINYINT "); break;
      }
      case SHORT: {
        query.append(" SMALLINT "); break;
      }
      case INT: {
        query.append(" INT "); break;
      }
      case LONG: {
        query.append(" BIGINT "); break;
      }
      case FLOAT: {
        query.append(" FLOAT "); break;
      }
      case DOUBLE: {
        query.append(" DOUBLE "); break;
      }
      case STRING8: {
        query.append(" CHAR(");
        query.append(std::to_string(description[i].stringLength()));
        query.append(") ");
        break;
      }
      case STRING: {
        query.append(" VARCHAR(");
        query.append(std::to_string(description[i].stringLength()));
        query.append(") ");
        break;
      }
      case UNKNOWN: {
        return false;
      }      
    }
    
    // add if required
    if(description[i].required()) {
      query.append(" NOT NULL ");
    }
    
    // add auto increment
    if(description[i].autoIncrement()) {
      query.append(" AUTO_INCREMENT ");
    }
    
    // add primary key
    if(description[i].primaryKey()) {
      query.append(" PRIMARY KEY ");
    }
  }
  
  query.append(")");
  // execute
  return handle->execute(query);
}

bool y::data::database::deleteTable(const std::string& tableName) {
  if(!connected) return false;
  return handle->execute("DROP TABLE " + tableName);
}

bool y::data::database::tableExists(const std::string& tableName) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SHOW TABLES LIKE '" + tableName + "'"));
  if (result->rowsCount()) return true;
  return false;
}

bool y::data::database::getTables(container<std::string>& tables) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SHOW TABLES"));
  for(int i = 0; i < result->rowsCount(); i++) {
    // todo
  }
  if (!result->rowsCount()) return false;
  return true;
}

bool y::data::database::getAllRows(const std::string& table, container<row>& rows) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SELECT * FROM " + table));
  for(int i = 0; i < result->rowsCount(); i++) {
    // todo
  }
  if (!result->rowsCount()) return false;
  return true;
}

bool y::data::database::getRows(const std::string& table, const std::string& condition, container<row>& rows) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SELECT " + condition + " FROM " + table));
  for(int i = 0; i < result->rowsCount(); i++) {
    // todo
  }
  if (!result->rowsCount()) return false;
  return true;  
}

bool y::data::database::setRow(const std::string& table, const std::string& condition, const row& values){
  if(!connected) return false;
}

bool y::data::database::addRow(const std::string& table, const row& values) {
  if(!connected) return false;
}

bool y::data::database::delRow(const std::string& table, const std::string& condition) {
  if(!connected) return false;
  return handle->execute("DELETE FROM " + table + " WHERE " + condition);
}

bool y::data::database::execute(const std::string& query) {
  if(!connected) return false;
  return handle->execute(query);
}