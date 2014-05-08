/* 
 * File:   field.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 9:07 PM
 */

#include "field.h"

y::data::field::field(const std::string & name, bool value) {
  fieldName = name;
  storage.t_bool = value;
  type = BOOL;
}

y::data::field::field(const std::string & name, char value) {
  fieldName = name;
  storage.t_char = value;
  type = CHAR;
}

y::data::field::field(const std::string & name, short value) {
  fieldName = name;
  storage.t_short = value;
  type = SHORT;
}

y::data::field::field(const std::string & name, int value) {
  fieldName = name;
  storage.t_int = value;
  type = INT;
}

y::data::field::field(const std::string & name, long value) {
  fieldName = name;
  storage.t_long = value;
  type = LONG;
}

y::data::field::field(const std::string & name, float value) {
  fieldName = name;
  storage.t_float = value;
  type = FLOAT;
}

y::data::field::field(const std::string & name, double value) {
  fieldName = name;
  storage.t_double = value;
  type = DOUBLE;
}

y::data::field::field(const std::string & name, const std::string & value) {
  fieldName = name;
  t_str8 = value;
  type = STRING8;
}

y::data::field::field(const std::string & name, const std::u16string & value) {
  fieldName = name;
  t_str16 = value;
  type = STRING;
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

y::data::field & y::data::field::name(const std::string& fieldName) {
  this->fieldName = fieldName;
  return *this;
}
