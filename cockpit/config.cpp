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
  cf.add_options()
    ("ServerName", value<std::string>())
  ;
  
  std::ifstream ifs("~/admintools/cockpit.cfg");
  if(ifs) {
    store(parse_config_file(ifs, cf), map);
    notify(map);
  } else {
    cout << "===============================================" << endl;
    cout << "/etc/admintools/cockpit.cfg not found." << endl;
    cout << "Starting with a new configuration." << endl;
    cout << "===============================================" << endl;
  }
  
  if(map.count("serverName")) {
    serverName = map["serverName"].as<std::string>();
  } else {
    cout << "Please enter the name of this server: ";
    getline(cin, serverName);
  } 
}

void config::save() {
  std::ofstream ofs("~/admintools/cockpit.cfg", ios_base::trunc);
  ofs << "serverName = " << serverName << endl;
  ofs.close();
}