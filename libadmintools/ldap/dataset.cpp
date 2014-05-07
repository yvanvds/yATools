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
  content = orig.content;
}

bool y::ldap::dataset::create(const std::string & filter) {
  this->filter = filter;
  return Server().getData(*this);
}

int y::ldap::dataset::count() {
  return content.size();
}

y::ldap::data & y::ldap::dataset::get(int index) {
  if (index >= content.size()) return dummy;
  return content[index];
}

y::ldap::data & y::ldap::dataset::New(data_type type) {
  content.emplace_back(type);
  return content.back();
}