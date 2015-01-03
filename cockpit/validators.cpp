/* 
 * File:   hostValidate.cpp
 * Author: yvan
 * 
 * Created on January 3, 2015, 1:54 PM
 */

#include <iostream>
#include <fstream>
#include <map>
#include "validators.h"
#include "admintools.h"
#include "config.h"
#include <boost/filesystem.hpp>

void ValidateAll() {
  hostValidate();
}

void hostValidate() {
  std::vector<std::string> result;
  
  // check hostname
  y::sys::GetProcessResult("cat /etc/hostname", result);
  if(result.size() && result[0].compare(Config().getServerName()) == 0) {
    y::sys::stdOut("/etc/hostname is valid");
  } else {
    y::sys::stdOut("correcting /etc/hostname");
    std::ofstream ofs("/etc/hostname", std::ios_base::trunc);
    ofs << Config().getServerName();
    ofs.close();
  }
  
  // check known hosts for this domain
  std::string domainFile = "/root/github/yATools/data/domains/";
  
  domainFile += Config().getDomainName();
  if(boost::filesystem::exists(domainFile)) {
    std::ifstream ifs(domainFile);
    std::string line;
    while(std::getline(ifs, line)) {
      int pos = line.find_first_of(':');
      Config().hosts[line.substr(0,pos)] = line.substr(pos+1);
    }
    ifs.close();
  }
  
  // if host is not found, add it
  if(Config().hosts.find(Config().getServerName()) == Config().hosts.end()) {
    Config().hosts[Config().getServerName()] = Config().getBackboneIP();
    y::sys::file::append(domainFile, Config().getServerName() + ":" + Config().getBackboneIP());
    y::sys::stdOut(Config().getServerName() + " added to domain list. You probably need to push this git repo.");
  }
  
  // check /etc/hosts
  result.clear();
  for(auto iter = Config().hosts.begin(); iter != Config().hosts.end(); ++iter) {
    if(!y::sys::file::has("/etc/hosts", iter->first)) {
      y::sys::file::append("/etc/hosts", iter->second + " " + iter->first);
      y::sys::stdOut("added " + Config().getServerName() + " to /etc/hosts");
    }
  }
  
}