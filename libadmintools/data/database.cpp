/* 
 * File:   database.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 7:11 PM
 */

#include "database.h"
#include "sqlserver.h"
#include "row.h"
#include "../utils/container.h"
#include "../utils/convert.h"
#include "dateTime.h"

y::data::database::database() 
: connection(y::data::Server().getConnection()),
  connected(false){
  handle = std::unique_ptr<sql::Statement>(connection->createStatement());
}

bool y::data::database::use(const std::string& dbName) {
  if(!Server().hasDatabase(dbName)) {
    connected = false;
  } else {
    connection->setSchema(dbName);
    connected = true;
  }
  return connected;
}

bool y::data::database::createTable(const std::string& tableName, row & description) {
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
        query.append(") CHARACTER SET 'utf8' COLLATE 'utf8_unicode_ci'");
        break;
      }
      case DATE_TIME: {
        query.append(" DATETIME ");
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
  std::cout << query << std::endl;
  
  return handle->execute(query);
}

bool y::data::database::deleteTable(const std::string& tableName) {
  if(!connected) return false;
  bool result = false;
  
  try {
    result = handle->execute("DROP TABLE " + tableName);
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  
  return result;
}

bool y::data::database::tableExists(const std::string& tableName) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  
  try {
    result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SHOW TABLES LIKE '" + tableName + "'"));
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
    
  if (result->rowsCount()) return true;
  return false;
}

bool y::data::database::getTables(container<std::string>& tables) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  
  try {
    result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SHOW TABLES"));
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
    
  int i = 0;
  while(result->next()) {
    tables[i++] = result->getString(1);
  }
  if (!result->rowsCount()) return false;
  return true;
}

bool y::data::database::getAllRows(const std::string& table, container<row>& rows) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  
  try {
    result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SELECT * FROM " + table));
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  
  if (!result->rowsCount()) return false;
  
  parseRows(result, rows);
  
  return true;
}

bool y::data::database::getRows(const std::string& table, const std::string& condition, container<row>& rows) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  
  try {
    result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SELECT * FROM " + table + " WHERE " + condition));
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  
  if (!result->rowsCount()) return false;
  
  parseRows(result, rows);
  return true;  
}

void y::data::database::parseRows(std::unique_ptr<sql::ResultSet>& result, container<row>& rows) {
  // NOTE: mysql column indexing is 1-based not zero-based!
  
  sql::ResultSetMetaData * meta = result->getMetaData();
  container<std::string> columnNames;
  container<std::string> columnTypes;
  for(int i = 1; i <= meta->getColumnCount(); i++) {
    columnNames[i-1] = meta->getColumnName(i);
    columnTypes[i-1] = meta->getColumnTypeName(i);
  }
  while(result->next()) {
    row & entry = rows.New();
    for(int i = 0; i < columnNames.elms(); i++) {
      if(columnTypes[i].compare("BIT") == 0) {
        entry.addBool(columnNames[i], result->getBoolean(i+1));
      } else if(columnTypes[i].compare("TINYINT") == 0) {
        entry.addChar(columnNames[i], result->getInt(i+1));
      } else if(columnTypes[i].compare("SMALLINT") == 0) {
        entry.addShort(columnNames[i], result->getInt(i+1));
      } else if(columnTypes[i].compare("INT") == 0) {
        entry.addInt(columnNames[i], result->getInt(i+1));
      } else if(columnTypes[i].compare("BIGINT") == 0) {
        entry.addLong(columnNames[i], result->getInt64(i+1));
      } else if(columnTypes[i].compare("FLOAT") == 0) {
        entry.addFloat(columnNames[i], result->getDouble(i+1));
      } else if(columnTypes[i].compare("DOUBLE") == 0) {
        entry.addDouble(columnNames[i], result->getDouble(i+1));
      } else if(columnTypes[i].compare("CHAR") == 0) {
        entry.addString8(columnNames[i], result->getString(i+1));
      } else if(columnTypes[i].compare("VARCHAR") == 0) {
        entry.addString(columnNames[i], str16(result->getString(i+1)));
      } else if(columnTypes[i].compare("DATETIME") == 0) {
        dateTime d;
        d.dbFormat(result->getString(i+1));
        entry.addDate(columnNames[i], d);
      }
    }
  }
}

bool y::data::database::setRow(const std::string& table, const std::string& condition, row& values){
  if(!connected) return false;
  if(!values.elms()) return false;
  
  sql::SQLString query;
  query.append("UPDATE ");
  query.append(table);
  query.append(" SET ");
  for(int i = 0; i < values.elms(); i++) {
    if(i > 0) query.append(", ");
    query.append(values[i].name());
    query.append("=");
    
    switch(values[i].getType()) {
      case BOOL: {
        if(values[i].asBool()) {
          query.append("b'1'");
        } else {
          query.append("b'0'");
        } 
        break;
      }
      case CHAR: {
        query.append("'");
        query.append(std::to_string(values[i].asChar()));
        query.append("'");
        break;
      }
      case SHORT: {
        query.append("'");
        query.append(std::to_string(values[i].asShort()));
        query.append("'");
        break;
      }
      case INT: {
        query.append("'");
        query.append(std::to_string(values[i].asInt()));
        query.append("'");
        break;
      }
      case LONG: {
        query.append("'");
        query.append(std::to_string(values[i].asLong()));
        query.append("'");
        break;
      }
      case FLOAT: {
        query.append("'");
        query.append(std::to_string(values[i].asFloat()));
        query.append("'");
        break;
      }
      case DOUBLE: {
        query.append("'");
        query.append(std::to_string(values[i].asDouble()));
        query.append("'");
        break;
      }
      case STRING: {
        query.append("'");
        query.append(str8(values[i].asString()));
        query.append("'");
        break;
      }
      case STRING8: {
        query.append("'");
        query.append(values[i].asString8());
        query.append("'");
        break;
      }
      case DATE_TIME: {
        query.append("'");
        query.append(values[i].asDate().dbFormat());
        query.append("'");
        break;
      }
      default: return false;
      
    }
  }
  query.append(" WHERE ");
  query.append(condition);

  try {
    handle->execute(query);
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  return true;
}

bool y::data::database::addRow(const std::string& table, row& values) {
  if(!connected) return false;
  if(!values.elms()) return false;
  
  sql::SQLString query;
  query.append("INSERT INTO ");
  query.append(table);
  query.append(" (");
  for(int i = 0; i < values.elms(); i++) {
    if(i > 0) query.append(", ");
    query.append(values[i].name());
  }
  query.append(") VALUES (");
  for(int i = 0; i < values.elms(); i++) {
    if(i > 0) query.append(", ");
    switch(values[i].getType()) {
      case BOOL: {
        if(values[i].asBool()) {
          query.append("b'1'");
        } else {
          query.append("b'0'");
        }
        break;
      }
      case CHAR: {
        query.append("'");
        query.append(std::to_string(values[i].asChar()));
        query.append("'");
        break;
      }
      case SHORT: {
        query.append("'");
        query.append(std::to_string(values[i].asShort()));
        query.append("'");
        break;
      }
      case INT: {
        query.append("'");
        query.append(std::to_string(values[i].asInt()));
        query.append("'");
        break;
      }
      case LONG: {
        query.append("'");
        query.append(std::to_string(values[i].asLong()));
        query.append("'");
        break;
      }
      case FLOAT: {
        query.append("'");
        query.append(std::to_string(values[i].asFloat()));
        query.append("'");
        break;
      }
      case DOUBLE: {
        query.append("'");
        query.append(std::to_string(values[i].asDouble()));
        query.append("'");
        break;
      }
      case STRING: {
        query.append("'");
        query.append(str8(values[i].asString()));
        query.append("'");
        break;
      }
      case STRING8: {
        query.append("'");
        query.append(values[i].asString8());
        query.append("'");
        break;
      }
      case DATE_TIME: {
        query.append("'");
        query.append(values[i].asDate().dbFormat());
        query.append("'");
        break;
      }
      default: return false;
    }
  }
  query.append(")");
  try {
    handle->execute(query);
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  return true;
}

bool y::data::database::delRow(const std::string& table, const std::string& condition) {
  if(!connected) return false;
  sql::SQLString query = "DELETE FROM " + table + " WHERE " + condition;

  try {
    handle->execute(query);
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  
  return true;
}

bool y::data::database::execute(const std::string& query) {
  if(!connected) return false;
  bool result;
  
  try {
    result = handle->execute(query);
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  return true;
}