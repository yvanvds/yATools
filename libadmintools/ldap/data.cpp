/* 
 * File:   data.cpp
 * Author: yvan
 * 
 * Created on January 30, 2014, 11:00 AM
 */

#include "data.h"

ldp::data::data(const data& orig) {
  attributes = orig.attributes;
}

void ldp::data::add(const std::string & name, const std::string & value) {
  attributes.insert(std::pair<std::string,std::string>(name, value));
}

int ldp::data::size() {
  return attributes.size();
}

int ldp::data::nameCount(const std::string& name) {
  return attributes.count(name);
}

const std::string & ldp::data::getValue(const std::string& name, int index) {
  // return dummy if index is not valid
  if (attributes.count(name) <= index) return dummy;
  
  // get range
  std::pair<std::multimap<std::string, std::string>::iterator,
          std::multimap<std::string, std::string>::iterator> range;
  range = attributes.equal_range(name);
  
  // move to index
  std::multimap<std::string, std::string>::iterator it = range.first;
  for (int i = 0; i < index; i++) {
    ++it;
  }
  
  // return result
  return it->second;
}

void ldp::data::setType(ldp::data_type type) {
  this->type = type;
}

ldp::data_type ldp::data::getType() {
  return type;
}

