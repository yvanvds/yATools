/* 
 * File:   dateTime.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 9:01 PM
 */

#include <string>

#include "dateTime.h"

y::data::dateTime::dateTime() :
  _day(0),
  _month(0),
  _year(0),
  _hours(0),
  _minutes(0),
  _seconds(0) {}

y::data::dateTime::dateTime(const std::wstring & dbFormat) :
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

std::wstring y::data::dateTime::dbFormat() const {
  std::wstring result;
  result.append(std::to_wstring(_year));
  result.append(L"-");
  if(_month < 10) result.append(L"0");
  result.append(std::to_wstring(_month));
  result.append(L"-");
  if(_day < 10) result.append(L"0");
  result.append(std::to_wstring(_day));
  result.append(L" ");

  if(_hours < 10) result.append(L"0");
  result.append(std::to_wstring(_hours));
  result.append(L":");
  if(_minutes < 10) result.append(L"0");
  result.append(std::to_wstring(_minutes));
  result.append(L":");
  if(_seconds < 10) result.append(L"0");
  result.append(std::to_wstring(_seconds));
  
  return result;
}

void y::data::dateTime::dbFormat(const std::wstring& value) {
  _year = std::stoi(value.substr(0, 4));
  _month = std::stoi(value.substr(5, 2));
  _day = std::stoi(value.substr(8, 2));
  _hours = std::stoi(value.substr(11, 2));
  _minutes = std::stoi(value.substr(14, 2));
  _seconds = std::stoi(value.substr(17, 2));
}