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
//#include "ldap/account.h"

y::smartschool & y::Smartschool() {
  static smartschool s;
  return s;
}

y::smartschool::smartschool() {

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