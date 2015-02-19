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

void y::utils::parseCSV(const std::wstring& s, container<std::wstring>& list) {
  size_t pos = 0;
  std::wstring input(s);
  std::wstring delimiter = L";";
  while((pos = input.find(delimiter)) != std::wstring::npos) {
    list.New() = input.substr(0,pos);
    input.erase(0, pos + delimiter.length());
  }
}