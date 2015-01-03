/* 
 * File:   config.cpp
 * Author: yvan
 * 
 * Created on January 2, 2015, 7:16 PM
 */

#include <fstream>

#include "config.h"
#include <iostream>

using namespace boost::program_options;
using namespace std;

config & Config() {
  static config c;
  return c;
}

void config::create() {
  needsSaving = false;
  
  cf.add_options()
    ("serverName", value<std::string>())
    ("domainName", value<std::string>())
    ("publicIP"  , value<std::string>())
    ("backboneIP", value<std::string>())
  ;
  
  std::ifstream ifs("/root/admintools/cockpit.cfg");
  if(ifs) {
    store(parse_config_file(ifs, cf), map);
    notify(map);
  } else {
    cout << "===============================================" << endl;
    cout << "/root/admintools/cockpit.cfg not found." << endl;
    cout << "Starting with a new configuration." << endl;
    cout << "===============================================" << endl;
  }
  
  if(map.count("serverName")) {
    serverName = map["serverName"].as<std::string>();
  } else {
    cout << "Please enter the name of this server: ";
    getline(cin, serverName);
    needsSaving = true;
  } 
  
  if(map.count("domainName")) {
    domainName = map["domainName"].as<std::string>();
  } else {
    cout << "Please enter the domain for this server: ";
    getline(cin, domainName);
    needsSaving = true;
  }
  
  if(map.count("publicIP")) {
    publicIP = map["publicIP"].as<std::string>();
  } else {
    cout << "Please enter the public IP address: ";
    getline(cin, publicIP);
    needsSaving = true;
  }
  
  if(map.count("backboneIP")) {
    backboneIP = map["backboneIP"].as<std::string>();
  } else {
    cout << "Please enter the backbone IP address: ";
    getline(cin, backboneIP);
    needsSaving = true;
  }
}

void config::save() {
  if(!needsSaving) return;
  
  std::ofstream ofs("/root/admintools/cockpit.cfg", ios_base::trunc);
  ofs << "serverName = " << serverName << endl;
  ofs << "domainName = " << domainName << endl;
  ofs.close();
}

string config::getServerName() {
  return serverName;
}

string config::getDomainName() {
  return domainName;
}

string config::getPublicIP() {
  return publicIP;
}

string config::getBackboneIP() {
  return backboneIP;
}
