/* 
 * File:   server.h
 * Author: yvan
 *
 * Created on May 8, 2014, 5:55 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "utils/string.h"

namespace y {
  namespace data {
    class server {
    public:
      server();
 
      bool drop       (const string & dbName);
      bool create     (const string & dbName);
      bool hasDatabase(const string & dbName);
      
    private:
      // the caller is responsible for deleting this, best to use a managed ptr
      std::unique_ptr<sql::Connection> getConnection();
      
      sql::Driver * driver;
      std::unique_ptr<sql::Connection> connection;
      std::unique_ptr<sql::Statement>  handle;
      
      friend class database;
    };
    
  }
}


#endif	/* SERVER_H */

