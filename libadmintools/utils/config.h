#pragma once
/* 
 * File:   config.h
 * Author: yvan
 *
 * Created on December 8, 2013, 9:45 PM
 */

#include <boost/program_options.hpp>
#include "container.h"
#include "string.h"

namespace y {
  namespace utils {
    class config {
    public:
      config();
      
      void load(); // use config file only, no command line arguments
      void load(int argc, char** argv);
      
      const string & getLdapPasswd       () const;
      const string & getLdapHost         () const;
      const string & getLdapBaseDN       () const;
      const string & getLdapAdminDN      () const;
      const string & getLdapTestUID      () const;
      const string & getLdapTestPassword () const;
      const string & getLdapTestUidNumber() const;
      const string & getLdapTestDN       () const;
      const string & getMysqlPassword    () const;
      const string & getDomain           () const;
      const string & getSSPw             () const;
      
      bool isYearbookAdmin(const string & uid);

    private:
          
      boost::program_options::options_description general;
      boost::program_options::options_description file   ;
      boost::program_options::options_description all    ;
      
      bool configReady;
      
      boost::program_options::variables_map map;
      
      std::string configFile;
      
      string ldapPasswd;
      string ldapAdminDN;
      string ldapHost;
      string ldapBaseDN;
      string ldapTestUID;
      string ldapTestPassword;
      string ldapTestUidNumber;
      string ldapTestDN;
      string mysqlPassword;
      string domain;
      string smartschoolPw;
      
      container<string> yearbookAdmin;
    };
    
    config & Config();

  }
}



