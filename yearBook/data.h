/* 
 * File:   data.h
 * Author: yvan
 *
 * Created on May 14, 2014, 8:30 PM
 */

#include <admintools.h>

#ifndef YEARBOOKDATA_H
#define	YEARBOOKDATA_H

class dataconnect {
public:
  dataconnect();
  
  bool load(const Wt::WString & ID);
  void save();
  
  void ID(const Wt::WString & value);
  void name(const Wt::WString & value);
  void surname(const Wt::WString & value);
  void servername(const Wt::WString & value);
  void group(const Wt::WString & value);
  void mail(const Wt::WString & value);
  void answer1(const Wt::WString & value);
  void answer2(const Wt::WString & value);
  void answer3(const Wt::WString & value);
  void answer4(const Wt::WString & value);
  void photo(const Wt::WString & value);
  void birthday(const Wt::WDate & value);
  
  Wt::WString ID();
  Wt::WString name();
  Wt::WString surname();
  Wt::WString servername();
  Wt::WString group();
  Wt::WString mail();
  Wt::WString answer1();
  Wt::WString answer2();
  Wt::WString answer3();
  Wt::WString answer4();
  Wt::WString photo();
  Wt::WDate birthday();
  
private:
  std::unique_ptr<y::data::server> server;
  std::unique_ptr<y::data::database> db;
  
  
  std::string _ID;
  std::u16string _name;
  std::u16string _surname;
  std::u16string _servername;
  y::data::dateTime _birthday;
  std::u16string _group;
  std::u16string _mail;
  std::u16string _answer1;
  std::u16string _answer2;
  std::u16string _answer3;
  std::u16string _answer4;
  std::u16string _photo;
  
  bool newEntry;
};

#endif	/* YEARBOOKDATA_H */

