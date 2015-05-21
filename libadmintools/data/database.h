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

#define CREATE_STATEMENT(NAME, ARGS) sql::PreparedStatement * NAME = connection->prepareStatement(ARGS)
#define DELETE_STATEMENT(NAME) delete NAME

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
      database();
      ~database();
      
      database & open();
      void close();
      
      // schema management
      bool drop  (const string & schema);
      bool create(const string & schema);
      bool has   (const string & schema);
      bool use   (const string & schema);
      
      
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
      void addToStatement(sql::PreparedStatement * statement, field & condition, int position);
      
      sql::Driver * driver;
      sql::Connection * connection;
      sql::Statement * handle;
      bool connected;
      
    };
  }
}
#endif	/* DATABASE_H */

