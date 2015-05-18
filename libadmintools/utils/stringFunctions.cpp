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


void y::utils::keepOnlyChars(std::string& s) {
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

#pragma GCC diagnostic ignored "-Wmultichar"
void y::utils::replaceUTF8Chars(std::string& s) {
  for(unsigned int i = 0; i < s.length(); i++) {
    switch (s[i]) {
      case 'à': s[i] = 'a'; break;
      case 'á': s[i] = 'a'; break;
      case 'â': s[i] = 'a'; break;
      case 'ã': s[i] = 'a'; break;
      case 'ä': s[i] = 'a'; break;
      case 'å': s[i] = 'a'; break;
      case 'æ': s[i] = 'e'; break;
      case 'ç': s[i] = 'c'; break;
      case 'è': s[i] = 'e'; break;
      case 'é': s[i] = 'e'; break;
      case 'ê': s[i] = 'e'; break;
      case 'ë': s[i] = 'e'; break;
      case 'ì': s[i] = 'i'; break;
      case 'í': s[i] = 'i'; break;
      case 'î': s[i] = 'i'; break;
      case 'ï': s[i] = 'i'; break;
      case 'ð': s[i] = 'o'; break;
      case 'ñ': s[i] = 'n'; break;
      case 'ò': s[i] = 'o'; break;
      case 'ó': s[i] = 'o'; break;
      case 'ô': s[i] = 'o'; break;
      case 'õ': s[i] = 'o'; break;
      case 'ö': s[i] = 'o'; break;
      case 'ø': s[i] = 'o'; break;
      case 'ù': s[i] = 'u'; break;
      case 'ú': s[i] = 'u'; break;
      case 'û': s[i] = 'u'; break;
      case 'ü': s[i] = 'u'; break;
      case 'ý': s[i] = 'y'; break;
      case 'ÿ': s[i] = 'y'; break;
      case 'À': s[i] = 'A'; break;
      case 'Á': s[i] = 'A'; break;
      case 'Â': s[i] = 'A'; break;
      case 'Ã': s[i] = 'A'; break;
      case 'Ä': s[i] = 'A'; break;
      case 'Å': s[i] = 'A'; break;
      case 'Æ': s[i] = 'E'; break;
      case 'Ç': s[i] = 'C'; break;
      case 'È': s[i] = 'E'; break;
      case 'É': s[i] = 'E'; break;
      case 'Ê': s[i] = 'E'; break;
      case 'Ë': s[i] = 'E'; break;
      case 'Ì': s[i] = 'I'; break;
      case 'Í': s[i] = 'I'; break;
      case 'Î': s[i] = 'I'; break;
      case 'Ï': s[i] = 'I'; break;
      case 'Ð': s[i] = 'D'; break;
      case 'Ñ': s[i] = 'N'; break;
      case 'Ò': s[i] = 'O'; break;
      case 'Ó': s[i] = 'O'; break;
      case 'Ô': s[i] = 'O'; break;
      case 'Õ': s[i] = 'O'; break;
      case 'Ö': s[i] = 'O'; break;
      case 'Ø': s[i] = 'O'; break;
      case 'Ù': s[i] = 'U'; break;
      case 'Ú': s[i] = 'U'; break;
      case 'Û': s[i] = 'U'; break;
      case 'Ü': s[i] = 'U'; break;
      case 'Ý': s[i] = 'Y'; break;      
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