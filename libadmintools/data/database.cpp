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
#include "utils/string.h"

y::data::order::order() : ascend(true) {}

y::data::order & y::data::order::setKey(const string & key) {
  this->key = key;
  return *this;
}

y::data::order & y::data::order::descending() {
  ascend = false;
  return *this;
}

y::data::order & y::data::order::ascending() {
  ascend = true;
  return *this;
}

container<y::data::order> y::data::defaultOrder;

y::data::database::database(y::data::server & serverObject) : serverObject(serverObject)
, connection(serverObject.getConnection()),
  connected(false){
  handle = std::unique_ptr<sql::Statement>(connection->createStatement());
}

bool y::data::database::use(const string & dbName) {
  if(!serverObject.hasDatabase(dbName)) {
    connected = false;
  } else {
    connection->setSchema(dbName.db());
    connected = true;
  }
  return connected;
}

bool y::data::database::createTable(const string & tableName, row & description) {
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
  query.append(tableName.db());
  query.append(" (");
  for(int i = 0; i < description.elms(); i++) {
    // add comma
    if(i>0) query.append(", ");
    
    // add field name
    query.append(description[i].name().db());
    
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

bool y::data::database::deleteTable(const string & tableName) {
  if(!connected) return false;
  bool result = false;
  
  try {
    result = handle->execute("DROP TABLE " + tableName.db());
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
  
  return result;
}

bool y::data::database::tableExists(const string & tableName) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  
  try {
    result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SHOW TABLES LIKE '" + tableName.db() + "'"));
  } catch (sql::SQLException & e) {
    std::cout << "#\t SQL Exception: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return false;
  }
    
  if (result->rowsCount()) return true;
  return false;
}

bool y::data::database::getTables(container<string>& tables) {
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

bool y::data::database::getAllRows(const string & table, container<row>& rows, container<order>& orderBy) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  
  string query;
  query = "SELECT * FROM ";
  query += table;
  if(!orderBy.empty()) {
    query += " ORDER BY ";
    for(int i = 0; i < orderBy.elms(); i++) {
      if(i > 0) query += ", ";
      query += orderBy[0].key;
      if (orderBy[0].ascend) {
        query += " ASC";
      } else {
        query += " DESC";
      }
    }
  }
  
  try {
    result = std::unique_ptr<sql::ResultSet>(handle->executeQuery(query.db()));
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

bool y::data::database::getRows(const string & table, container<row> & rows, field & condition, container<order>& orderBy, COMPARE c) {
  if(!connected) return false;
  std::unique_ptr<sql::ResultSet> result;
  
  string query;
  query = "SELECT * FROM ";
  query += table;
  query += " WHERE ";
  query += condition.name();
  switch(c) {
    case COMPARE::equal: 
      query += "="; break;
  }
  query += "?";

  if(!orderBy.empty()) {
    query += " ORDER BY ";
    for(int i = 0; i < orderBy.elms(); i++) {
      if(i > 0) query += ", ";
      query += orderBy[0].key;
      if (orderBy[0].ascend) {
        query += " ASC";
      } else {
        query += " DESC";
      }
    }
  }  
  
  STATEMENT(statement, query.db());
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
  container<string> columnNames;
  container<string> columnTypes;
  for(unsigned int i = 1; i <= meta->getColumnCount(); i++) {
    columnNames[i-1] = meta->getColumnName(i);
    columnTypes[i-1] = meta->getColumnTypeName(i);
  }
  while(result->next()) {
    row & entry = rows.New();
    for(int i = 0; i < columnNames.elms(); i++) {
      if(columnTypes[i] == "BIT") {
        entry.addBool(columnNames[i], result->getBoolean(i+1));
      } else if(columnTypes[i] == "TINYINT") {
        entry.addChar(columnNames[i], result->getInt(i+1));
      } else if(columnTypes[i] == "SMALLINT") {
        entry.addShort(columnNames[i], result->getInt(i+1));
      } else if(columnTypes[i] == "INT") {
        entry.addInt(columnNames[i], result->getInt(i+1));
      } else if(columnTypes[i] == "BIGINT") {
        entry.addLong(columnNames[i], result->getInt64(i+1));
      } else if(columnTypes[i] == "FLOAT") {
        entry.addFloat(columnNames[i], result->getDouble(i+1));
      } else if(columnTypes[i] == "DOUBLE") {
        entry.addDouble(columnNames[i], result->getDouble(i+1));
      } else if(columnTypes[i] == "VARCHAR") {
        entry.addString(columnNames[i], string(result->getString(i+1)));
      } else if(columnTypes[i] == "DATETIME") {
        dateTime d;
        d.dbFormat(string(result->getString(i+1)));
        entry.addDate(columnNames[i], d);
      }
    }
  }
}

bool y::data::database::setRow(const string & table, row & values, field & condition, y::data::COMPARE c){
  if(!connected) return false;
  if(!values.elms()) return false;
  
  string query("UPDATE ");
  query += table + " SET ";
  for(int i = 0; i < values.elms(); i++) {
    if(i > 0) query += ", ";
    query += values[i].name();
    query += "=?";
  }
  query += " WHERE ";
  query += condition.name();
  switch (c) {
    case COMPARE::equal: query += "="; break;
  }
  query += "?";
  
  STATEMENT(statement, query.db());
  
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

bool y::data::database::addRow(const string& table, row& values) {
  if(!connected) return false;
  if(!values.elms()) return false;
  
  string query("INSERT INTO ");
  query += table + " (";
  for(int i = 0; i < values.elms(); i++) {
    if(i > 0) query += ", ";
    query += values[i].name();
  }
  query += ") VALUES (";
  for(int i = 0; i < values.elms(); i++) {
    if(i > 0) query += ", ";
    query += "?";
  }
  query += ")";

  STATEMENT(statement, query.db());
  
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

bool y::data::database::delRow(const string & table, field & condition, y::data::COMPARE c) {
  if(!connected) return false;
  string query("DELETE FROM ");
  query += table;
  query += " WHERE ";
  query += condition.name();
  switch (c) {
    case COMPARE::equal: query += "=";
  } 
  query += "?";

  STATEMENT(statement, query.db());

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

bool y::data::database::execute(const string & query) {
  if(!connected) return false;
  
  try {
    handle->execute(query.db());
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
      statement->setString(position, condition.asString().db());
      break;
    }
    case DATE_TIME: {
      statement->setDateTime(position, condition.asDate().dbFormat().db());
      break;
    }
    default: return;

  }
}