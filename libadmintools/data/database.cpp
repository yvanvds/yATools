/* 
 * File:   database.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 7:11 PM
 */

#include "database.h"
#include "sqlserver.h"
#include "row.h"

y::data::database::database() : handle(y::data::Server().getStatement()) {
  
}

bool y::data::database::use(const std::string& dbName) {
  return handle->execute("USE " + dbName);
}

bool y::data::database::createTable(const std::string& tableName, const row & description) {
  // don't create an empty table
  if (!description.elms()) return false;
  
  // form query
  sql::SQLString query;
  query.append("CREATE TABLE ");
  query.append(tableName);
  query.append(" (");
  for(int i = 0; i < description.elms(); i++) {
    query.append(description[i].name());
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
    }
  }
  // execute
}

bool y::data::database::deleteTable(const std::string& tableName) {
  return handle->execute("DROP TABLE " + tableName);
}


