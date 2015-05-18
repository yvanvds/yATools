/* 
 * File:   database.h
 * Author: yvan
 *
 * Created on May 8, 2014, 7:11 PM
 */

#ifndef DATABASE_H
#define	DATABASE_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "../utils/container.h"
#include "../utils/string.h"
#include "row.h"
#include "sqlserver.h"

#define STATEMENT(NAME, ARGS) \
std::unique_ptr<sql::PreparedStatement> NAME \
= std::unique_ptr<sql::PreparedStatement>(connection->prepareStatement(ARGS))

namespace y {
  namespace data {
    
    enum COMPARE {
      equal,
    };
    
    class database;
    
    class order {
    public:
      order();
      order & setKey(const string & key);
      order & descending(); 
      order & ascending(); // this is the default direction
    private:
      string key;
      bool ascend;
      friend class database;
    };
    
    extern container<order> defaultOrder;
    
    class database {
    public:
      database(server & serverObject);
      
      bool use(const string & dbName);
      
      bool createTable(const string & tableName, row & description);
      bool deleteTable(const string & tableName);
      bool tableExists(const string & tableName);
      
      bool getTables(container<string> & tables);
      bool getAllRows(const string & table, container<row> & rows, container<order> & order = defaultOrder);
      bool getRows(const string & table, container<row> & rows, field & condition, container<order> & order = defaultOrder, COMPARE c = COMPARE::equal);

      bool setRow(const string & table, row & values, field & condition, COMPARE c = COMPARE::equal);
      bool addRow(const string & table, row & values);
      bool delRow(const string & table, field & condition, COMPARE c = COMPARE::equal);
      
      bool execute(const string & query);
      
    private:
      void parseRows(std::unique_ptr<sql::ResultSet> & result, container<row> & rows);
      void addToStatement(std::unique_ptr<sql::PreparedStatement> & statement, field & condition, int position);
      
      server & serverObject;
      std::unique_ptr<sql::Connection> connection;
      std::unique_ptr<sql::Statement> handle;
      bool connected;
      
    };
  }
}
#endif	/* DATABASE_H */

