/* 
 * File:   smartschool.cpp
 * Author: yvan
 * 
 * Created on February 16, 2015, 4:14 PM
 */

#include "smartschool.h"
#include "utils/config.h"
#include "utils/convert.h"
#include "V3Binding.nsmap"
#include "utils/stringFunctions.h"
#include "utils/string.h"
#include "data/database.h"
#include "ldap/group.h"
#include "utils/log.h"

#include "Wt/Json/Parser"
#include "Wt/Json/Object"
#include "Wt/Json/Value"

//#include "ldap/account.h"

y::smartschool & y::Smartschool() {
  static smartschool s;
  return s;
}

y::smartschool::smartschool() {
  y::data::database db;
  db.open();
  if(!db.has("admintools")) {
    db.create("admintools");
  }
  db.use("admintools");
  
  if(!db.tableExists(SS_ERRORS)) {
    createErrorCodeTable(db);
  } else {
    container<y::data::row> rows;
    y::data::field condition;
    condition.name("ID").setInt(0);
    db.getRows(SS_ERRORS, rows, condition);
    if(rows.elms()) {
      std::string::size_type sz;
      int lasttime = std::stoi(rows[0]["code"].asString().utf8(), &sz);
      time_t now = time(0);
      
      // renew if a day has past
      if(now - lasttime > 86400) {
        db.deleteTable(SS_ERRORS);
        createErrorCodeTable(db);
      }
    }
  }
  loadErrorCodes(db);
  db.close();
}

y::smartschool::~smartschool() {
  service.destroy();
}

int y::smartschool::getUserDetails(const string& name, const string& password, y::data::row& details) {
  soap_dom_element result;
  
  
  
  if(service.isValidUserCredentials(y::utils::Config().getSSPw().ss(), 
                                    name.ss(), 
                                    password.ss(),
                                    result) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    Wt::Json::Object data;
    Wt::Json::ParseError error;
    if(!Wt::Json::parse(string(result.wide).utf8(), data, error)) {
      return string(result.wide).asInt();
    } else {
      details["number"].setInt(string(data.get("number")).asInt());
      details["username"].setString(string(data.get("username")));
      details["name"].setString(string(data.get("name")));
      details["surname"].setString(string(data.get("surname")));
      details["email"].setString(string(data.get("email")));
      details["role"].setInt(string(data.get("role")).asInt());
      details["accountType"].setInt(string(data.get("accountType")).asInt());
    }
    
  }
  
  
  return 0;
}

int y::smartschool::addCourse(const string& name, const string& description) {
  std::string result;
  if(service.addCourse(y::utils::Config().getSSPw().ss(), name.ss(), description.ss(), result) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    // it's a string, but it always returns an int
    return std::stoi(result);
  } 
}

int y::smartschool::setCourseClasses(const string& courseName, const string& courseDescription, container<string>& groupIDs) {
  soap_dom_element result;
  string grouplist;
  for(int i = 0; i < groupIDs.elms(); i++) {
    grouplist += groupIDs[i];
    if(i < (groupIDs.elms() - 1)) grouplist += ',';
  }
  
  if(service.addCourseStudents(y::utils::Config().getSSPw().ss()
                            , courseName.ss()
                            , courseDescription.ss()
                            , grouplist.ss()
                            , result
    ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    return string(result.wide).asInt();
  }
}

int y::smartschool::setCourseTeachers(const string& courseName, const string& courseDescription, const string & teacher, container<string> * coTeachers) {
  soap_dom_element result;
  string grouplist;
  if(coTeachers != nullptr) {
    for(int i = 0; i < coTeachers->elms(); i++) {
      grouplist += (*coTeachers)[i];
      if(i < (coTeachers->elms() - 1)) grouplist += ',';
    }
  }
  
  if(service.addCourseTeacher(y::utils::Config().getSSPw().ss()
                              , courseName.ss()
                              , courseDescription.ss()
                              , teacher.ss()
                              , grouplist.ss() 
                              , result
    ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    return string(result.wide).asInt();
  }
}



int y::smartschool::savePassword(y::ldap::account& account) {
  /*xsd__anyType * result;
  if(service.savePassword(
          y::utils::Config().getSSPw().ss(),
          account.uid()().ss(),
          account.getPasswordText().ss(),
          0,
          result) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    if(result->soap_type() == SOAP_TYPE_xsd__int) {
      return ((xsd__int*)(result))->__item;
    }
  }*/
  return 0;
}

void y::smartschool::saveUser(y::ldap::account& account) {
  std::string role;
  if(!account.isStaff() && !account.isStudent()) return;
  
  if(account.role().get() == ROLE::DIRECTOR) {
    role = "Directie";
  } else if(account.isStaff()) {
    role = "Leerkracht";
  } else {
    role = "Leerling";
  }
  
  soap_dom_element result;
  if(service.saveUser(
          y::utils::Config().getSSPw().ss(),
          std::to_string(account.uidNumber().get()) , // internal number
          account.uid().get().ss()                 , // username
          account.getPasswordText().ss()       , // password
          "", // password for first co-account
          "", // password for second co-account
          account.cn().ss()                  , // first name
          account.sn().ss()                  , // last name
          "", // extra names
          "", // initials
          "", // sex
          "", // birthday
          "", // birthplace
          "", // birthcountry
          "", // street address
          "", // postal code
          "", // city
          "", // country
          account.mail().get().ss(), // email
          "", // mobile phone
          "", // home phone
          "", // fax
          "", // rijksregisternummer
          "", // stamboeknummer
          role, // basisrol
          "", // untisveld
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
  }
}

int y::smartschool::addUserToGroup(y::ldap::account& account, const string& group, bool keepCurrent) {
  soap_dom_element result;
  if(service.saveUserToClassesAndGroups(
          y::utils::Config().getSSPw().ss(),
          account.uid().get().ss(),
          group.ss(),
          keepCurrent,
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    //if(result->soap_type() == SOAP_TYPE_xsd__int) {
    //  return ((xsd__int*)(result))->__item;
    //}
  }
  return 0;
}

int y::smartschool::deleteUser(y::ldap::account& account, const string & removalDate) {
  soap_dom_element result;
  if(service.delUser(
          y::utils::Config().getSSPw().ss(),
          account.uid().get().ss(),
          removalDate.ss(), // official date
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    //if(result->soap_type() == SOAP_TYPE_xsd__int) {
    //  return ((xsd__int*)(result))->__item;
    //}
  }
  return 0;
}

int y::smartschool::addClass(y::ldap::schoolClass & group) {
  soap_dom_element result;
  string parent;
  
  switch(group.cn()[0]) {
    case '1': parent = "1stejaar"; break;
    case '2': parent = "2dejaar"; break;
    case '3': parent = "3dejaar"; break;
    case '4': parent = "4dejaar"; break;
    case '5': parent = "5dejaar"; break;
    case '6': parent = "6dejaar"; break;
    case '7': parent = "7dejaar"; break;
  }
  
  string description("Leerlingen ");
  description += group.cn(); 
  
  if(service.saveClass(
          y::utils::Config().getSSPw().ss() , // password smartschool
          group.cn().ss()                   , // group name
          description.ss()                  , // group description
          group.cn().ss()                   , // unique group ID
          parent.ss()                       , // parent for this group
          ""                                , // koppeling schoolagenda
          "125252"                          , // institute number
          "502"                             , // admin number
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    return string(result.wide).asInt();
  }
}

int y::smartschool::deleteClass(y::ldap::schoolClass & group) {
  soap_dom_element result;
  if(service.delClass(
          y::utils::Config().getSSPw().ss(), // password smartschool
          group.cn().ss()                  , // unique group ID
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return -1;
  } else {
    return string(result.wide).asInt();
  }
  return 0;
}

void y::smartschool::createErrorCodeTable(y::data::database & db) {
  y::data::row fields;
  fields.addInt("ID");
  fields["ID"].primaryKey(true).required(true);
  fields.addString("code");
  fields["code"].stringLength(512);

  db.createTable(SS_ERRORS, fields);

  // error 0 does not exists, so we abuse this value to
  // remember the last time we requested the error codes.
  // This saves us another table

  y::data::row row;
  row.addInt("ID", 0);
  time_t now = time(0);
  row.addString("code", string(now));
  db.addRow(SS_ERRORS, row);
  getErrorCodesFromSmartschool(db);
}

void y::smartschool::getErrorCodesFromSmartschool(y::data::database & db) {
  
  std::string result;
  if(service.returnCsvErrorCodes(result) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
  } else {
    std::wstring line;
    std::wstringstream resultStream;
    resultStream << strW(result);
    
    while(std::getline(resultStream, line)) {
      std::wstring item;
      std::vector<std::wstring> elms;
      
      for (unsigned int i = 0; i < line.size(); i++) {
        if(line[i] != ';') {
          item += line[i];
        } else {
          elms.push_back(std::move(item.c_str()));
          item.clear();
        }
      }
      
      if(elms.size() < 2) continue;
      
      y::data::row row;
      std::string::size_type sz;
      row.addInt("ID", std::stoi(elms[0], &sz));
      
      // erase quotes 
      elms[1].erase(0,1);
      elms[1].erase(elms[1].end()-1, elms[1].end());
      row.addString("code", string(elms[1]));
      db.addRow(SS_ERRORS, row);
    }
    
  }
}

void y::smartschool::loadErrorCodes(y::data::database& db) {
  container<y::data::row> rows;
  db.getAllRows(SS_ERRORS, rows);
  for(int i = 0; i < rows.elms(); i++) {
    errorTable[rows[i]["ID"].asInt()] = rows[i]["code"].asString();
  }
}

string y::smartschool::errorToText(int code) {
  // seems like ss didn't implement this code
  if(code == 9) {
    return string("Wrong username or password.");
  }
  if(errorTable.valid(code)) {
    return errorTable[code];
  }
  return string("no error found with this ID");
}
