/* 
 * File:   config.cpp
 * Author: yvan
 * 
 * Created on December 8, 2013, 9:45 PM
 */

#include <iostream>
#include <vector>
#include "config.h"
#include "convert.h"
#include "../system/workDir.h"
#include "log.h"

y::utils::config & y::utils::Config() {
  static config c;
  return c;
}

using namespace boost::program_options;

y::utils::config::config() : general("general options"),
    file("config file options"),
    configReady(false){
}

void y::utils::config::load() {
  load(0, nullptr);
}

void y::utils::config::load(int argc, char** argv) {
  if(configReady) {
    //Log().add("y::sys::config::load is called more than once!");
    return;
  }
  
  general.add_options()
    ("help", "print help message")
    ("work-directory,w", value<std::string>(), "set working directory")
    ("config,c", 
     value<std::string>(&configFile)->default_value("/etc/yATools.cfg"), 
     "Name of the config file to be used."
    )
  ;
  
  file.add_options()
    ("ldapPasswd"       , value<std::string>(), "set ldap admin password")
    ("ldapHost"         , value<std::string>(), "set ldap host"          )
    ("ldapBaseDN"       , value<std::string>(), "set ldap base DN"       )
    ("ldapAdminDN"      , value<std::string>(), "set ldap admin DN"      )
    ("ldapTestUID"      , value<std::string>(), "set ldap test account"  )
    ("ldapTestPassword" , value<std::string>(), "set ldap test account password")
    ("ldapTestUIDNumber", value<std::string>(), "set ldap test account UID number")
    ("ldapTestDN"       , value<std::string>(), "set ldap test account DN")
    ("mysqlRootPassword", value<std::string>(), "set mysql root password")
    ("domain"           , value<std::string>(), "set network domain"     )
    ("smartschoolPw"    , value<std::string>(), "set smartschool password")
    ("yearbookAdmin"    , value< std::vector<std::string> >(), "set yearbook administrators" )
  ;
  
  all.add(general).add(file);
  
  store(parse_command_line(argc, argv, all), map);
  notify(map);
  
  std::wifstream ifs(configFile.c_str());
  if(!ifs) {
    string out("cannot open config file: ");
    out += configFile.c_str();
    Log().add(out);
  } else {
    /*std::string out = "loading config file: ";
    out.append(configFile);
    Log().add(out);*/
    store(parse_config_file(ifs, file), map);
    notify(map);
  }
  
  if(map.count("help")) {
    std::cout << general << std::endl;
    exit(0);
  }
  
  if(map.count("work-directory")) {
    y::sys::WorkDir.set(map["work-directory"].as<std::string>());
  }
  
  if(map.count("ldapPasswd")) {
    ldapPasswd = map["ldapPasswd"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: ldap password is not set.");
  }
  
  if(map.count("ldapHost")) {
    ldapHost = map["ldapHost"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: ldap host is not set.");
  }
  
  if(map.count("ldapBaseDN")) {
    ldapBaseDN = map["ldapBaseDN"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: ldap Base DN is not set.");
  }   
  
  if(map.count("ldapAdminDN")) {
    ldapAdminDN = map["ldapAdminDN"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: ldap admin DN is not set.");
  } 
  
  if(map.count("ldapTestUID")) {
    ldapTestUID = map["ldapTestUID"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: ldap test UID is not set.");
  }
  
  if(map.count("ldapTestPassword")) {
    ldapTestPassword = map["ldapTestPassword"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: ldap test password is not set.");
  }
  
  if(map.count("ldapTestUIDNumber")) {
    ldapTestUidNumber = map["ldapTestUIDNumber"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: ldap test UID number is not set.");
  }
  
  if(map.count("ldapTestDN")) {
    ldapTestDN = map["ldapTestDN"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: ldap test DN is not set.");
  }
  
  if(map.count("mysqlRootPassword")) {
    mysqlPassword = map["mysqlRootPassword"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: mysql password is not set.");
  }
  
  if(map.count("domain")) {
    domain = map["domain"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: domain is not set.");
  }
  
  if(map.count("smartschoolPw")) {
    smartschoolPw = map["smartschoolPw"].as<std::string>();
  } else {
    y::utils::Log().add("Config warning: smartschool password is not set.");
  }
  
  if(map.count("yearbookAdmin")) {
    const std::vector<std::string> & admin = map["yearbookAdmin"].as< std::vector<std::string> >();
    for(unsigned int i = 0; i < admin.size(); i++) {
      yearbookAdmin.New() = admin[i];
    }
  }
  
  configReady = true;
}

const string & y::utils::config::getLdapPasswd() const {
  return ldapPasswd;
}

const string & y::utils::config::getLdapHost() const {
  return ldapHost;
}

const string & y::utils::config::getLdapBaseDN() const {
  return ldapBaseDN;
}

const string & y::utils::config::getLdapAdminDN() const {
  return ldapAdminDN;
}

const string & y::utils::config::getLdapTestUID() const {
  return ldapTestUID;
}

const string & y::utils::config::getLdapTestPassword() const {
  return ldapTestPassword;
}

const string & y::utils::config::getLdapTestUidNumber() const {
  return ldapTestUidNumber;
}

const string & y::utils::config::getLdapTestDN() const {
  return ldapTestDN;
}

const string & y::utils::config::getMysqlPassword() const {
  return mysqlPassword;
}

const string & y::utils::config::getDomain() const {
  return domain;
}

const string & y::utils::config::getSSPw() const {
  return smartschoolPw;
}

bool y::utils::config::isYearbookAdmin(const string& uid) {
  for(int i = 0; i < yearbookAdmin.elms(); i++) {
    if(yearbookAdmin[i] == uid) return true;
  }
  
  return false;
}