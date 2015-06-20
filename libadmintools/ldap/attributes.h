#pragma once
#include "utils/string.h"

/*
   These classes contain all the attributes we
 * store in ldap. We want to make certain that
 * no mistakes will happen with accidental conversions
 * or wrong argument order in any programs we create.
 * This is why it is not allowed to use standard strings
 * or int's as arguments. Instead you have to use
 * DN, CN, FULL_NAME etc. No conversions from one to 
 * another are possible.
 */


class DN {
public:
  explicit DN(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  DN & operator=(const DN &ref);
  bool operator==(const DN &ref) const;
  bool operator!=(const DN &ref) const;

private:
  string val;
};

class UID_NUMBER {
public:
  explicit UID_NUMBER(const int val) : val(val) {}

  // operators
  int get() const; // get value
  UID_NUMBER & operator=(const UID_NUMBER &ref) {
    if(this != &ref) {
      val = ref.val;
    }
    return *this;
  }
  bool operator==(const UID_NUMBER &ref) const;
  bool operator!=(const UID_NUMBER &ref) const;

private:
  int val;
};

class UID {
public:
  explicit UID(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  UID & operator=(const UID &ref);
  bool operator==(const UID &ref) const;
  bool operator!=(const UID &ref) const;

private:
  string val;
};

class CN {
public:
  explicit CN(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  CN & operator= (const CN &ref);
  bool operator==(const CN &ref) const;
  bool operator!=(const CN &ref) const;

private:
  string val;
};

class SN {
public:
  explicit SN(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  SN & operator= (const SN &ref);
  bool operator==(const SN &ref) const;
  bool operator!=(const SN &ref) const;

private:
  string val;
};

class FULL_NAME {
public:
  explicit FULL_NAME(const string & val) : val(val) {}
  explicit FULL_NAME(const string & cn, const string & sn);

  // operators
  const string & get() const; // get value
  FULL_NAME & operator=(const FULL_NAME &ref);
  bool operator==(const FULL_NAME &ref) const;
  bool operator!=(const FULL_NAME &ref) const;

private:
  string val;
};

class ROLE {
public:
  enum TYPE {
    NONE,
    TEACHER,
    STUDENT,
    DIRECTOR,
    ADMIN,
    SUPPORT,
    EXTERN,
    EXTERN_WITH_MAIL,
  };

  explicit ROLE(TYPE val) : val(val) {}

  // operators
  TYPE get() const; // get value
  ROLE & operator=(const ROLE &ref);
  bool operator==(const ROLE &ref) const;
  bool operator!=(const ROLE &ref) const;

  static string toText(TYPE           value);
  static TYPE   toRole(const string & value);
  
private:
  TYPE val;
};

class GID_NUMBER {
public:
  explicit GID_NUMBER(int val) : val(val) {}

  // operators
  int get() const; // get value
  GID_NUMBER & operator=(const GID_NUMBER &ref);
  bool operator==(const GID_NUMBER &ref) const;
  bool operator!=(const GID_NUMBER &ref) const;

private:
  int val;
};

class WISA_ID {
public:
  explicit WISA_ID(int val) : val(val) {}

  // operators
  int get() const; // get value
  WISA_ID & operator=(const WISA_ID &ref);
  bool operator==(const WISA_ID &ref) const;
  bool operator!=(const WISA_ID &ref) const;

private:
  int val;
};

class WISA_NAME {
public:
  explicit WISA_NAME(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  WISA_NAME & operator=(const WISA_NAME &ref);
  bool operator==(const WISA_NAME &ref) const;
  bool operator!=(const WISA_NAME &ref) const;

private:
  string val;
};

class PASSWORD {
public:
  explicit PASSWORD(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  PASSWORD & operator=(const PASSWORD &ref);
  bool operator==(const PASSWORD &ref) const;
  bool operator!=(const PASSWORD &ref) const;

private:
  string val;
};

class MAIL {
public:
  explicit MAIL(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  MAIL & operator=(const MAIL &ref);
  bool operator==(const MAIL &ref) const;
  bool operator!=(const MAIL &ref) const;

private:
  string val;
};


class MAIL_ALIAS {
public:
  explicit MAIL_ALIAS(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  MAIL_ALIAS & operator=(const MAIL_ALIAS &ref);
  bool operator==(const MAIL_ALIAS &ref) const;
  bool operator!=(const MAIL_ALIAS &ref) const;

private:
  string val;
};

class DAY {
public:
  explicit DAY(int val);

  // operators
  int get() const; // get value
  DAY & operator=(const DAY &ref);
  bool operator==(const DAY &ref) const;
  bool operator!=(const DAY &ref) const;

private:
  int val;
};

class MONTH {
public:
  explicit MONTH(int val);

  // operators
  int get() const; // get value
  MONTH & operator=(const MONTH &ref);
  bool operator==(const MONTH &ref) const;
  bool operator!=(const MONTH &ref) const;

private:
  int val;
};

class YEAR {
public:
  explicit YEAR(int val) : val(val) {}

  // operators
  int get() const; // get value
  YEAR & operator=(const YEAR &ref);
  bool operator==(const YEAR &ref) const;
  bool operator!=(const YEAR &ref) const;

private:
  int val;
};

class DATE {
public: 
  explicit DATE(const string & ldapDate, bool fromWisa = false);
  explicit DATE(const DAY & day, const MONTH & month, const YEAR & year);

  // operators
  string get() const; // get value
  int asInt () const;
  int getDay() const;
  int getMonth() const;
  int getYear() const;
  DATE & operator=(const DATE &ref);
  bool operator==(const DATE &ref) const;
  bool operator!=(const DATE &ref) const;

private:
  DAY day;
  MONTH month;
  YEAR year;
};

class HOMEDIR {
public:
  explicit HOMEDIR(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  HOMEDIR & operator=(const HOMEDIR &ref);
  bool operator==(const HOMEDIR &ref) const;
  bool operator!=(const HOMEDIR &ref) const;

private:
  string val;
};

class BIRTHPLACE {
public:
  explicit BIRTHPLACE(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  BIRTHPLACE & operator=(const BIRTHPLACE &ref);
  bool operator==(const BIRTHPLACE &ref) const;
  bool operator!=(const BIRTHPLACE &ref) const;

private:
  string val;
};

class SCHOOLCLASS {
public:
  explicit SCHOOLCLASS(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  SCHOOLCLASS & operator=(const SCHOOLCLASS &ref);
  bool operator==(const SCHOOLCLASS &ref) const;
  bool operator!=(const SCHOOLCLASS &ref) const;

private:
  string val;
};

class GENDER {
public:
  enum TYPE {
    MALE,
    FEMALE,
    TRANSGENDER,
    NONE, 
  };
  
  explicit GENDER(TYPE val) : val(val) {}

  // operators
  TYPE get() const; // get value
  GENDER & operator=(const GENDER &ref);
  bool operator==(const GENDER &ref) const;
  bool operator!=(const GENDER &ref) const;

  static string toText  (TYPE           value);
  static TYPE   toGender(const string & value);
  
private:
  TYPE val;
};

class ADMINGROUP {
public:
  explicit ADMINGROUP(int val) : val(val) {}

  // operators
  int get() const; // get value
  ADMINGROUP & operator=(const ADMINGROUP &ref);
  bool operator==(const ADMINGROUP &ref) const;
  bool operator!=(const ADMINGROUP &ref) const;

private:
  int val;
};

class REGISTER_ID {
public:
  explicit REGISTER_ID(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  REGISTER_ID & operator=(const REGISTER_ID &ref);
  bool operator==(const REGISTER_ID &ref) const;
  bool operator!=(const REGISTER_ID &ref) const;

private:
  string val;
};

class NATION {
public:
  explicit NATION(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  NATION & operator=(const NATION &ref);
  bool operator==(const NATION &ref) const;
  bool operator!=(const NATION &ref) const;

private:
  string val;
};

class STEM_ID {
public:
  explicit STEM_ID(int val) : val(val) {}

  // operators
  int get() const; // get value
  STEM_ID & operator=(const STEM_ID &ref);
  bool operator==(const STEM_ID &ref) const;
  bool operator!=(const STEM_ID &ref) const;

private:
  int val;
};

class SCHOOL_ID {
public:
  explicit SCHOOL_ID(int val) : val(val) {}

  // operators
  int get() const; // get value
  SCHOOL_ID & operator=(const SCHOOL_ID &ref);
  bool operator==(const SCHOOL_ID &ref) const;
  bool operator!=(const SCHOOL_ID &ref) const;

private:
  int val;
};

class COUNTRY {
public:
  explicit COUNTRY(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  COUNTRY & operator=(const COUNTRY &ref);
  bool operator==(const COUNTRY &ref) const;
  bool operator!=(const COUNTRY &ref) const;

private:
  string val;
};

class STREET {
public:
  explicit STREET(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  STREET & operator=(const STREET &ref);
  bool operator==(const STREET &ref) const;
  bool operator!=(const STREET &ref) const;

private:
  string val;
};

class HOUSENUMBER {
public:
  explicit HOUSENUMBER(int val) : val(val) {}

  // operators
  int get() const; // get value
  HOUSENUMBER & operator=(const HOUSENUMBER &ref);
  bool operator==(const HOUSENUMBER &ref) const;
  bool operator!=(const HOUSENUMBER &ref) const;

private:
  int val;
};

class HOUSENUMBER_ADD {
public:
  explicit HOUSENUMBER_ADD(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  HOUSENUMBER_ADD & operator=(const HOUSENUMBER_ADD &ref);
  bool operator==(const HOUSENUMBER_ADD &ref) const;
  bool operator!=(const HOUSENUMBER_ADD &ref) const;

private:
  string val;
};

class CITY {
public:
  explicit CITY(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  CITY & operator=(const CITY &ref);
  bool operator==(const CITY &ref) const;
  bool operator!=(const CITY &ref) const;

private:
  string val;
};

class POSTAL_CODE {
public:
  explicit POSTAL_CODE(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  POSTAL_CODE & operator=(const POSTAL_CODE &ref);
  bool operator==(const POSTAL_CODE &ref) const;
  bool operator!=(const POSTAL_CODE &ref) const;

private:
  string val;
};

class DESCRIPTION {
public:
  explicit DESCRIPTION(const string & val) : val(val) {}

  // operators
  const string & get() const; // get value
  DESCRIPTION & operator= (const DESCRIPTION &ref);
  bool operator==(const DESCRIPTION &ref) const;
  bool operator!=(const DESCRIPTION &ref) const;

private:
  string val;
};

class ADJUNCT {
public:
  explicit ADJUNCT(const DN & val) : val(val) {}
  
  const DN & get() const;
  ADJUNCT & operator=(const ADJUNCT &ref);
  bool operator==(const ADJUNCT & ref) const;
  bool operator!=(const ADJUNCT & ref) const;
  
private:
  DN val;
};

class TITULAR {
public:
  explicit TITULAR(const DN & val) : val(val) {}
  
  const DN & get() const;
  TITULAR & operator=(const TITULAR &ref);
  bool operator==(const TITULAR & ref) const;
  bool operator!=(const TITULAR & ref) const;
  
private:
  DN val;
};

class MEMBER {
public:
  explicit MEMBER(const DN & val) : val(val) {}
  
  const DN & get() const;
  MEMBER & operator=(const MEMBER &ref);
  bool operator==(const MEMBER & ref) const;
  bool operator!=(const MEMBER & ref) const;
  
private:
  DN val;
};


enum WISA_IMPORT {
  WI_NOT_ACCOUNTED, // initial status
  WI_ACCOUNTED    , // a wisa entry is found for this entry
  WI_DISCARD      , // don't process in this session  
};
