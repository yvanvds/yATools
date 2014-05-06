/* 
 * File:   config.cpp
 * Author: yvan
 * 
 * Created on December 8, 2013, 9:45 PM
 */

#include <iostream>
#include "config.h"
#include "../system/workDir.h"


using namespace boost::program_options;

y::sys::config::config(int argc, char** argv) : general("general options") {
  general.add_options()
    ("help", "print help message")
    ("work-directory,w", value<std::string>(), "set working directory")
  ;
  
  store(parse_command_line(argc, argv, general), map);
  notify(map);
  
  if(map.count("help")) {
    std::cout << general << std::endl;
    exit;
  }
  
  if(map.count("work-directory")) {
    WorkDir.set(map["work-directory"].as<std::string>());
  }
          
}

