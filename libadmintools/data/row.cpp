/* 
 * File:   row.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 8:45 PM
 */

#include "row.h"
#include <iostream>

y::data::row & y::data::row::addBool(const string& name, bool value) {
  fields.New().name(name).setBool(value);
  return *this;
}

y::data::row & y::data::row::addChar(const string& name, char value) {
  fields.New().name(name).setChar(value);
  return *this;
}

y::data::row & y::data::row::addShort(const string& name, short value) {
  fields.New().name(name).setShort(value);
  return *this;
}

y::data::row & y::data::row::addInt(const string& name, int value) {
  fields.New().name(name).setInt(value);
  return *this;
}

y::data::row & y::data::row::addLong(const string& name, long value) {
  fields.New().name(name).setLong(value);
  return *this;
}

y::data::row & y::data::row::addFloat(const string& name, float value) {
  fields.New().name(name).setFloat(value);
  return *this;
}

y::data::row & y::data::row::addDouble(const string& name, double value) {
  fields.New().name(name).setDouble(value);
  return *this;
}


y::data::row & y::data::row::addString(const string& name, const string & value) {
  fields.New().name(name).setString(value);
  return *this;
}

y::data::row & y::data::row::addDate(const string& name, const dateTime & value) {
  fields.New().name(name).setDate(value);
  return *this;
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

y::data::field & y::data::row::operator [](const string& name) {
  for (int i = 0; i < fields.elms(); i++) {
    if(fields[i].name() == name) {
      return fields[i];
    }
  }
  // no element found, make a new one with this name
  return fields.New().name(name);
}

void y::data::row::print() {
  for(int i = 0; i < fields.elms(); i++) {
    std::cout << fields[i].name() << " -> ";
    switch(fields[i].getType()) {
      case UNKNOWN: std::cout << "!!!type unknown!!!" << std::endl  ; break;
      case BOOL   : std::cout << fields[i].asBool  () << " (bool)"  ; break;
      case CHAR   : std::cout << fields[i].asChar  () << " (char)"  ; break;
      case SHORT  : std::cout << fields[i].asShort () << " (short)" ; break;
      case INT    : std::cout << fields[i].asInt   () << " (int)"   ; break;
      case LONG   : std::cout << fields[i].asLong  () << " (long)"  ; break;
      case FLOAT  : std::cout << fields[i].asFloat () << " (float)" ; break;
      case DOUBLE : std::cout << fields[i].asDouble() << " (double)"; break;
      case STRING : std::cout << fields[i].asString() << " (string)"; break;
      case DATE_TIME: std::cout << fields[i].asDate().dbFormat() << " (date_time)"; break;
    }
    std:: cout << std::endl;
  }
}

