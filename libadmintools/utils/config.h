#pragma once
/* 
 * File:   config.h
 * Author: yvan
 *
 * Created on December 8, 2013, 9:45 PM
 */

#include <boost/program_options.hpp>

namespace y {
  namespace utils {
    class config {
    public:
      config();
      
      void load(); // use config file only, no command line arguments
      void load(int argc, char** argv);
      
      const std::string & getLdapPasswd () const;
      const std::string & getLdapHost   () const;
      const std::string & getLdapBaseDN () const;
      const std::string & getLdapAdminDN() const;

    private:
      bool configReady;
      
      boost::program_options::options_description general;
      boost::program_options::options_description file   ;
      boost::program_options::options_description all    ;
      
      boost::program_options::variables_map map;
      
      std::string configFile;
      
      std::string ldapPasswd;
      std::string ldapAdminDN;
      std::string ldapHost;
      std::string ldapBaseDN;
    };
    
    config & Config();

  }
}



