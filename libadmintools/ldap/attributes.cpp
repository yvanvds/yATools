/* 
 * File:   attributes.cpp
 * Author: yvan
 * 
 * Created on January 14, 2014, 5:42 PM
 */

#include "attributes.h"
#include "utils/log.h"
#include <sstream>
#include <stdexcept>
#include "utils/convert.h"

const string & DN::operator ()() const {
  return val;
}

DN & DN::operator =(const DN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool DN::operator ==(const DN& ref) const{
  return val == ref.val;
}

bool DN::operator !=(const DN& ref) const{
  return val != ref.val;
}

int UID_NUMBER::operator ()() const{
  return val;
}

bool UID_NUMBER::operator ==(const UID_NUMBER& ref) const{
  return val == ref.val;
}

bool UID_NUMBER::operator !=(const UID_NUMBER& ref) const{
  return val != ref.val;
}

const string & UID::operator ()() const {
  return val;
}

UID & UID::operator =(const UID& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool UID::operator ==(const UID& ref) const{
  return val == ref.val;
}

bool UID::operator !=(const UID& ref) const{
  return val != ref.val;
}

FULL_NAME::FULL_NAME(const string & cn, const string & sn) {
  val = cn;
  val += " ";
  val += sn;
}

const string & FULL_NAME::operator ()() const {
  return val;
}

FULL_NAME & FULL_NAME::operator =(const FULL_NAME& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool FULL_NAME::operator ==(const FULL_NAME& ref) const{
  return val == ref.val;
}

bool FULL_NAME::operator !=(const FULL_NAME& ref) const{
  return val != ref.val;
}

string ROLE::toText(TYPE value) {
  switch(value) {
    case TEACHER : return "teacher";
    case STUDENT : return "student";
    case DIRECTOR: return "director";
    case ADMIN   : return "admin";
    case SUPPORT : return "support";
    case EXTERN  : return "extern";
    case EXTERN_WITH_MAIL: return "externmail";
    default: return "none";
  }
}

ROLE::TYPE ROLE::toRole(const string & value) {
  if(value == "teacher"   ) return TEACHER;
  if(value == "student"   ) return STUDENT;
  if(value == "director"  ) return DIRECTOR;
  if(value == "admin"     ) return ADMIN;
  if(value == "support"   ) return SUPPORT;
  if(value == "extern"    ) return EXTERN;
  if(value == "externmail") return EXTERN_WITH_MAIL;
  return NONE;
}

ROLE::TYPE ROLE::operator ()() const {
  return val;
}

ROLE & ROLE::operator =(const ROLE& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ROLE::operator ==(const ROLE & ref) const{
  return val == ref.val;
}

bool ROLE::operator !=(const ROLE & ref) const{
  return val != ref.val;
}

int GID_NUMBER::operator()() const {
  return val;
}

GID_NUMBER & GID_NUMBER::operator=(const GID_NUMBER &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool GID_NUMBER::operator==(const GID_NUMBER &ref) const{
  return val == ref.val;
}

bool GID_NUMBER::operator!=(const GID_NUMBER &ref) const {
  return val != ref.val;
}

int WISA_ID::operator()() const {
  return val;
}

WISA_ID & WISA_ID::operator=(const WISA_ID &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool WISA_ID::operator==(const WISA_ID &ref) const{
  return val == ref.val;
}

bool WISA_ID::operator!=(const WISA_ID &ref) const {
  return val != ref.val;
}

const string & MAIL::operator ()() const {
  return val;
}

MAIL & MAIL::operator =(const MAIL& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool MAIL::operator ==(const MAIL & ref) const{
  return val == ref.val;
}

bool MAIL::operator !=(const MAIL & ref) const{
  return val != ref.val;
}

const string & PASSWORD::operator ()() const {
  return val;
}

PASSWORD & PASSWORD::operator =(const PASSWORD& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool PASSWORD::operator ==(const PASSWORD & ref) const{
  return val == ref.val;
}

bool PASSWORD::operator !=(const PASSWORD & ref) const{
  return val != ref.val;
}

int DAY::operator()() const {
  return val;
}

DAY::DAY(int val) : val(val) {
  if(this->val <  1) this->val =  1;
  if(this->val > 31) this->val = 31;
}

DAY & DAY::operator=(const DAY &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool DAY::operator==(const DAY &ref) const{
  return val == ref.val;
}

bool DAY::operator!=(const DAY &ref) const {
  return val != ref.val;
}

MONTH::MONTH(int val) : val(val) {
  if(this->val <  1) this->val =  1;
  if(this->val > 12) this->val = 12;
}

int MONTH::operator()() const {
  return val;
}

MONTH & MONTH::operator=(const MONTH &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool MONTH::operator==(const MONTH &ref) const{
  return val == ref.val;
}

bool MONTH::operator!=(const MONTH &ref) const {
  return val != ref.val;
}

int YEAR::operator()() const {
  return val;
}

YEAR & YEAR::operator=(const YEAR &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool YEAR::operator==(const YEAR &ref) const{
  return val == ref.val;
}

bool YEAR::operator!=(const YEAR &ref) const {
  return val != ref.val;
}



DATE::DATE(const string & date, bool fromWisa) : day(1), month(1), year(1) {
  if(fromWisa) {
    int currentValue = 0;
    std::wstring value;
    for(unsigned int i = 0; i < date.size(); i++) {
      if(date[i] != '/') {
        value += date[i];
      } else {
        switch (currentValue) {
          case 0: {
            day = DAY(std::stoi(str8(value)));
            currentValue++;
            break;
          }
          case 1: {
            month = MONTH(std::stoi(str8(value)));
            currentValue++;
            break;
          }
        }
        value.clear();
      }
    }
    year = YEAR(std::stoi(str8(value)));
    return;
  }
  
  int i;
  try {
    i = date.asInt();
  } catch(const std::invalid_argument &e) {
    string message("Invalid ldap::DATE conversion: ");
    message += date;
    y::utils::Log().add(message);
    return;
  }
  day = DAY(i % 100);
  i /= 100;
  month = MONTH(i % 100);
  i /= 100;
  year = YEAR(i);
}

DATE::DATE(const DAY& day, const MONTH& month, const YEAR& year) 
        : day(day), month(month), year(year) {}

int DATE::operator ()() const {
  int result = year();
  result *= 100;
  result += month();
  result *= 100;
  result += day();
  return result;
}

string DATE::asString() const {
  std::stringstream result;
  result << day();
  switch(month()) {
    case 1: result << " januari "; break;
    case 2: result << " februari "; break;
    case 3: result << " maart "; break;
    case 4: result << " april "; break;
    case 5: result << " mei "; break;
    case 6: result << " juni "; break;
    case 7: result << " juli "; break;
    case 8: result << " augustus "; break;
    case 9: result << " september "; break;
    case 10: result << " oktober "; break;
    case 11: result << " november "; break;
    case 12: result << " december "; break;
  }
  result << year();
  std::string s = result.str();
  return string(s);
}

int DATE::getDay() const {
  return day();
}

int DATE::getMonth() const {
  return month();
}

int DATE::getYear() const {
  return year();
}

DATE & DATE::operator =(const DATE& ref) {
  if(this != &ref) {
    day = ref.day;
    month = ref.month;
    year = ref.year;
  }
  return *this;
}

bool DATE::operator ==(const DATE& ref) const {
  return (day == ref.day && month == ref.month && year == ref.year);
}

bool DATE::operator !=(const DATE& ref) const {
  return (day != ref.day || month != ref.month || year != ref.year);
}

const string & HOMEDIR::operator ()() const {
  return val;
}

HOMEDIR & HOMEDIR::operator =(const HOMEDIR& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool HOMEDIR::operator ==(const HOMEDIR & ref) const{
  return val == ref.val;
}

bool HOMEDIR::operator !=(const HOMEDIR & ref) const{
  return val != ref.val;
}

