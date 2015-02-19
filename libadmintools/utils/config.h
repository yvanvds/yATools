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
      
      const std::wstring & getLdapPasswd       () const;
      const std::wstring & getLdapHost         () const;
      const std::wstring & getLdapBaseDN       () const;
      const std::wstring & getLdapAdminDN      () const;
      const std::wstring & getLdapTestUID      () const;
      const std::wstring & getLdapTestPassword () const;
      const std::wstring & getLdapTestUidNumber() const;
      const std::wstring & getLdapTestDN       () const;
      const std::wstring & getMysqlPassword    () const;
      const std::wstring & getDomain           () const;
      const std::wstring & getSSPw             () const;

    private:
          
      boost::program_options::options_description general;
      boost::program_options::options_description file   ;
      boost::program_options::options_description all    ;
      
      bool configReady;
      
      boost::program_options::variables_map map;
      
      std::string configFile;
      
      std::wstring ldapPasswd;
      std::wstring ldapAdminDN;
      std::wstring ldapHost;
      std::wstring ldapBaseDN;
      std::wstring ldapTestUID;
      std::wstring ldapTestPassword;
      std::wstring ldapTestUidNumber;
      std::wstring ldapTestDN;
      std::wstring mysqlPassword;
      std::wstring domain;
      std::wstring smartschoolPw;
    };
    
    config & Config();

  }
}



