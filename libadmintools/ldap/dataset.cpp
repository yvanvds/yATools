/* 
 * File:   dataset.cpp
 * Author: yvan
 * 
 * Created on January 30, 2014, 10:39 AM
 */

#include "dataset.h"
#include "server.h"
#include <ldap.h>

y::ldap::dataset::dataset(const dataset& orig) {
  filter = orig.filter;
  directory = orig.directory;
  content = orig.content;
}

bool y::ldap::dataset::create(const std::string & filter, const std::string & directory) {
  this->filter = filter;
  this->directory = directory;
  return Server().getData(*this);
}

int y::ldap::dataset::elms() {
  return content.size();
}

y::ldap::data & y::ldap::dataset::get(int index) {
  if (static_cast<unsigned int>(index) >= content.size()) return dummy;
  return content[index];
}

y::ldap::data & y::ldap::dataset::New(data_type type) {
  content.emplace_back(type);
  return content.back();
}