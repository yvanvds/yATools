/* 
 * File:   data.cpp
 * Author: yvan
 * 
 * Created on January 30, 2014, 11:00 AM
 */

#include "data.h"

y::ldap::data::data(const data& orig) {
  attributes = orig.attributes;
  type = orig.type;
}

void y::ldap::data::add(const std::wstring & name, const std::wstring & value) {
  attributes.emplace(std::wstring(name), std::wstring(value));
}

int y::ldap::data::elms() {
  return attributes.size();
}

int y::ldap::data::elms(const std::wstring& name) const {
  return attributes.count(name);
}

const std::wstring & y::ldap::data::getValue(const std::wstring& name, int index) const {
  // return dummy if index is not valid
  if (attributes.count(name) <= static_cast<unsigned int>(index)) return dummy;
  
  // get range
  std::pair<std::multimap<std::wstring, std::wstring>::const_iterator,
          std::multimap<std::wstring, std::wstring>::const_iterator> range;
  range = attributes.equal_range(name);
  
  // move to index
  std::multimap<std::wstring, std::wstring>::const_iterator it = range.first;
  for (int i = 0; i < index; i++) {
    ++it;
  }
  
  // return result
  return it->second;
}

void y::ldap::data::setType(y::ldap::data_type type) {
  this->type = type;
}

y::ldap::data_type y::ldap::data::getType() {
  return type;
}

