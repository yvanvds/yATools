/* 
 * File:   convert.h
 * Author: yvan
 *
 * Created on May 11, 2014, 7:50 PM
 */

#ifndef CONVERT_H
#define	CONVERT_H

#include <string>
#include <ext/codecvt_specializations.h>
#include <Wt/WString>
#include <stdexcept>

class MyException : public std::runtime_error
{
public:
  MyException(const std::string& w) : std::runtime_error(w) { }
};

typedef __gnu_cxx::encoding_state EncSt;

struct UTF8 {
  typedef char storage_type;
  static const char* iconvName() { return "UTF-8"; }
};

struct UTF16 {
  typedef char16_t storage_type;
  static const char* iconvName()
#if BYTE_ORDER == BIG_ENDIAN
    { return "UTF-16BE"; }
#else
    { return "UTF-16LE"; }
#endif
};

struct UTF32 {
  typedef char32_t storage_type;
  static const char* iconvName()
#if BYTE_ORDER == BIG_ENDIAN
    { return "UTF-32BE"; }
#else
    { return "UTF-32LE"; }
#endif
};

struct WCHAR_T {
  typedef char32_t storage_type;
  static const char* iconvName()
#if BYTE_ORDER == BIG_ENDIAN
    { return "WCHAR_T"; }
#else
    { return "WCHAR_T"; }
#endif
};


template<class T, class F> int storageMultiplier();

template<class T, class F>
class Converter {
 private:
  typedef typename F::storage_type from_storage_type;
  typedef typename T::storage_type to_storage_type;

  typedef std::codecvt<from_storage_type, to_storage_type, EncSt> codecvt_type;

 public:
  typedef std::basic_string<from_storage_type> from_string_type;
  typedef std::basic_string<to_storage_type> to_string_type;

  to_string_type operator()(const from_string_type& s)
  {
    static std::locale loc(std::locale::classic(), new codecvt_type);
    static EncSt state(F::iconvName(), T::iconvName());
    static const codecvt_type& cvt = std::use_facet<codecvt_type>(loc);

    const from_storage_type* enx;

    int len = s.length() * storageMultiplier<T, F>();
    to_storage_type i[len];
    to_storage_type* inx;

    typename codecvt_type::result r =
      cvt.out(state, s.c_str(), s.c_str() + s.length(), enx, i, i + len, inx);

    if (r != codecvt_type::ok)
      throw MyException("Conversion failed");

    return to_string_type(i, inx - i);
  }
};

extern std::string str8(const std::u16string& s);
extern std::string str8(const std::u32string& s);
extern std::string str8(const std::wstring&   s);

extern std::wstring strW(const std::string & s);

extern std::u16string str16(const std::string& s);
extern std::u16string str16(const std::u32string& s);

extern std::u32string str32(const std::string& s);
extern std::u32string str32(const std::u16string& s);

extern Wt::WString strWt(const std::u16string& s);


#endif	/* CONVERT_H */

