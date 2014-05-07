/* 
 * File:   config.cpp
 * Author: yvan
 * 
 * Created on December 8, 2013, 9:45 PM
 */

#include <iostream>
#include "config.h"
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
    ("ldapPasswd" , value<std::string>(), "set ldap admin password")
    ("ldapHost"   , value<std::string>(), "set ldap host"          )
    ("ldapBaseDN" , value<std::string>(), "set ldap base DN"       )
    ("ldapAdminDN", value<std::string>(), "set ldap admin DN"      )
    ("ldapTestUID", value<std::string>(), "set ldap test account"  )
    ("ldapTestPassword", value<std::string>(), "set ldap test account password")
  ;
  
  all.add(general).add(file);
  
  store(parse_command_line(argc, argv, all), map);
  notify(map);
  
  std::ifstream ifs(configFile.c_str());
  if(!ifs) {
    std::string out = "cannot open config file: ";
    out.append(configFile);
    Log().add(out);
  } else {
    std::string out = "loading config file: ";
    out.append(configFile);
    Log().add(out);
    store(parse_config_file(ifs, file), map);
    notify(map);
  }
  
  if(map.count("help")) {
    std::cout << general << std::endl;
    exit;
  }
  
  if(map.count("work-directory")) {
    y::sys::WorkDir.set(map["work-directory"].as<std::string>());
  }
  
  if(map.count("ldapPasswd")) {
    ldapPasswd = map["ldapPasswd"].as<std::string>();
  }
  
  if(map.count("ldapHost")) {
    ldapHost = map["ldapHost"].as<std::string>();
  }
  
  if(map.count("ldapBaseDN")) {
    ldapBaseDN = map["ldapBaseDN"].as<std::string>();
  }   
  
  if(map.count("ldapAdminDN")) {
    ldapAdminDN = map["ldapAdminDN"].as<std::string>();
  } 
  
  if(map.count("ldapTestUID")) {
    ldapTestUID = map["ldapTestUID"].as<std::string>();
  }
  
  if(map.count("ldapTestPassword")) {
    ldapTestPassword = map["ldapTestPassword"].as<std::string>();
  }
  
  configReady = true;
}

const std::string & y::utils::config::getLdapPasswd() const {
  return ldapPasswd;
}

const std::string & y::utils::config::getLdapHost() const {
  return ldapHost;
}

const std::string & y::utils::config::getLdapBaseDN() const {
  return ldapBaseDN;
}

const std::string & y::utils::config::getLdapAdminDN() const {
  return ldapAdminDN;
}

const std::string & y::utils::config::getLdapTestUID() const {
  return ldapTestUID;
}

const std::string & y::utils::config::getLdapTestPassword() const {
  return ldapTestPassword;
}
