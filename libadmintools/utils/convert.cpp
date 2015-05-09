/* 
 * File:   convert.cpp
 * Author: yvan
 * 
 * Created on May 11, 2014, 7:50 PM
 */

#include "convert.h"
#include <string>
#include <locale>
#include <boost/locale.hpp>

template<>
int storageMultiplier<UTF8, UTF32>() { return 4; }

template<>
int storageMultiplier<UTF8, UTF16>() { return 3; }

template<>
int storageMultiplier<UTF16, UTF8>() { return 1; }

template<>
int storageMultiplier<UTF16, UTF32>() { return 2; }

template<>
int storageMultiplier<UTF32, UTF8>() { return 1; }

template<>
int storageMultiplier<UTF32, UTF16>() { return 1; }

template<>
int storageMultiplier<WCHAR_T, UTF8>() { return 1; }

template<>
int storageMultiplier<UTF8, WCHAR_T>() { return 4; }

std::string str8(const std::u16string& s)
{
  static Converter<UTF8, UTF16> converter;

  return converter(s);
}

std::string str8(const std::u32string& s)
{
  static Converter<UTF8, UTF32> converter;

  return converter(s);
}

std::string str8(const std::wstring& s) {
  return boost::locale::conv::utf_to_utf<char>(s);
}

std::wstring strW(const std::string& s) {
  return boost::locale::conv::utf_to_utf<wchar_t>(s);
}

std::u16string str16(const std::string& s)
{
  static Converter<UTF16, UTF8> converter;

  return converter(s);
}

std::u16string str16(const std::u32string& s)
{
  static Converter<UTF16, UTF32> converter;

  return converter(s);
}

std::u32string str32(const std::string& s)
{
  static Converter<UTF32, UTF8> converter;

  return converter(s);
}

std::u32string str32(const std::u16string& s)
{
  static Converter<UTF32, UTF16> converter;

  return converter(s);
}


Wt::WString strWt(const std::u16string& s) {
  return Wt::WString(str8(s), Wt::UTF8);
}
