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
#include "utils/convert.h"

#include "../utils/random.h"

char consonants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
                     'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '\0'}; 
char vowels[] = {'a', 'e', 'i', 'o', 'u', 'y', '\0'};


y::utils::security & y::utils::Security() {
  static security s;
  return s;
}

bool y::utils::security::test(const y::ldap::account& account, const string& password) {
  const PASSWORD & p = account.password();
  std::string removeCrypt = p.get().utf8();
  removeCrypt.erase(0, 7);
  const char * pass = removeCrypt.c_str();
  char * result;
  
  result = crypt(password.c_str(), pass);
  if(strcmp(result, pass) == 0) {
    return true;
  }
  
  return false;
}

string y::utils::security::makePassword(int length) {
  string result;
  bool vowel = false;
  
  int capitalPos = Random().get(length -1);
  
  int numberPos = Random().get(length -1);
  while (capitalPos == numberPos) {
    numberPos = Random().get(length -1);
  }
   
  for(int i = 0; i < length; i++) {
    if (i == numberPos) {
      result += Random().get(9);
    } else if(vowel) {
      result += vowels[Random().get(5)];
    } else {
      result += consonants[Random().get(19)];
    }
    
    if(i == capitalPos) {
      char c = result[i];
      c = (char)toupper(c);
      result[i] = c;
    }
    
    vowel = !vowel;
  }
   
  return result;
}


bool y::utils::security::isGoodPassword(const string& password) {
  // look in header file for explanation of this regex
  static const boost::regex e("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9]).{8,20}$");
  return boost::regex_match(password.utf8(), e);
}