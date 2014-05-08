/* 
 * File:   row.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 8:45 PM
 */

#include "row.h"

y::data::row & y::data::row::addBool(const std::string& name, bool value) {
  fields.New().name(name).setBool(value);
}

y::data::row & y::data::row::addChar(const std::string& name, char value) {
  fields.New().name(name).setChar(value);
}

y::data::row & y::data::row::addShort(const std::string& name, short value) {
  fields.New().name(name).setShort(value);
}

y::data::row & y::data::row::addInt(const std::string& name, int value) {
  fields.New().name(name).setInt(value);
}

y::data::row & y::data::row::addLong(const std::string& name, long value) {
  fields.New().name(name).setLong(value);
}

y::data::row & y::data::row::addFloat(const std::string& name, float value) {
  fields.New().name(name).setFloat(value);
}

y::data::row & y::data::row::addDouble(const std::string& name, double value) {
  fields.New().name(name).setDouble(value);
}

y::data::row & y::data::row::addString8(const std::string& name, const std::string & value) {
  fields.New().name(name).setString8(value);
}

y::data::row & y::data::row::addString(const std::string& name, const std::u16string & value) {
  fields.New().name(name).setString(value);
}

int y::data::row::elms() const {
  return fields.elms();
}

y::data::row & y::data::row::clear() {
  fields.clear();
  return *this;
}

y::data::field & y::data::row::operator [](int i) {
  return fields[i];
}

y::data::field & y::data::row::operator [](const std::string& name) {
  for (int i = 0; i < fields.elms(); i++) {
    if(fields[i].name().compare(name)==0) {
      return fields[i];
    }
  }
  // no element found, make a new one with this name
  return fields.New().name(name);
}