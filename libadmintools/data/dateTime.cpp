/* 
 * File:   dateTime.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 9:01 PM
 */

#include "utils/string.h"
#include "dateTime.h"

y::data::dateTime::dateTime() :
  _day(0),
  _month(0),
  _year(0),
  _hours(0),
  _minutes(0),
  _seconds(0) {}

y::data::dateTime::dateTime(const string & dbFormat) :
  _day(0),
  _month(0),
  _year(0),
  _hours(0),
  _minutes(0),
  _seconds(0) {
  this->dbFormat(dbFormat);
}

y::data::dateTime & y::data::dateTime::day(int value) {
  _day = value;
  return *this;
}

y::data::dateTime & y::data::dateTime::month(int value) {
  _month = value;
  return *this;
}

y::data::dateTime & y::data::dateTime::year(int value) {
  _year = value; 
  return *this;
}

y::data::dateTime & y::data::dateTime::hours(int value) {
  _hours = value; 
  return *this;
}

y::data::dateTime & y::data::dateTime::minutes(int value) {
  _minutes = value;
  return *this;
}

y::data::dateTime & y::data::dateTime::seconds(int value) {
  _seconds = value;
  return *this;
}

int y::data::dateTime::day() const {
  return _day;
}

int y::data::dateTime::month() const {
  return _month;
}

int y::data::dateTime::year() const {
  return _year;
}

int y::data::dateTime::hours() const {
  return _hours;
}

int y::data::dateTime::minutes() const {
  return _minutes;
}

int y::data::dateTime::seconds() const {
  return _seconds;
}

string y::data::dateTime::dbFormat() const {
  string result;
  result += _year;
  result += "-";
  if(_month < 10) result += 0;
  result += _month;
  result += "-";
  if(_day < 10) result += 0;
  result += _day;
  result += " ";

  if(_hours < 10) result += 0;
  result += _hours;
  result += ":";
  if(_minutes < 10) result += 0;
  result += _minutes;
  result += ":";
  if(_seconds < 10) result += 0;
  result += _seconds;
  
  return result;
}

void y::data::dateTime::dbFormat(const string & value) {
  _year = std::stoi(value.db().substr(0, 4));
  _month = std::stoi(value.db().substr(5, 2));
  _day = std::stoi(value.db().substr(8, 2));
  _hours = std::stoi(value.db().substr(11, 2));
  _minutes = std::stoi(value.db().substr(14, 2));
  _seconds = std::stoi(value.db().substr(17, 2));
}