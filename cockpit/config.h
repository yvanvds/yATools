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

class config {
public:
  void create();
  void save();
  
private:
  boost::program_options::options_description cf;
  boost::program_options::variables_map map;
  
  std::string serverName;
};

config & Config();

#endif	/* CONFIG_H */

