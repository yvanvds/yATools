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

y::data::field::field(const std::string & name, bool value) {
  field();
  fieldName = name;
  storage.t_bool = value;
  type = BOOL;
}

y::data::field::field(const std::string & name, char value) {
  field();
  fieldName = name;
  storage.t_char = value;
  type = CHAR;
}

y::data::field::field(const std::string & name, short value) {
  field();
  fieldName = name;
  storage.t_short = value;
  type = SHORT;
}

y::data::field::field(const std::string & name, int value) {
  field();
  fieldName = name;
  storage.t_int = value;
  type = INT;
}

y::data::field::field(const std::string & name, long value) {
  field();
  fieldName = name;
  storage.t_long = value;
  type = LONG;
}

y::data::field::field(const std::string & name, float value) {
  field();
  fieldName = name;
  storage.t_float = value;
  type = FLOAT;
}

y::data::field::field(const std::string & name, double value) {
  field();
  fieldName = name;
  storage.t_double = value;
  type = DOUBLE;
}

y::data::field::field(const std::string & name, const std::string & value) {
  field();
  fieldName = name;
  t_str8 = value;
  type = STRING8;
}

y::data::field::field(const std::string & name, const std::u16string & value) {
  field();
  fieldName = name;
  t_str16 = value;
  type = STRING;
}

y::data::field::field(const std::string & name, const dateTime & value) {
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

const std::string & y::data::field::asString8() {
  return t_str8;
}

const std::u16string & y::data::field::asString() {
  return t_str16;
}

const y::data::dateTime & y::data::field::asDate() {
  return date;
}

const std::string & y::data::field::name() {
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

y::data::field & y::data::field::setString8(const std::string & value) {
  t_str8 = value;
  type = STRING8;
  return *this;
}

y::data::field & y::data::field::setString(const std::u16string & value) {
  t_str16 = value;
  type = STRING;
  return *this;
}

y::data::field & y::data::field::setDate(const dateTime & value) {
  date = value;
  type = DATE_TIME;
  return *this;
}

y::data::field & y::data::field::name(const std::string& fieldName) {
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
    std::cout << fieldName << ": " << asBool() << std::endl;
  } else if(getType() == CHAR) {
    std::cout << fieldName << ": " << asChar() << std::endl;
  } else if(getType() == SHORT) {
    std::cout << fieldName << ": " << asShort() << std::endl;
  } else if(getType() == INT) {
    std::cout << fieldName << ": " << asInt() << std::endl;
  } else if(getType() == LONG) {
    std::cout << fieldName << ": " << asLong() << std::endl;
  } else if(getType() == FLOAT) {
    std::cout << fieldName << ": " << asFloat() << std::endl;
  } else if(getType() == DOUBLE) {
    std::cout << fieldName << ": " << asDouble() << std::endl;
  } else if(getType() == STRING8) {
    std::cout << fieldName << ": " << asString8() << std::endl;
  } else if(getType() == STRING) {
    std::cout << fieldName << ": " << str8(asString()) << std::endl;
  } else if(getType() == DATE_TIME) {
    std::cout << fieldName << ": " << date.dbFormat() << std::endl;
  }
}