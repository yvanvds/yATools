/* 
 * File:   dataset.cpp
 * Author: yvan
 * 
 * Created on January 30, 2014, 10:39 AM
 */

#include "dataset.h"
#include "server.h"
#include <ldap.h>
#include <boost/algorithm/string.hpp>

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

bool y::ldap::dataset::createFromDN(const std::string& dn) {
  std::vector<std::string> strs;
  boost::split(strs, dn, boost::is_any_of(","));
  assert(strs.size() > 1);
  this->filter = strs[0];
  this->directory = strs[1];
  for(unsigned int i = 2; i < strs.size(); i++) {
    this->directory += ",";
    this->directory += strs[i];
  }
  return Server().getData(*this, true);
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