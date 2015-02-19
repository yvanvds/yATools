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
                            str8(y::utils::Config().getMysqlPassword()).c_str()));
  bool myTrue = true;
  connection->setClientOption("OPT_RECONNECT", &myTrue);
  handle = std::unique_ptr<sql::Statement>(connection->createStatement());
}

bool y::data::server::drop(const std::wstring& dbName) {
  return handle->execute("DROP DATABASE " + str8(dbName));
}

bool y::data::server::create(const std::wstring& dbName) {
  return handle->execute("CREATE DATABASE " + str8(dbName) + " CHARACTER SET 'utf8' COLLATE 'utf8_unicode_ci'");
}

bool y::data::server::hasDatabase(const std::wstring& dbName) {
  std::unique_ptr<sql::ResultSet> result;
  result = std::unique_ptr<sql::ResultSet>(handle->executeQuery("SHOW DATABASES LIKE '" + str8(dbName) + "'"));
  if (result->rowsCount()) return true;
  return false;
}


std::unique_ptr<sql::Connection> y::data::server::getConnection() {
  return std::unique_ptr<sql::Connection>
          (driver->connect("tcp://127.0.0.1:3306", 
                           "root", 
                           str8(y::utils::Config().getMysqlPassword()).c_str()));
}
