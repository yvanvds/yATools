/* 
 * File:   field.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 9:07 PM
 */

#include "field.h"
#include <iostream>
#include "../utils/convert.h"
#include "dateTime.h"

y::data::field::field() : type(UNKNOWN) {
  str_length = 16;
  _required = false;
  _auto = false;
  _primary = false;
}

y::data::field::field(const string & name, bool value) {
  field();
  fieldName = name;
  storage.t_bool = value;
  type = BOOL;
}

y::data::field::field(const string & name, char value) {
  field();
  fieldName = name;
  storage.t_char = value;
  type = CHAR;
}

y::data::field::field(const string & name, short value) {
  field();
  fieldName = name;
  storage.t_short = value;
  type = SHORT;
}

y::data::field::field(const string & name, int value) {
  field();
  fieldName = name;
  storage.t_int = value;
  type = INT;
}

y::data::field::field(const string & name, long value) {
  field();
  fieldName = name;
  storage.t_long = value;
  type = LONG;
}

y::data::field::field(const string & name, float value) {
  field();
  fieldName = name;
  storage.t_float = value;
  type = FLOAT;
}

y::data::field::field(const string & name, double value) {
  field();
  fieldName = name;
  storage.t_double = value;
  type = DOUBLE;
}

y::data::field::field(const string & name, const string & value) {
  field();
  fieldName = name;
  t_str16 = value;
  type = STRING;
}

y::data::field::field(const string & name, const dateTime & value) {
  field();
  fieldName = name;
  date = value;
  type = DATE_TIME;
}

y::data::FIELD_TYPE y::data::field::getType() {
  return type;
}

bool y::data::field::asBool() {
  return storage.t_bool;
}

char y::data::field::asChar() {
  return storage.t_char;
}

short y::data::field::asShort() {
  return storage.t_short;
}

int y::data::field::asInt() {
  return storage.t_int;
}

long y::data::field::asLong() {
  return storage.t_long;
}

float y::data::field::asFloat() {
  return storage.t_float;
}

double y::data::field::asDouble() {
  return storage.t_double;
}

const string & y::data::field::asString() {
  return t_str16;
}

const y::data::dateTime & y::data::field::asDate() {
  return date;
}

const string & y::data::field::name() {
  return fieldName;
}

y::data::field & y::data::field::setBool(bool value) {
  storage.t_bool = value;
  type = BOOL;
  return *this;
}

y::data::field & y::data::field::setChar(char value) {
  storage.t_char = value;
  type = CHAR;
  return *this;
}

y::data::field & y::data::field::setShort(short value) {
  storage.t_short = value;
  type = SHORT;
  return *this;
}

y::data::field & y::data::field::setInt(int value) {
  storage.t_int = value;
  type = INT;
  return *this;
}

y::data::field & y::data::field::setLong(long value) {
  storage.t_long = value;
  type = LONG;
  return *this;
}

y::data::field & y::data::field::setFloat(float value) {
  storage.t_float = value;
  type = FLOAT;
  return *this;
}

y::data::field & y::data::field::setDouble(double value) {
  storage.t_double = value;
  type = DOUBLE;
  return *this;
}

y::data::field & y::data::field::setString(const string & value) {
  t_str16 = value;
  type = STRING;
  return *this;
}

y::data::field & y::data::field::setDate(const dateTime & value) {
  date = value;
  type = DATE_TIME;
  return *this;
}

y::data::field & y::data::field::name(const string& fieldName) {
  this->fieldName = fieldName;
  return *this;
}

y::data::field & y::data::field::stringLength(int length) {
  str_length = length;
  return *this;
}

y::data::field & y::data::field::required(bool value) {
  _required = value;
  return *this;
}

y::data::field & y::data::field::autoIncrement(bool value) {
  _auto = value;
  return *this;
}

y::data::field & y::data::field::primaryKey(bool value) {
  _primary = value;
  return *this;
}

int y::data::field::stringLength() {
  return str_length;
}

bool y::data::field::required() {
  return _required;
}

bool y::data::field::autoIncrement() {
  return _auto;
}

bool y::data::field::primaryKey() {
  return _primary;
}

void y::data::field::print() {
  if(getType() == BOOL) {
    std::wcout << fieldName << L": " << asBool() << std::endl;
  } else if(getType() == CHAR) {
    std::wcout << fieldName << L": " << asChar() << std::endl;
  } else if(getType() == SHORT) {
    std::wcout << fieldName << L": " << asShort() << std::endl;
  } else if(getType() == INT) {
    std::wcout << fieldName << L": " << asInt() << std::endl;
  } else if(getType() == LONG) {
    std::wcout << fieldName << L": " << asLong() << std::endl;
  } else if(getType() == FLOAT) {
    std::wcout << fieldName << L": " << asFloat() << std::endl;
  } else if(getType() == DOUBLE) {
    std::wcout << fieldName << L": " << asDouble() << std::endl;
  } else if(getType() == STRING) {
    std::wcout << fieldName << L": " << asString() << std::endl;
  } else if(getType() == DATE_TIME) {
    std::wcout << fieldName << L": " << date.dbFormat() << std::endl;
  }
}