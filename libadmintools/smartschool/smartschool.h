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
#include "ldap/group.h"

namespace y {
  class smartschool {
  public:
    smartschool();
   ~smartschool();
   
   int getUserDetails(const string & name, const string & password, y::data::row & details);
   
   // add a new course
   int addCourse(const string & name, const string & description);
   
   
   // add class or group to a course
   int setCourseClasses(const string & courseName, const string & courseDescription, container<string> & groupIDs);
  
   // add teacher to course, container with co-teachers can be empty
   int setCourseTeachers(const string & courseName, const string & courseDescription, const string & teacher, container<string> * coTeachers = nullptr);
  
   int savePassword(y::ldap::account & account);
   void saveUser(y::ldap::account & account);
   int addUserToGroup(y::ldap::account & account, const string & group, bool keepCurrent);
   int deleteUser(y::ldap::account & account, const string & removalDate = string("00/00/0000"));
   
   int addClass(y::ldap::group & group);
   int deleteClass(y::ldap::group & group);
   
   string errorToText(int code);
   
  private:
    V3BindingProxy service;
    
    // local database
    const string SS_ERRORS = string("smartschool_errors");
    
    // for maintenance
    void getErrorCodesFromSmartschool(y::data::database & db);
    void createErrorCodeTable(y::data::database & db);
    void loadErrorCodes(y::data::database & db);

    container<string> errorTable;
  };
  
  smartschool & Smartschool();
}



#endif	/* SMARTSCHOOL_H */

