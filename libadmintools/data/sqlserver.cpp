/* 
 * File:   server.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 5:55 PM
 */

#include "sqlserver.h"
#include "utils/config.h"
#include "utils/convert.h"

y::data::server::server() {
  driver = get_driver_instance();
  connection = std::unique_ptr<sql::Connection>(
            driver->connect("tcp://127.0.0.1:3306", 
                            "root", 
                            y::utils::Config().getMysqlPassword().ldap()));
  bool myTrue = true;
  connection->setClientOption("OPT_RECONNECT", &myTrue);
  handle = std::unique_ptr<sql::Statement>(connection->createStatement());
}

bool y::data::server::drop(const string& dbName) {
  return handle->execute("DROP DATABASE " + dbName.db());
}

bool y::data::server::create(const string& dbName) {
  return handle->execute("CREATE DATABASE " + dbName.db() + " CHARACTER SET 'utf8' COLLATE 'utf8_unicode_ci'");
}

bool y::data::server::hasDatabase(const string& dbName) {
  std::unique_ptr<sql::ResultSet> result;
  result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SHOW DATABASES LIKE '" + dbName.db() + "'"));
  if (result->rowsCount()) return true;
  return false;
}


std::unique_ptr<sql::Connection> y::data::server::getConnection() {
  return std::unique_ptr<sql::Connection>
          (driver->connect("tcp://127.0.0.1:3306", 
                           "root", 
                           y::utils::Config().getMysqlPassword().ldap()));
}
