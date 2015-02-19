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
      order & setKey(const std::string & key);
      order & descending(); 
      order & ascending(); // this is the default direction
    private:
      std::string key;
      bool ascend;
      friend class database;
    };
    
    extern container<order> defaultOrder;
    
    class database {
    public:
      database(server & serverObject);
      
      bool use(const std::wstring & dbName);
      
      bool createTable(const std::wstring & tableName, row & description);
      bool deleteTable(const std::wstring & tableName);
      bool tableExists(const std::wstring & tableName);
      
      bool getTables(container<std::wstring> & tables);
      bool getAllRows(const std::wstring & table, container<row> & rows, container<order> & order = defaultOrder);
      bool getRows(const std::wstring & table, container<row> & rows, field & condition, container<order> & order = defaultOrder, COMPARE c = COMPARE::equal);

      bool setRow(const std::wstring & table, row & values, field & condition, COMPARE c = COMPARE::equal);
      bool addRow(const std::wstring & table, row & values);
      bool delRow(const std::wstring & table, field & condition, COMPARE c = COMPARE::equal);
      
      bool execute(const std::wstring & query);
      
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

