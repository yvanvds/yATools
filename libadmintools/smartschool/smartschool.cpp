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
#include "utils/base64.h"
#include "utils/xmlParser.h"

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

bool y::smartschool::getUserDetails(const string& name, const string& password, y::data::row& details) {
  soap_dom_element result;
  
  if(service.isValidUserCredentials(y::utils::Config().getSSPw().ss(), 
                                    name.ss(), 
                                    password.ss(),
                                    result) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
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
   
  return true;
}

bool y::smartschool::addCourse(const string& name, const string& description) {
  std::string result;
  if(service.addCourse(y::utils::Config().getSSPw().ss(), name.ss(), description.ss(), result) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    // it's a string, but it always returns an int
    int error = std::stoi(result);
    if (error == 0) return true;
    y::utils::Log().add(errorToText(error));
    return false;
  } 
}

bool y::smartschool::getCourses(container<course> & result) {
  std::string stringResult;
  if(service.getCourses(
          y::utils::Config().getSSPw().ss(),
          stringResult
          )!= SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    std::string decoded = base64_decode(stringResult);
    
    tinyxml2::XMLDocument doc;
    doc.Parse(decoded.c_str(), decoded.length());
    
    if(doc.Error()) {
      y::utils::Log().add(string("xml error in smartschool::getCourses"));
    }
    
    tinyxml2::XMLElement * courses = nullptr;
    courses = doc.FirstChildElement("courses");
    if(courses == nullptr) return false;
    
    tinyxml2::XMLElement * c = nullptr;
    c = courses->FirstChildElement("course");

    while (c != nullptr) {
      course & newcourse = result.New();
    
      const tinyxml2::XMLElement * name = nullptr;
      name = c->FirstChildElement("name");
      if(name != nullptr) { 
        newcourse.name = name->GetText();
      }
      
      const tinyxml2::XMLElement * description = nullptr;
      description = c->FirstChildElement("description");
      if(description != nullptr) {
        newcourse.description = description->GetText();
      }
      
      const tinyxml2::XMLElement * active = nullptr;
      active = c->FirstChildElement("active");
      if(active != nullptr) {
        string value(active->GetText());
        newcourse.active = (value == "1");
      } 
      
      const tinyxml2::XMLElement * mainTeacher = nullptr;
      mainTeacher = c->FirstChildElement("mainTeacher");
      if(mainTeacher != nullptr) {
        const tinyxml2::XMLElement * firstName = nullptr;
        firstName = mainTeacher->FirstChildElement("firstname");
        if(firstName != nullptr) {
          newcourse.mainTeacher.firstname = firstName->GetText();
        }
        
        const tinyxml2::XMLElement * lastName = nullptr;
        lastName = mainTeacher->FirstChildElement("lastname");
        if(lastName != nullptr) {
          newcourse.mainTeacher.lastname = lastName->GetText();
        }
        
        const tinyxml2::XMLElement * userName = nullptr;
        userName = mainTeacher->FirstChildElement("username");
        if(userName != nullptr) {
          newcourse.mainTeacher.username = userName->GetText();
        }
        
        const tinyxml2::XMLElement * number = nullptr;
        number = mainTeacher->FirstChildElement("number");
        if(number != nullptr) {
          newcourse.mainTeacher.wisaID = number->GetText();
        }
        
      }
      
      TODO(Retrieve coTeachers)
      
      tinyxml2::XMLElement * studentGroups = nullptr;
      studentGroups = c->FirstChildElement("studentGroups");
      
      if(studentGroups != nullptr) {
        const tinyxml2::XMLElement * s = nullptr;
        s = studentGroups->FirstChildElement("studentGroup");
        
        while (s != nullptr) {
          studentGroup & g = newcourse.classes.New();
          
          const tinyxml2::XMLElement * name = nullptr;
          name = s->FirstChildElement("name");
          if(name != nullptr) {
            g.name = name->GetText();
          }
          
          const tinyxml2::XMLElement * description = nullptr;
          description = s->FirstChildElement("description");
          if(description != nullptr) {
            g.description = description->GetText();
          }
          
          const tinyxml2::XMLElement * type = nullptr;
          type = s->FirstChildElement("type");
          if(type != nullptr) {
            g.type = type->GetText();
          }
          
          s = s->NextSiblingElement();
        }
      }
              
      c = c->NextSiblingElement();
    }

    return true;
  }
}

bool y::smartschool::setCourseStudents(const string& courseName, const string& courseDescription, container<string>& groupIDs) {
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
    return false;
  } else {
    return validateSoapResult(result);
  }
}

bool y::smartschool::setCourseTeachers(const string& courseName, const string& courseDescription, const string & teacher, container<string> * coTeachers) {
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
    return false;
  } else {
    return validateSoapResult(result);
  }
}



bool y::smartschool::savePassword(const y::ldap::account& account) {
  soap_dom_element result;
  
  if(service.savePassword(
          y::utils::Config().getSSPw().ss(),
          account.uid().get().ss(),
          account.getPasswordText().ss(),
          0,
          result) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    return validateSoapResult(result);
  }
}

bool y::smartschool::setCoAccount(const string & uid, const string& pw, bool firstAccount) {
  soap_dom_element result;
  
  if(service.savePassword(
          y::utils::Config().getSSPw().ss(),
          uid.ss(),
          pw.ss(),
          firstAccount ? 1 : 2,
          result) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    return validateSoapResult(result);
  }
}

bool y::smartschool::saveUser(const y::ldap::account& account) {
  string role;
  if(!account.isStaff() && !account.isStudent()) return false;
  
  if(account.role().get() == ROLE::DIRECTOR) {
    role = "Directie";
  } else if(account.isStaff()) {
    role = "Leerkracht";
  } else {
    role = "Leerling";
  }
  
  string gender("m");
  if(account.gender().get() == GENDER::FEMALE) {
    gender = "v";
  }
  
  string streetAddress = account.street().get();
  streetAddress += " ";
  streetAddress += account.houseNumber().get();
  if (account.houseNumberAdd().get().size()) {
    streetAddress += " bus ";
    streetAddress += account.houseNumberAdd().get();
  }
  
  string birthDay = string(account.birthDay().getYear());
  birthDay += "-"; birthDay += string(account.birthDay().getMonth());
  birthDay += "-"; birthDay += string(account.birthDay().getDay());
  
  string wisaID = getAccountID(account);
  
  string stamboekNummer(account.stemID().get());
  if(account.stemID().get() < 1000000) {
    stamboekNummer = string("0") + stamboekNummer;
  }
  
  soap_dom_element result;
 
  if(service.saveUser(
          y::utils::Config().getSSPw().ss(),
          wisaID.ss() , // internal number
          account.uid().get().ss()                 , // username
          account.getPasswordText().ss()       , // password
          "", // password for first co-account
          "", // password for second co-account
          account.cn().get().ss()                  , // first name
          account.sn().get().ss()                  , // last name
          "", // extra names
          "", // initials
          gender.ss(), // sex
          birthDay.ss(), // birthday
          account.birthPlace().get().ss(), // birthplace
          "", // birthcountry
          streetAddress.ss(), // street address
          account.postalCode().get().ss(), // postal code
          account.city().get().ss(), // city
          account.country().get().ss(), // country
          account.mail().get().ss(), // email
          "", // mobile phone
          "", // home phone
          "", // fax
          account.registerID().get().ss(), // rijksregisternummer
          stamboekNummer.ss(), // stamboeknummer
          role.ss(), // basisrol
          "", // untisveld
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    // perhaps an existing user does not exist in smartschool
    // in this case we have to make up a temporary password and 
    // try again
    if(string(result.wide).asInt() == 4) {
      soap_dom_element result;
      if(service.saveUser(
              y::utils::Config().getSSPw().ss(),
              wisaID.ss() , // internal number
              account.uid().get().ss()                 , // username
              "UnknowNP4ss"       , // password
              "", // password for first co-account
              "", // password for second co-account
              account.cn().get().ss()                  , // first name
              account.sn().get().ss()                  , // last name
              "", // extra names
              "", // initials
              gender.ss(), // sex
              birthDay.ss(), // birthday
              account.birthPlace().get().ss(), // birthplace
              "", // birthcountry
              streetAddress.ss(), // street address
              account.postalCode().get().ss(), // postal code
              account.city().get().ss(), // city
              account.country().get().ss(), // country
              account.mail().get().ss(), // email
              "", // mobile phone
              "", // home phone
              "", // fax
              account.registerID().get().ss(), // rijksregisternummer
              stamboekNummer.ss(), // stamboeknummer
              role.ss(), // basisrol
              "", // untisveld
              result
              ) != SOAP_OK) {
        service.soap_stream_fault(std::cerr);
      } else {
        return validateSoapResult(result);
      }
    }
    return validateSoapResult(result);
  }
}

bool y::smartschool::saveNationality(const y::ldap::account & account) {
  string ID = getAccountID(account);
  return saveUserParam(ID, "Nationalititeit", account.nationality().get());
}

bool y::smartschool::validate(const string & username, const string & password) {
  soap_dom_element result;
  if(service.isValidUserCredentials(
          y::utils::Config().getSSPw().ss(),
          username.ss(),
          password.ss(),
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    Wt::Json::Object data;
    Wt::Json::ParseError error;
    if(!Wt::Json::parse(string(result.wide).utf8(), data, error)) {
      return validateSoapResult(result);
    } else {
      return true;
    }
  }
}

bool y::smartschool::addUserToGroup(const y::ldap::account& account, const string& group, bool keepCurrent) {
  soap_dom_element result;
  if(service.saveUserToClassesAndGroups(
          y::utils::Config().getSSPw().ss(),
          account.uid().get().ss(),
          group.ss(),
          keepCurrent,
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    return validateSoapResult(result);
  }

}

bool y::smartschool::moveUserToClass(const y::ldap::account& account, const string & group) {
  soap_dom_element result;
  
  string user = account.uid().get();
  string changeDate = string(account.classChange().getYear());
  changeDate += "-"; changeDate += string(account.classChange().getMonth());
  changeDate += "-"; changeDate += string(account.classChange().getDay());
  
  if(service.saveUserToClass(
          y::utils::Config().getSSPw().ss(),
          user.ss(),
          group.ss(), 
          changeDate.ss(),
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    return validateSoapResult(result);
  }
}

bool y::smartschool::saveUserParam(const string& ID, const string& param, const string& value) {
  soap_dom_element result;
  if(service.saveUserParameter(
          y::utils::Config().getSSPw().ss(),
          ID.ss(),
          param.ss(),
          value.ss(),
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  }
  return validateSoapResult(result);
}

bool y::smartschool::deleteUser(const y::ldap::account& account) {
  soap_dom_element result;
  
  string changeDate = string(account.classChange().getYear());
  changeDate += "-"; changeDate += string(account.classChange().getMonth());
  changeDate += "-"; changeDate += string(account.classChange().getDay());  
  
  if(service.delUser(
          y::utils::Config().getSSPw().ss(),
          account.uid().get().ss(),
          changeDate.ss(), // official date
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    return validateSoapResult(result);
  }
}

bool y::smartschool::saveClass(const y::ldap::schoolClass & group) {
  soap_dom_element result;
  string parent;
  
  switch(group.cn().get()[0]) {
    case '1': parent = "1stejaar"; break;
    case '2': parent = "2dejaar"; break;
    case '3': parent = "3dejaar"; break;
    case '4': parent = "4dejaar"; break;
    case '5': parent = "5dejaar"; break;
    case '6': parent = "6dejaar"; break;
    case '7': parent = "7dejaar"; break;
  }
  
  string description("Leerlingen ");
  description += group.cn().get(); 
  
  if(service.saveClass(
          y::utils::Config().getSSPw().ss() , // password smartschool
          group.cn().get().ss()                   , // group name
          group.description().get().ss()          , // group description
          group.cn().get().ss()                   , // unique group ID
          parent.ss()                       , // parent for this group
          ""                                , // koppeling schoolagenda
          string(group.schoolID  ().get()).ss(), // institute number
          string(group.adminGroup().get()).ss(), // admin number
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } else {
    return validateSoapResult(result);
  }
}

bool y::smartschool::deleteClass(const y::ldap::schoolClass & group) {
  soap_dom_element result;
  if(service.delClass(
          y::utils::Config().getSSPw().ss(), // password smartschool
          group.cn().get().ss()                  , // unique group ID
          result
          ) != SOAP_OK) {
    service.soap_stream_fault(std::cerr);
    return false;
  } 
  
  return validateSoapResult(result);
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

string y::smartschool::getAccountID(const y::ldap::account& account) {
  if(account.isStaff()) return account.wisaName().get();
  else return string(account.wisaID().get());
}

bool y::smartschool::validateSoapResult(soap_dom_element& result) {
  int error = string(result.wide).asInt();
  if (error == 0) return true;
  y::utils::Log().add(errorToText(error));
  return false;
}