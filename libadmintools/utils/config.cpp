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
    std::wstring out = L"cannot open config file: ";
    out.append(strW(configFile));
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
    ldapPasswd = strW(map["ldapPasswd"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: ldap password is not set.");
  }
  
  if(map.count("ldapHost")) {
    ldapHost = strW(map["ldapHost"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: ldap host is not set.");
  }
  
  if(map.count("ldapBaseDN")) {
    ldapBaseDN = strW(map["ldapBaseDN"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: ldap Base DN is not set.");
  }   
  
  if(map.count("ldapAdminDN")) {
    ldapAdminDN = strW(map["ldapAdminDN"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: ldap admin DN is not set.");
  } 
  
  if(map.count("ldapTestUID")) {
    ldapTestUID = strW(map["ldapTestUID"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: ldap test UID is not set.");
  }
  
  if(map.count("ldapTestPassword")) {
    ldapTestPassword = strW(map["ldapTestPassword"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: ldap test password is not set.");
  }
  
  if(map.count("ldapTestUIDNumber")) {
    ldapTestUidNumber = strW(map["ldapTestUIDNumber"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: ldap test UID number is not set.");
  }
  
  if(map.count("ldapTestDN")) {
    ldapTestDN = strW(map["ldapTestDN"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: ldap test DN is not set.");
  }
  
  if(map.count("mysqlRootPassword")) {
    mysqlPassword = strW(map["mysqlRootPassword"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: mysql password is not set.");
  }
  
  if(map.count("domain")) {
    domain = strW(map["domain"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: domain is not set.");
  }
  
  if(map.count("smartschoolPw")) {
    smartschoolPw = strW(map["smartschoolPw"].as<std::string>());
  } else {
    y::utils::Log().add(L"Config warning: smartschool password is not set.");
  }
  
  if(map.count("yearbookAdmin")) {
    const std::vector<std::string> & admin = map["yearbookAdmin"].as< std::vector<std::string> >();
    for(unsigned int i = 0; i < admin.size(); i++) {
      yearbookAdmin.New() = strW(admin[i]);
    }
  }
  
  configReady = true;
}

const std::wstring & y::utils::config::getLdapPasswd() const {
  return ldapPasswd;
}

const std::wstring & y::utils::config::getLdapHost() const {
  return ldapHost;
}

const std::wstring & y::utils::config::getLdapBaseDN() const {
  return ldapBaseDN;
}

const std::wstring & y::utils::config::getLdapAdminDN() const {
  return ldapAdminDN;
}

const std::wstring & y::utils::config::getLdapTestUID() const {
  return ldapTestUID;
}

const std::wstring & y::utils::config::getLdapTestPassword() const {
  return ldapTestPassword;
}

const std::wstring & y::utils::config::getLdapTestUidNumber() const {
  return ldapTestUidNumber;
}

const std::wstring & y::utils::config::getLdapTestDN() const {
  return ldapTestDN;
}

const std::wstring & y::utils::config::getMysqlPassword() const {
  return mysqlPassword;
}

const std::wstring & y::utils::config::getDomain() const {
  return domain;
}

const std::wstring & y::utils::config::getSSPw() const {
  return smartschoolPw;
}

bool y::utils::config::isYearbookAdmin(const std::wstring& uid) {
  for(int i = 0; i < yearbookAdmin.elms(); i++) {
    if(yearbookAdmin[i].compare(uid) == 0) return true;
  }
  
  return false;
}