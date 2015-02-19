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
#include "data/database.h"


//#include "ldap/account.h"

y::smartschool & y::Smartschool() {
  static smartschool s;
  return s;
}

y::smartschool::smartschool() {
  server = std::unique_ptr<y::data::server  >(new y::data::server);
  db     = std::unique_ptr<y::data::database>(new y::data::database(*server));
  
  if(!server->hasDatabase(L"admintools")) {
    server->create(L"admintools");
  }
  db->use(L"admintools");
  
  if(!db->tableExists(SS_ERRORS)) {
    y::data::row fields;
    fields.addInt(L"ID");
    fields[L"ID"].primaryKey(true).required(true);
    fields.addString(L"code");
    fields[L"code"].stringLength(512);
    
    db->createTable(SS_ERRORS, fields);
    
    // error 0 does not exists, so we abuse this value to
    // remember the last time we requested the error codes.
    // This saves us another table
    
    y::data::row row;
    row.addInt(L"ID", 0);
    time_t now = time(0);
    row.addString(L"code", std::to_wstring(now));
    db->addRow(SS_ERRORS, row);
    getErrorCodes();
  } else {
    container<y::data::row> rows;
    y::data::field condition;
    condition.name(L"ID").setInt(0);
    db->getRows(SS_ERRORS, rows, condition);
    if(rows.elms()) {
      std::string::size_type sz;
      int lasttime = std::stoi(rows[0][L"code"].asString(), &sz);
      time_t now = time(0);
      std::cout << "last " << lasttime << std::endl;
      std::cout << "now " << now << std::endl;
    }
  }
}

y::smartschool::~smartschool() {
  service.destroy();
}

void y::smartschool::addCourse(const std::string& name, const std::string& description) {
  std::string result;
  if(service.addCourse(str8(y::utils::Config().getSSPw()), name, description, result) == SOAP_OK) {
  } else {
    service.soap_stream_fault(std::cerr);
  } 
}

void y::smartschool::addGroupsToCourse(const std::string& courseName, const std::string& courseDescription, container<std::string>& groupIDs) {
  std::string result;
  std::string grouplist;
  for(int i = 0; i < groupIDs.elms(); i++) {
    grouplist += groupIDs[i];
    if(i < groupIDs.elms() - 1);
    grouplist += ',';
  }
  
  // todo
  //if(service.addCourseStudents(y::utils::Config().getSSPw(), courseName, courseDescription, grouplist, result) != SOAP_OK) {
  //  service.soap_stream_fault(std::cerr);
  //}
}

void y::smartschool::saveUser(y::ldap::account& account) {
  std::string role;
  if(account.group()().compare(L"extern") == 0) return;
  if(account.group()().compare(L"externmail") == 0) return;
  
  if(account.group()().compare(L"directie") == 0) {
    role = "directie";
  } else if(account.group()().compare(L"personeel") == 0) {
    role = "leerkracht";
  } else {
    role = "leerling";
  }
  
  xsd__anyType * result;
  if(service.saveUser(
          str8(y::utils::Config().getSSPw()),
          std::to_string(account.uidNumber()()), 
          str8(account.uid()()),
          str8(account.getPasswordText()),
          "", // password for first co-account
          "", // password for second co-account
          str8(account.cn()()), // first name
          str8(account.sn()()), // last name
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
          str8(account.mail()()), // email
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

void y::smartschool::getErrorCodes() {
  
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
      row.addInt(L"ID", std::stoi(elms[0], &sz));
      
      // erase quotes 
      elms[1].erase(0,1);
      elms[1].erase(elms[1].end()-1, elms[1].end());
      row.addString(L"code", elms[1]);
      db->addRow(SS_ERRORS, row);
    }
    
  }
}