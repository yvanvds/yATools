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
#include "field.h"

y::data::database::database(y::data::server & serverObject) : serverObject(serverObject)
, connection(serverObject.getConnection()),
  connected(false){
  handle = std::unique_ptr<sql::Statement>(connection->createStatement());
}

bool y::data::database::use(const std::string& dbName) {
  if(!serverObject.hasDatabase(dbName)) {
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
      case UID: {
        // not implemented yet
        break;
      }
      case BINARY: {
        // not implemented yet
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

bool y::data::database::getRows(const std::string & table, container<row> & rows, field & condition, COMPARE c) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  
  std::string query;
  query = "SELECT * FROM " + table + " WHERE ";
  query.append(condition.name());
  switch(c) {
    case COMPARE::equal: 
      query.append("="); break;
  }
  query.append("?");

  STATEMENT(statement, query);
  addToStatement(statement, condition, 1);
  
  try {
    result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
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
  for(unsigned int i = 1; i <= meta->getColumnCount(); i++) {
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

bool y::data::database::setRow(const std::string & table, row & values, field & condition, y::data::COMPARE c){
  if(!connected) return false;
  if(!values.elms()) return false;
  
  sql::SQLString query;
  query.append("UPDATE ");
  query.append(table);
  query.append(" SET ");
  for(int i = 0; i < values.elms(); i++) {
    if(i > 0) query.append(", ");
    query.append(values[i].name());
    query.append("=?");
  }
  query.append(" WHERE ");
  query.append(condition.name());
  switch (c) {
    case COMPARE::equal: query.append("="); break;
  }
  query.append("?");
  
  STATEMENT(statement, query);
  
  int i = 0;
  for(; i < values.elms(); i++) {
    addToStatement(statement, values[i], i+1);    
  }
  addToStatement(statement, condition, i+1);

  try {
    statement->executeQuery();
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
    query.append("?");
  }
  query.append(")");

  STATEMENT(statement, query);
  
  for(int i = 0; i < values.elms(); i++) {
    addToStatement(statement, values[i], i+1);
  }

  try {
    statement->executeUpdate();
    
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  return true;
}

bool y::data::database::delRow(const std::string & table, field & condition, y::data::COMPARE c) {
  if(!connected) return false;
  sql::SQLString query = "DELETE FROM ";
  query.append(table);
  query.append(" WHERE ");
  query.append(condition.name());
  switch (c) {
    case COMPARE::equal: query.append("=");
  } 
  query.append("?");

  STATEMENT(statement, query);

  addToStatement(statement, condition, 1);

  try {
    statement->executeUpdate();
    
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

void y::data::database::addToStatement(std::unique_ptr<sql::PreparedStatement>& statement, field& condition, int position) {
  //std::cout << "added " << condition.name() << " at position " << position << std::endl;
  
  switch(condition.getType()) {
    case BOOL: {
      statement->setBoolean(position, condition.asBool());
      break;
    }
    case CHAR: {
      statement->setInt(position, condition.asChar());
      break;
    }
    case SHORT: {
      statement->setInt(position, condition.asShort());
      break;
    }
    case INT: {
      statement->setInt(position, condition.asInt());
      break;
    }
    case LONG: {
      statement->setInt64(position, condition.asLong());
      break;
    }
    case FLOAT: {
      statement->setDouble(position, condition.asFloat());
      break;
    }
    case DOUBLE: {
      statement->setDouble(position, condition.asDouble());
      break;
    }
    case STRING: {
      statement->setString(position, str8(condition.asString()));
      break;
    }
    case STRING8: {
      statement->setString(position, condition.asString8());
      break;
    }
    case DATE_TIME: {
      statement->setDateTime(position, condition.asDate().dbFormat());
      break;
    }
    default: return;

  }
}