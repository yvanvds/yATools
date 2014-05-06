/* 
 * File:   attributes.cpp
 * Author: yvan
 * 
 * Created on January 14, 2014, 5:42 PM
 */

#include "attributes.h"

const std::string & ldp::DN::operator ()() const {
  return val;
}

ldp::DN & ldp::DN::operator =(const DN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::DN::operator ==(const DN& ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::DN::operator !=(const DN& ref) const{
  return val.compare(ref.val) != 0;
}

int ldp::UID_NUMBER::operator ()() const{
  return val;
}

bool ldp::UID_NUMBER::operator ==(const UID_NUMBER& ref) const{
  return val == ref.val;
}

bool ldp::UID_NUMBER::operator !=(const UID_NUMBER& ref) const{
  return val != ref.val;
}

const std::string & ldp::UID::operator ()() const {
  return val;
}

ldp::UID & ldp::UID::operator =(const UID& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::UID::operator ==(const UID& ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::UID::operator !=(const UID& ref) const{
  return val.compare(ref.val) != 0;
}

const std::string & ldp::CN::operator ()() const {
  return val;
}

ldp::CN & ldp::CN::operator =(const CN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::CN::operator ==(const CN& ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::CN::operator !=(const CN& ref) const{
  return val.compare(ref.val) != 0;
}

const std::string & ldp::SN::operator ()() const {
  return val;
}

ldp::SN & ldp::SN::operator =(const SN& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::SN::operator ==(const SN& ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::SN::operator !=(const SN& ref) const{
  return val.compare(ref.val) != 0;
}

ldp::FULL_NAME::FULL_NAME(const CN& cn, const SN& sn) {
  val = cn();
  val += " ";
  val += sn();
}

const std::string & ldp::FULL_NAME::operator ()() const {
  return val;
}

ldp::FULL_NAME & ldp::FULL_NAME::operator =(const FULL_NAME& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::FULL_NAME::operator ==(const FULL_NAME& ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::FULL_NAME::operator !=(const FULL_NAME& ref) const{
  return val.compare(ref.val) != 0;
}

const std::string & ldp::GID::operator ()() const {
  return val;
}

ldp::GID & ldp::GID::operator =(const GID& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::GID::operator ==(const GID & ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::GID::operator !=(const GID & ref) const{
  return val.compare(ref.val) != 0;
}

int ldp::GID_NUMBER::operator()() const {
  return val;
}

ldp::GID_NUMBER & ldp::GID_NUMBER::operator=(const GID_NUMBER &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::GID_NUMBER::operator==(const GID_NUMBER &ref) const{
  return val == ref.val;
}

bool ldp::GID_NUMBER::operator!=(const GID_NUMBER &ref) const {
  return val != ref.val;
}

int ldp::WISA_ID::operator()() const {
  return val;
}

ldp::WISA_ID & ldp::WISA_ID::operator=(const WISA_ID &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::WISA_ID::operator==(const WISA_ID &ref) const{
  return val == ref.val;
}

bool ldp::WISA_ID::operator!=(const WISA_ID &ref) const {
  return val != ref.val;
}

const std::string & ldp::MAIL::operator ()() const {
  return val;
}

ldp::MAIL & ldp::MAIL::operator =(const MAIL& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::MAIL::operator ==(const MAIL & ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::MAIL::operator !=(const MAIL & ref) const{
  return val.compare(ref.val) != 0;
}

const std::string & ldp::PASSWORD::operator ()() const {
  return val;
}

ldp::PASSWORD & ldp::PASSWORD::operator =(const PASSWORD& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::PASSWORD::operator ==(const PASSWORD & ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::PASSWORD::operator !=(const PASSWORD & ref) const{
  return val.compare(ref.val) != 0;
}

int ldp::DAY::operator()() const {
  return val;
}

ldp::DAY & ldp::DAY::operator=(const DAY &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::DAY::operator==(const DAY &ref) const{
  return val == ref.val;
}

bool ldp::DAY::operator!=(const DAY &ref) const {
  return val != ref.val;
}

int ldp::MONTH::operator()() const {
  return val;
}

ldp::MONTH & ldp::MONTH::operator=(const MONTH &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::MONTH::operator==(const MONTH &ref) const{
  return val == ref.val;
}

bool ldp::MONTH::operator!=(const MONTH &ref) const {
  return val != ref.val;
}

int ldp::YEAR::operator()() const {
  return val;
}

ldp::YEAR & ldp::YEAR::operator=(const YEAR &ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::YEAR::operator==(const YEAR &ref) const{
  return val == ref.val;
}

bool ldp::YEAR::operator!=(const YEAR &ref) const {
  return val != ref.val;
}

ldp::DATE::DATE(const DAY& day, const MONTH& month, const YEAR& year) 
        : day(day), month(month), year(year) {}

int ldp::DATE::operator ()() const {
  int result = year();
  result << 2;
  result += month();
  result << 2;
  result += day();
  return result;
}

std::string ldp::DATE::asString() const {
  std::string result;
  result += day();
  switch(month()) {
    case 1: result += " januari "; break;
    case 2: result += " februari "; break;
    case 3: result += " maart "; break;
    case 4: result += " april "; break;
    case 5: result += " mei "; break;
    case 6: result += " juni "; break;
    case 7: result += " juli "; break;
    case 8: result += " augustus "; break;
    case 9: result += " september "; break;
    case 10: result += " oktober "; break;
    case 11: result += " november "; break;
    case 12: result += " december "; break;
  }
  result += year();
}

int ldp::DATE::getDay() const {
  return day();
}

int ldp::DATE::getMonth() const {
  return month();
}

int ldp::DATE::getYear() const {
  return year();
}

ldp::DATE & ldp::DATE::operator =(const DATE& ref) {
  if(this != &ref) {
    day = ref.day;
    month = ref.month;
    year = ref.year;
  }
  return *this;
}

bool ldp::DATE::operator ==(const DATE& ref) const {
  return (day == ref.day && month == ref.month && year == ref.year);
}

bool ldp::DATE::operator !=(const DATE& ref) const {
  return (day != ref.day || month != ref.month || year != ref.year);
}

const std::string & ldp::HOMEDIR::operator ()() const {
  return val;
}

ldp::HOMEDIR & ldp::HOMEDIR::operator =(const HOMEDIR& ref) {
  if(this != &ref) val = ref.val;
  return *this;
}

bool ldp::HOMEDIR::operator ==(const HOMEDIR & ref) const{
  return val.compare(ref.val) == 0;
}

bool ldp::HOMEDIR::operator !=(const HOMEDIR & ref) const{
  return val.compare(ref.val) != 0;
}

