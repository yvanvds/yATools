/* 
 * File:   config.h
 * Author: yvan
 *
 * Created on January 2, 2015, 7:16 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <boost/program_options.hpp>
#include <string>
#include <map>

class config {
public:
  void create();
  void save();
  
  std::string getServerName();
  std::string getDomainName();
  std::string getPublicIP();
  std::string getBackboneIP();
  
  // this is filled in hostValidate()
  std::map<std::string, std::string> hosts;
  
private:
  boost::program_options::options_description cf;
  boost::program_options::variables_map map;
  
  bool needsSaving;
  
  std::string serverName;
  std::string domainName;
  std::string publicIP;
  std::string backboneIP;
};

config & Config();

#endif	/* CONFIG_H */

