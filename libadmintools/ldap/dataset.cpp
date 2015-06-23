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
  server = orig.server;
  filter = orig.filter;
  directory = orig.directory;
  content = orig.content;
}

bool y::ldap::dataset::create(const string & filter, const string & directory) {
  this->filter = filter;
  this->directory = directory;
  return server->getData(*this);
}

bool y::ldap::dataset::createFromDN(const string& dn) {
  std::string temp = dn.utf8();
  std::vector<std::string> strs;
  boost::split(strs, temp, boost::is_any_of(","));
  if(strs.size() < 2) return false;
  
  this->filter = strs[0];
  this->directory = strs[1];
  for(unsigned int i = 2; i < strs.size(); i++) {
    this->directory += ",";
    this->directory += string(strs[i]);
  }
  return server->getData(*this, true);
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