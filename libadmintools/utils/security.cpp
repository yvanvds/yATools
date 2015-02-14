/* 
 * File:   security.cpp
 * Author: yvan
 * 
 * Created on May 8, 2014, 4:37 PM
 */

#include "security.h"
#include <crypt.h>
#include <string.h>
#include <boost/regex.hpp>
#include <cctype>

#include "../utils/random.h"

char consonants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
                     'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '\0'}; 
char vowels[] = {'a', 'e', 'i', 'o', 'u', 'y', '\0'};

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

std::string y::utils::security::makePassword(int length) {
  std::string result;
  bool vowel = false;
  for(int i = 0; i < length; i++) {
    if(vowel) {
      result += vowels[Random().get(5)];
    } else {
      result += consonants[Random().get(19)];
    }
    vowel = !vowel;
  }
  return result;
}


bool y::utils::security::isGoodPassword(const std::string& password) {
  // look in header file for explanation of this regex
  static const boost::regex e("^(?=.*[!@#$%&_])(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9]).{8,20}$");
  return boost::regex_match(password, e);
}