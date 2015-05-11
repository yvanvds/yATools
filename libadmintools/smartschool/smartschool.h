/* 
 * File:   smartschool.h
 * Author: yvan
 *
 * Created on February 16, 2015, 4:14 PM
 */

#ifndef SMARTSCHOOL_H
#define	SMARTSCHOOL_H

#include "soapV3BindingProxy.h"

#include "utils/container.h"
#include "ldap/account.h"
#include "data/database.h"
#include "data/sqlserver.h"
#include "ldap/group.h"

namespace y {
  class smartschool {
  public:
    smartschool();
   ~smartschool();
   
   // add a new course
   int addCourse(const std::string & name, const std::string & description);
   
   // add class or group to a course
   void addGroupsToCourse(const std::string & courseName, const std::string & courseDescription, container<std::string> & groupIDs);
  
   // add teacher to course
   // void addTeacherToCourse(const std::string & courseName, const std::string & courseDescription, const )
  
   int savePassword(y::ldap::account & account);
   void saveUser(y::ldap::account & account);
   int addUserToGroup(y::ldap::account & account, const std::string & group, bool keepCurrent);
   int deleteUser(y::ldap::account & account, const std::string & removalDate = "00/00/0000");
   
   int addClass(y::ldap::group & group);
   int deleteClass(y::ldap::group & group);
   
   std::wstring errorToText(int code);
   
  private:
    V3BindingProxy service;
    
    // local database
    const std::wstring SS_ERRORS = L"smartschool_errors";
    std::unique_ptr<y::data::server> server;
    std::unique_ptr<y::data::database> db;
    
    // for maintenance
    void getErrorCodes();
    void createErrorCodeTable();
  };
  
  smartschool & Smartschool();
}



#endif	/* SMARTSCHOOL_H */

