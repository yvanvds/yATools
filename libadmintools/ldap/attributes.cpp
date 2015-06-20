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
#include "defines.h"

TODO(is there really no way to template these attributes?)

///////////////////////////////////////
// DN
///////////////////////////////////////

const string & DN::get() const {
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

///////////////////////////////////////
// UID_NUMBER
///////////////////////////////////////

int UID_NUMBER::get() const{
  return val;
}

bool UID_NUMBER::operator ==(const UID_NUMBER& ref) const{
  return val == ref.val;
}

bool UID_NUMBER::operator !=(const UID_NUMBER& ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// UID
///////////////////////////////////////

const string & UID::get() const {
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

///////////////////////////////////////
// CN
///////////////////////////////////////

const string & CN::get() const {
  return val;
}

CN & CN::operator =(const CN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool CN::operator ==(const CN& ref) const{
  return val == ref.val;
}

bool CN::operator !=(const CN& ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// SN
///////////////////////////////////////

const string & SN::get() const {
  return val;
}

SN & SN::operator =(const SN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool SN::operator ==(const SN& ref) const{
  return val == ref.val;
}

bool SN::operator !=(const SN& ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// FULL_NAME
///////////////////////////////////////

FULL_NAME::FULL_NAME(const string & cn, const string & sn) {
  val = cn;
  val += " ";
  val += sn;
}

const string & FULL_NAME::get() const {
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

///////////////////////////////////////
// ROLE
///////////////////////////////////////

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

ROLE::TYPE ROLE::get() const {
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

///////////////////////////////////////
// GID_NUMBER
///////////////////////////////////////

int GID_NUMBER::get() const {
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

///////////////////////////////////////
// WISA_ID
///////////////////////////////////////

int WISA_ID::get() const {
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


///////////////////////////////////////
// WISA_NAME
///////////////////////////////////////

const string & WISA_NAME::get() const {
  return val;
}

WISA_NAME & WISA_NAME::operator =(const WISA_NAME& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool WISA_NAME::operator ==(const WISA_NAME& ref) const{
  return val == ref.val;
}

bool WISA_NAME::operator !=(const WISA_NAME& ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// PASSWORD
///////////////////////////////////////

const string & PASSWORD::get() const {
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

///////////////////////////////////////
// MAIL
///////////////////////////////////////

const string & MAIL::get() const {
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

///////////////////////////////////////
// MAIL_ALIAS
///////////////////////////////////////

const string & MAIL_ALIAS::get() const {
  return val;
}

MAIL_ALIAS & MAIL_ALIAS::operator =(const MAIL_ALIAS& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool MAIL_ALIAS::operator ==(const MAIL_ALIAS & ref) const{
  return val == ref.val;
}

bool MAIL_ALIAS::operator !=(const MAIL_ALIAS & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// DAY
///////////////////////////////////////

int DAY::get() const {
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

///////////////////////////////////////
// MONTH
///////////////////////////////////////

MONTH::MONTH(int val) : val(val) {
  if(this->val <  1) this->val =  1;
  if(this->val > 12) this->val = 12;
}

int MONTH::get() const {
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

///////////////////////////////////////
// YEAR
///////////////////////////////////////

int YEAR::get() const {
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

///////////////////////////////////////
// DATE
///////////////////////////////////////

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

int DATE::asInt() const {
  int result = year.get();
  result *= 100;
  result += month.get();
  result *= 100;
  result += day.get();
  return result;
}

string DATE::get() const {
  std::stringstream result;
  result << day.get();
  switch(month.get()) {
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
  result << year.get();
  std::string s = result.str();
  return string(s);
}

int DATE::getDay() const {
  return day.get();
}

int DATE::getMonth() const {
  return month.get();
}

int DATE::getYear() const {
  return year.get();
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

///////////////////////////////////////
// HOMEDIR
///////////////////////////////////////

const string & HOMEDIR::get() const {
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

///////////////////////////////////////
// BIRTHPLACE
///////////////////////////////////////

const string & BIRTHPLACE::get() const {
  return val;
}

BIRTHPLACE & BIRTHPLACE::operator =(const BIRTHPLACE& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool BIRTHPLACE::operator ==(const BIRTHPLACE & ref) const{
  return val == ref.val;
}

bool BIRTHPLACE::operator !=(const BIRTHPLACE & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// SCHOOLCLASS
///////////////////////////////////////

const string & SCHOOLCLASS::get() const {
  return val;
}

SCHOOLCLASS & SCHOOLCLASS::operator =(const SCHOOLCLASS & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool SCHOOLCLASS::operator ==(const SCHOOLCLASS & ref) const{
  return val == ref.val;
}

bool SCHOOLCLASS::operator !=(const SCHOOLCLASS & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// GENDER
///////////////////////////////////////

string GENDER::toText(TYPE value) {
  switch(value) {
    case MALE       : return "male";
    case FEMALE     : return "female";
    case TRANSGENDER: return "transgender";
    default: return "none";
  }
}

GENDER::TYPE GENDER::toGender(const string & value) {
  if(value == "male"       ) return MALE;
  if(value == "female"     ) return FEMALE;
  if(value == "transgender") return TRANSGENDER;
  return NONE;
}

GENDER::TYPE GENDER::get() const {
  return val;
}

GENDER & GENDER::operator =(const GENDER & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool GENDER::operator ==(const GENDER & ref) const{
  return val == ref.val;
}

bool GENDER::operator !=(const GENDER & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// ADMINGROUP
///////////////////////////////////////

int ADMINGROUP::get() const {
  return val;
}

ADMINGROUP & ADMINGROUP::operator=(const ADMINGROUP &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ADMINGROUP::operator==(const ADMINGROUP &ref) const{
  return val == ref.val;
}

bool ADMINGROUP::operator!=(const ADMINGROUP &ref) const {
  return val != ref.val;
}

///////////////////////////////////////
// REGISTER_ID
///////////////////////////////////////

const string & REGISTER_ID::get() const {
  return val;
}

REGISTER_ID & REGISTER_ID::operator =(const REGISTER_ID & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool REGISTER_ID::operator ==(const REGISTER_ID & ref) const{
  return val == ref.val;
}

bool REGISTER_ID::operator !=(const REGISTER_ID & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// NATION
///////////////////////////////////////

const string & NATION::get() const {
  return val;
}

NATION & NATION::operator =(const NATION & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool NATION::operator ==(const NATION & ref) const{
  return val == ref.val;
}

bool NATION::operator !=(const NATION & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// STEM_ID
///////////////////////////////////////

int STEM_ID::get() const {
  return val;
}

STEM_ID & STEM_ID::operator=(const STEM_ID &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool STEM_ID::operator==(const STEM_ID &ref) const{
  return val == ref.val;
}

bool STEM_ID::operator!=(const STEM_ID &ref) const {
  return val != ref.val;
}

///////////////////////////////////////
// SCHOOL_ID
///////////////////////////////////////

int SCHOOL_ID::get() const {
  return val;
}

SCHOOL_ID & SCHOOL_ID::operator=(const SCHOOL_ID &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool SCHOOL_ID::operator==(const SCHOOL_ID &ref) const{
  return val == ref.val;
}

bool SCHOOL_ID::operator!=(const SCHOOL_ID &ref) const {
  return val != ref.val;
}

///////////////////////////////////////
// DESCRIPTION
///////////////////////////////////////

const string & DESCRIPTION::get() const {
  return val;
}

DESCRIPTION & DESCRIPTION::operator =(const DESCRIPTION & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool DESCRIPTION::operator ==(const DESCRIPTION & ref) const{
  return val == ref.val;
}

bool DESCRIPTION::operator !=(const DESCRIPTION & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// ADJUNCT
///////////////////////////////////////

const DN & ADJUNCT::get() const {
  return val;
}

ADJUNCT & ADJUNCT::operator =(const ADJUNCT & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ADJUNCT::operator ==(const ADJUNCT & ref) const{
  return val == ref.val;
}

bool ADJUNCT::operator !=(const ADJUNCT & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// TITULAR
///////////////////////////////////////

const DN & TITULAR::get() const {
  return val;
}

TITULAR & TITULAR::operator =(const TITULAR & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool TITULAR::operator ==(const TITULAR & ref) const{
  return val == ref.val;
}

bool TITULAR::operator !=(const TITULAR & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// MEMBER
///////////////////////////////////////

const DN & MEMBER::get() const {
  return val;
}

MEMBER & MEMBER::operator =(const MEMBER & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool MEMBER::operator ==(const MEMBER & ref) const{
  return val == ref.val;
}

bool MEMBER::operator !=(const MEMBER & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// COUNTRY
///////////////////////////////////////

const string & COUNTRY::get() const {
  return val;
}

COUNTRY & COUNTRY::operator =(const COUNTRY & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool COUNTRY::operator ==(const COUNTRY & ref) const{
  return val == ref.val;
}

bool COUNTRY::operator !=(const COUNTRY & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// STREET
///////////////////////////////////////

const string & STREET::get() const {
  return val;
}

STREET & STREET::operator =(const STREET & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool STREET::operator ==(const STREET & ref) const{
  return val == ref.val;
}

bool STREET::operator !=(const STREET & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// HOUSENUMBER
///////////////////////////////////////

int HOUSENUMBER::get() const {
  return val;
}

HOUSENUMBER & HOUSENUMBER::operator=(const HOUSENUMBER &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool HOUSENUMBER::operator==(const HOUSENUMBER &ref) const{
  return val == ref.val;
}

bool HOUSENUMBER::operator!=(const HOUSENUMBER &ref) const {
  return val != ref.val;
}

///////////////////////////////////////
// HOUSENUMBER_ADD
///////////////////////////////////////

const string & HOUSENUMBER_ADD::get() const {
  return val;
}

HOUSENUMBER_ADD & HOUSENUMBER_ADD::operator =(const HOUSENUMBER_ADD & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool HOUSENUMBER_ADD::operator ==(const HOUSENUMBER_ADD & ref) const{
  return val == ref.val;
}

bool HOUSENUMBER_ADD::operator !=(const HOUSENUMBER_ADD & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// CITY
///////////////////////////////////////

const string & CITY::get() const {
  return val;
}

CITY & CITY::operator =(const CITY & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool CITY::operator ==(const CITY & ref) const{
  return val == ref.val;
}

bool CITY::operator !=(const CITY & ref) const{
  return val != ref.val;
}

///////////////////////////////////////
// POSTAL_CODE
///////////////////////////////////////

const string & POSTAL_CODE::get() const {
  return val;
}

POSTAL_CODE & POSTAL_CODE::operator =(const POSTAL_CODE & ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool POSTAL_CODE::operator ==(const POSTAL_CODE & ref) const{
  return val == ref.val;
}

bool POSTAL_CODE::operator !=(const POSTAL_CODE & ref) const{
  return val != ref.val;
}

