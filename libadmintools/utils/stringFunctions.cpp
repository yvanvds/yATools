/* 
 * File:   stringFunctions.cpp
 * Author: yvan
 * 
 * Created on February 19, 2015, 3:35 PM
 */

#include <iosfwd>
#include <cctype>
#include <string>

#include "stringFunctions.h"


void y::utils::keepOnlyChars(std::wstring& s) {
  size_t i = 0;
  size_t len = s.length();
  
  while (i < len) {
    if(!isalnum(s[i]) || s[i] == L' ') {
      s.erase(i, 1);
      len--;
    } else {
      i++;
    }
  }
}