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
#include "ldap/schoolClass.h"

namespace y {
  class smartschool {
  public:
    
    struct courseTeacher {
      string firstname;
      string lastname;
      string username;
      string wisaID;
    };
    
    struct studentGroup {
      string name;
      string description;
      string type;
    };
    
    struct course {
      string name;
      string description;
      bool active;
      courseTeacher mainTeacher;
      container<courseTeacher> coTeachers;
      container<studentGroup> classes;
    };
    
    smartschool();
   ~smartschool();
   
   // course functions
   bool addCourse        (const string & name      , const string & description); // create a course in smartschool
   bool setCourseStudents(const string & courseName, const string & courseDescription, container<string> & classIDs);
   bool setCourseTeachers(const string & courseName, const string & courseDescription, const string & teacher, container<string> * coTeachers = nullptr);
   bool getCourses       (container<course> & result);
   
   // skore management
   bool getSkoreInfo(container<string> & result);
   
   // user management
   bool saveUser        (const y::ldap::account & account);
   bool savePassword    (const y::ldap::account & account);
   bool saveNationality (const y::ldap::account & account);
   bool savePhoto       (const y::ldap::account & account);
   bool setAccountStatus(const y::ldap::account & account);
   bool unregister      (const y::ldap::account & account);
   
   bool setCoAccount(const string & uid, const string & pw, bool firstAccount);
   
   bool validate        (const string & username, const string & password);
   
   bool deleteUser      (const y::ldap::account & account);
   bool replaceWisaID   (const y::ldap::account & account, WISA_ID & oldID);
  
   bool getUserDetails  (const string & name, const string & password, y::data::row & details);
   bool getAbsents      (const y::ldap::account & account, int year, container<string> & absents);   
   bool getAllAccounts  (const string & group, bool recursive, container<string> & accounts);
   bool getAllAccountsExtended(const string & group, bool recursive, container<string> & accounts);
   
   // group management
   bool getAllGroupsAndClasses(container<string> & result);
   bool getAllClasses         (container<string> & result);
   bool getClassTeachers      (container<string> & result);
   bool saveClass  (const y::ldap::schoolClass & group);
   bool saveGroup  (const y::ldap::group       & group);
   bool deleteClass(const y::ldap::schoolClass & group);
   bool moveUserToClass(const y::ldap::account & account, const string & group);   
   bool addUserToGroup (const y::ldap::account & account, const string & group, bool keepCurrent);
   
   // other
   bool sendMessage(const y::ldap::account & account, const string & title, const string & body);
   string errorToText(int code);
   
  private:
    V3BindingProxy service;
    
    // local database
    const string SS_ERRORS = string("smartschool_errors");
    
    // for maintenance
    void getErrorCodesFromSmartschool(y::data::database & db);
    void createErrorCodeTable(y::data::database & db);
    void loadErrorCodes(y::data::database & db);

    bool saveUserParam(const string & ID, const string & param, const string & value);
    string getAccountID(const y::ldap::account & account);
    
    bool validateSoapResult(soap_dom_element & result);
    
    container<string> errorTable;
  };
  
  smartschool & Smartschool();
}



#endif	/* SMARTSCHOOL_H */

