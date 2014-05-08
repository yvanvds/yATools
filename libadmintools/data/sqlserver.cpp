/* 
 * File:   server.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 5:55 PM
 */

#include "sqlserver.h"
#include "utils/config.h"

y::data::server & y::data::Server() {
  static server s;
  return s;
}

y::data::server::server() {
  driver = get_driver_instance();
  connection = std::unique_ptr<sql::Connection>(
            driver->connect("tcp://127.0.0.1:3306", 
                            "root", 
                            y::utils::Config().getMysqlPassword().c_str()));
  handle = getStatement();
}

bool y::data::server::drop(const std::string& dbName) {
  return handle->execute("DROP DATABASE " + dbName);
}

bool y::data::server::create(const std::string& dbName) {
  return handle->execute("CREATE DATABASE " + dbName);
}

bool y::data::server::hasDatabase(const std::string& dbName) {
  std::unique_ptr<sql::ResultSet> result;
  result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SHOW DATABASES LIKE '" + dbName + "'"));
  if (result->rowsCount()) return true;
  return false;
}


std::unique_ptr<sql::Statement> y::data::server::getStatement() {
  return std::unique_ptr<sql::Statement>(connection->createStatement());
}

