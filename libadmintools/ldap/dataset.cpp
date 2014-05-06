/* 
 * File:   dataset.cpp
 * Author: yvan
 * 
 * Created on January 30, 2014, 10:39 AM
 */

#include "dataset.h"
#include "server.h"
#include <ldap.h>

ldp::dataset::dataset(const dataset& orig) {
  filter = orig.filter;
  content = orig.content;
}

bool ldp::dataset::create(const std::string & filter) {
  this->filter = filter;
  Server().getData(*this);
}

int ldp::dataset::count() {
  return content.size();
}

ldp::data & ldp::dataset::get(int index) {
  if (index >= content.size()) return dummy;
  return content[index];
}

