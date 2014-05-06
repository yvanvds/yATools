/* 
 * File:   dataset.cpp
 * Author: yvan
 * 
 * Created on January 30, 2014, 10:39 AM
 */

#include "dataset.h"
#include "server.h"
#include <ldap.h>

ldp::dataset::dataset(const resultset& orig) {
  filter = orig.filter;
  results = orig.results;
}

bool ldp::dataset::create(const std::string & filter) {
  this->filter = filter;
  Server().getData(*this);
}

int ldp::dataSet::count() {
  return datamap.size();
}

result & get(int index) {
  if (index >= datamap.size()) return dummy;
  return datamap[index];
}

