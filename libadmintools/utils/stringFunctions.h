/* 
 * File:   stringFunctions.h
 * Author: yvan
 *
 * Created on February 19, 2015, 3:35 PM
 */

#ifndef STRINGFUNCTIONS_H
#define	STRINGFUNCTIONS_H
#include "container.h"
#include <string>

namespace y {
  namespace utils {
    void keepOnlyChars(std::wstring & s);
    void replaceUTF8Chars(std::wstring & s);
    
    // tokenize a string based on ';' values
    void parseCSV(const std::wstring & s, container<std::wstring> & list);
  }
}

#endif	/* STRINGFUNCTIONS_H */

