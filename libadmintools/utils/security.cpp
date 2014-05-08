/* 
 * File:   security.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 4:37 PM
 */

#include "security.h"
#include <crypt.h>
#include <string.h>

y::utils::security & y::utils::Security() {
  static security s;
  return s;
}

bool y::utils::security::test(const y::ldap::account& account, const std::string& password) {
  const y::ldap::PASSWORD & p = account.password();
  std::string removeCrypt = p();
  removeCrypt.erase(0, 7);
  const char * pass = removeCrypt.c_str();
  char * result;
  
  result = crypt(password.c_str(), pass);
  if(strcmp(result, pass) == 0) {
    return true;
  }
  
  return false;
}