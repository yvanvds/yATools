/* 
 * File:   database.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 7:11 PM
 */

#include "database.h"
#include "sqlserver.h"

y::data::database::database() : handle(y::data::Server().getStatement()) {
  
}

bool y::data::database::use(const std::string& dbName) {
  return handle->execute("USE " + dbName);
}

bool y::data::database::createTable(const std::string& tableName, const row & description) {
  // form query
  sql::SQLString query;
  query.append("CREATE TABLE ");
  query.append(tableName);
  if(description.elms()) query.append(" (");
  for(int i = 0; i < description.elms(); i++) {
    
  }
  // execute
}

bool y::data::database::deleteTable(const std::string& tableName) {
  return handle->execute("DROP TABLE " + tableName);
}


