/* 
 * File:   string.h
 * Author: yvan
 *
 * Created on May 15, 2015, 9:01 PM
 */

#ifndef STRING_H
#define	STRING_H

#include <string>
#include <iostream>
#include <boost/locale.hpp>
#include "convert.h"
#include "stringFunctions.h"
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

class string {
public:
           string(                         ) {}
           string(const string       & orig) : content(orig.content ) {}
  explicit string(const std::string  & orig) : content(       orig  ) {}
  explicit string(const std::wstring & orig) : content(  str8(orig) ) {}
           string(const Wt ::WString & orig) : content(orig.toUTF8()) {}
           string(const char         * orig) : content(       orig  ) {}
           
  
  explicit string(int value) : content(std::to_string(value)) {}
  
  // return as wide string
  std::wstring wide () const { return strW(content); }
  // return as utf8 string
  std::string  utf8 () const { return      content ; }
  // return as c string
  const char * c_str() const { return content.c_str(); }
  // return as ldap string
  const char * ldap () const { return content.c_str(); }
  // return as database string
  std::string  db   () const { return content; }
  // return as Wt string
  Wt::WString  wt   () const { return Wt::WString(content, Wt::UTF8); }
  // return as smartschool string
  std::string  ss   () const { return boost::locale::conv::from_utf(content, "Latin1"); }
  // return as integer
  int          asInt() const { return std::stoi(content); }
  
  // information
  bool         empty() const { return content.length() == 0; }
  unsigned int size () const { return content.length()     ; }
  
  // assignment
  void operator=(const string       & ref) { content = ref.content; }
  void operator=(const std::string  & ref) { content =      ref   ; }
  void operator=(const std::wstring & ref) { content = str8(ref)  ; }
  void operator=(const char         * ref) { content =      ref   ; }
  
  // compare
  bool operator==(const string & ref) const { return content.compare(ref.content) == 0; }

  friend bool operator==(const std::string  & lhs, const string & rhs) { return rhs.content.compare(     lhs ) == 0; }
  friend bool operator==(const std::wstring & lhs, const string & rhs) { return rhs.content.compare(str8(lhs)) == 0; }
  
  bool operator!=(const string & ref) const { return content.compare(ref.content) != 0; }
  
  friend bool operator!=(const std::string  & lhs, const string & rhs) { return rhs.content.compare(     lhs ) != 0; }
  friend bool operator!=(const std::wstring & lhs, const string & rhs) { return rhs.content.compare(str8(lhs)) != 0; }
  
  bool operator<(const string & ref) const { return content < ref.content; }
  
  // append
  string & operator+=(const string       & ref) { content +=         ref.content; return *this; }
  string & operator+=(char                 ref) { content +=                ref ; return *this; }
  string & operator+=(int                  ref) { content += std::to_string(ref); return *this; }
  string & operator+=(float                ref) { content += std::to_string(ref); return *this; }
  string & operator+=(double               ref) { content += std::to_string(ref); return *this; }
  
  string operator+(const string       & ref) const { return string(content +         ref.content); }
  string operator+(const std::string  & ref) const { return string(content +                ref ); }
  string operator+(const std::wstring & ref) const { return string(content +           str8(ref)); }
  string operator+(const char *         ref) const { return string(content +                ref ); }
  string operator+(int                  ref) const { return string(content + std::to_string(ref)); }
  string operator+(float                ref) const { return string(content + std::to_string(ref)); }
  string operator+(double               ref) const { return string(content + std::to_string(ref)); }
  
  friend string operator+(const char * lhs, const string & rhs) { string result(lhs); result += rhs; return result; }
  
  // stream
  string & operator<<(const string       & ref) { content +=         ref.content; return *this; }
  string & operator<<(const std::string  & ref) { content +=                ref ; return *this; }
  string & operator<<(const std::wstring & ref) { content +=           str8(ref); return *this; }
  string & operator<<(int                  ref) { content += std::to_string(ref); return *this; }
  string & operator<<(float                ref) { content += std::to_string(ref); return *this; }
  string & operator<<(double               ref) { content += std::to_string(ref); return *this; }
  
  friend std::ostream  & operator<<(std::ostream  & stream, const string & str) { stream << str.utf8(); return stream; }
  friend std::wostream & operator<<(std::wostream & stream, const string & str) { stream << str.wide(); return stream; }
  
  
  //iteration
        char & operator[](int pos)       { return content[pos]; }
  const char & operator[](int pos) const { return content[pos]; }
  
  // manipulation
  string & replaceUTF8  () { y::utils::replaceUTF8Chars       (content); return *this; }
  string & keeponlyChars() { y::utils::keepOnlyChars          (content); return *this; }
  string & toLower      () { content = boost::locale::to_lower(content); return *this; }
  string & removeNewLine() {
      // windows
    boost::replace_all(content, "\r\n", " ");
    // linux
    boost::replace_all(content, "\n", " ");
    // mac
    boost::replace_all(content, "\r", " ");
    return *this;
  }
  
  void execute          () { system(content.c_str()); }
  void clear            () {        content.clear() ; }
private:
  std::string content;
};


#endif	/* STRING_H */

