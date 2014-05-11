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
#include "../utils/container.h"
#include "row.h"

namespace y {
  namespace data {
    class database {
    public:
      database();
      
      bool use(const std::string & dbName);
      
      bool createTable(const std::string & tableName, row & description);
      bool deleteTable(const std::string & tableName);
      bool tableExists(const std::string & tableName);
      
      bool getTables(container<std::string> & tables);
      bool getAllRows(const std::string & table, container<row> & rows);
      bool getRows(const std::string & table, const std::string & condition, container<row> & rows);

      bool setRow(const std::string & table, const std::string & condition, row & values);
      bool addRow(const std::string & table, row & values);
      bool delRow(const std::string & table, const std::string & condition);
      
      bool execute(const std::string & query);
      
    private:
      void parseRows(std::unique_ptr<sql::ResultSet> & result, container<row> & rows);
      
      std::unique_ptr<sql::Connection> connection;
      std::unique_ptr<sql::Statement> handle;
      bool connected;
    };
  }
}
#endif	/* DATABASE_H */

