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

const std::wstring & y::ldap::DN::operator ()() const {
  return val;
}

y::ldap::DN & y::ldap::DN::operator =(const DN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::DN::operator ==(const DN& ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::DN::operator !=(const DN& ref) const{
  return val.compare(ref.val) != 0;
}

int y::ldap::UID_NUMBER::operator ()() const{
  return val;
}

bool y::ldap::UID_NUMBER::operator ==(const UID_NUMBER& ref) const{
  return val == ref.val;
}

bool y::ldap::UID_NUMBER::operator !=(const UID_NUMBER& ref) const{
  return val != ref.val;
}

const std::wstring & y::ldap::UID::operator ()() const {
  return val;
}

y::ldap::UID & y::ldap::UID::operator =(const UID& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::UID::operator ==(const UID& ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::UID::operator !=(const UID& ref) const{
  return val.compare(ref.val) != 0;
}

const std::wstring & y::ldap::CN::operator ()() const {
  return val;
}

y::ldap::CN & y::ldap::CN::operator =(const CN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::CN::operator ==(const CN& ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::CN::operator !=(const CN& ref) const{
  return val.compare(ref.val) != 0;
}

const std::wstring & y::ldap::SN::operator ()() const {
  return val;
}

y::ldap::SN & y::ldap::SN::operator =(const SN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::SN::operator ==(const SN& ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::SN::operator !=(const SN& ref) const{
  return val.compare(ref.val) != 0;
}

y::ldap::FULL_NAME::FULL_NAME(const CN& cn, const SN& sn) {
  val = cn();
  val += L" ";
  val += sn();
}

const std::wstring & y::ldap::FULL_NAME::operator ()() const {
  return val;
}

y::ldap::FULL_NAME & y::ldap::FULL_NAME::operator =(const FULL_NAME& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::FULL_NAME::operator ==(const FULL_NAME& ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::FULL_NAME::operator !=(const FULL_NAME& ref) const{
  return val.compare(ref.val) != 0;
}

const std::wstring & y::ldap::GID::operator ()() const {
  return val;
}

y::ldap::GID & y::ldap::GID::operator =(const GID& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::GID::operator ==(const GID & ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::GID::operator !=(const GID & ref) const{
  return val.compare(ref.val) != 0;
}

int y::ldap::GID_NUMBER::operator()() const {
  return val;
}

y::ldap::GID_NUMBER & y::ldap::GID_NUMBER::operator=(const GID_NUMBER &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::GID_NUMBER::operator==(const GID_NUMBER &ref) const{
  return val == ref.val;
}

bool y::ldap::GID_NUMBER::operator!=(const GID_NUMBER &ref) const {
  return val != ref.val;
}

int y::ldap::WISA_ID::operator()() const {
  return val;
}

y::ldap::WISA_ID & y::ldap::WISA_ID::operator=(const WISA_ID &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::WISA_ID::operator==(const WISA_ID &ref) const{
  return val == ref.val;
}

bool y::ldap::WISA_ID::operator!=(const WISA_ID &ref) const {
  return val != ref.val;
}

const std::wstring & y::ldap::MAIL::operator ()() const {
  return val;
}

y::ldap::MAIL & y::ldap::MAIL::operator =(const MAIL& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::MAIL::operator ==(const MAIL & ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::MAIL::operator !=(const MAIL & ref) const{
  return val.compare(ref.val) != 0;
}

const std::wstring & y::ldap::PASSWORD::operator ()() const {
  return val;
}

y::ldap::PASSWORD & y::ldap::PASSWORD::operator =(const PASSWORD& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::PASSWORD::operator ==(const PASSWORD & ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::PASSWORD::operator !=(const PASSWORD & ref) const{
  return val.compare(ref.val) != 0;
}

int y::ldap::DAY::operator()() const {
  return val;
}

y::ldap::DAY::DAY(int val) : val(val) {
  if(this->val <  1) this->val =  1;
  if(this->val > 31) this->val = 31;
}

y::ldap::DAY & y::ldap::DAY::operator=(const DAY &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::DAY::operator==(const DAY &ref) const{
  return val == ref.val;
}

bool y::ldap::DAY::operator!=(const DAY &ref) const {
  return val != ref.val;
}

y::ldap::MONTH::MONTH(int val) : val(val) {
  if(this->val <  1) this->val =  1;
  if(this->val > 12) this->val = 12;
}

int y::ldap::MONTH::operator()() const {
  return val;
}

y::ldap::MONTH & y::ldap::MONTH::operator=(const MONTH &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::MONTH::operator==(const MONTH &ref) const{
  return val == ref.val;
}

bool y::ldap::MONTH::operator!=(const MONTH &ref) const {
  return val != ref.val;
}

int y::ldap::YEAR::operator()() const {
  return val;
}

y::ldap::YEAR & y::ldap::YEAR::operator=(const YEAR &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::YEAR::operator==(const YEAR &ref) const{
  return val == ref.val;
}

bool y::ldap::YEAR::operator!=(const YEAR &ref) const {
  return val != ref.val;
}



y::ldap::DATE::DATE(const std::wstring & date, bool fromWisa) : day(1), month(1), year(1) {
  if(fromWisa) {
    int currentValue = 0;
    std::wstring value;
    for(int i = 0; i < date.size(); i++) {
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
          case 2: {
            year = YEAR(std::stoi(str8(value)));
            currentValue++;
            break;
          }
        }
        value.clear();
      }
    }
    return;
  }
  
  int i;
  try {
    i = std::stoi(str8(date));
  } catch(const std::invalid_argument &e) {
    std::wstring message(L"Invalid ldap::DATE conversion: ");
    message += date;
    utils::Log().add(message);
    return;
  }
  day = DAY(i % 100);
  i /= 100;
  month = MONTH(i % 100);
  i /= 100;
  year = YEAR(i);
}

y::ldap::DATE::DATE(const DAY& day, const MONTH& month, const YEAR& year) 
        : day(day), month(month), year(year) {}

int y::ldap::DATE::operator ()() const {
  int result = year();
  result *= 100;
  result += month();
  result *= 100;
  result += day();
  return result;
}

std::wstring y::ldap::DATE::asString() const {
  std::wstringstream result;
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
  return result.str();
}

int y::ldap::DATE::getDay() const {
  return day();
}

int y::ldap::DATE::getMonth() const {
  return month();
}

int y::ldap::DATE::getYear() const {
  return year();
}

y::ldap::DATE & y::ldap::DATE::operator =(const DATE& ref) {
  if(this != &ref) {
    day = ref.day;
    month = ref.month;
    year = ref.year;
  }
  return *this;
}

bool y::ldap::DATE::operator ==(const DATE& ref) const {
  return (day == ref.day && month == ref.month && year == ref.year);
}

bool y::ldap::DATE::operator !=(const DATE& ref) const {
  return (day != ref.day || month != ref.month || year != ref.year);
}

const std::wstring & y::ldap::HOMEDIR::operator ()() const {
  return val;
}

y::ldap::HOMEDIR & y::ldap::HOMEDIR::operator =(const HOMEDIR& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool y::ldap::HOMEDIR::operator ==(const HOMEDIR & ref) const{
  return val.compare(ref.val) == 0;
}

bool y::ldap::HOMEDIR::operator !=(const HOMEDIR & ref) const{
  return val.compare(ref.val) != 0;
}

