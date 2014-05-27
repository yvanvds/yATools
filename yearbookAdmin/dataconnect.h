/* 
 * File:   dataconnect.h
 * Author: yvan
 *
 * Created on May 20, 2014, 10:46 PM
 */

#ifndef DATACONNECT_H
#define	DATACONNECT_H

#include <admintools.h>
#include <vector>
#include <Wt/WDate>
#include <Wt/WString>

struct entry {
  std::string ID;
  std::u16string name;
  std::u16string surname;
  std::u16string servername;
  y::data::dateTime birthday;
  std::u16string group;
  std::u16string mail;
  std::u16string answer1;
  std::u16string answer2;
  std::u16string answer3;
  std::u16string answer4;
  std::u16string photo;
  y::data::dateTime submitDate;
  bool approved;
  bool changed;
};

class dataconnect {
public:
  dataconnect();
  
  void load();
  void save(int entry);
  void remove(int entry);
  void reloadEntries(const std::string & orderBy);
  
  Wt::WDate getOpenDate();
  void setOpenDate(const Wt::WDate & date);
  
  Wt::WDate getCloseDate();
  void setCloseDate(const Wt::WDate & date);
  
  Wt::WString getQuestion(int nr);
  void setQuestion(int nr, const Wt::WString & question);
  
  void addUser(const std::string & name);
  void delUser(const std::string & name);
  
  std::vector<entry> entries;
  container<y::data::row> replacements;
  container<y::data::row> validUsers;
  
private:
  std::unique_ptr<y::data::server> server;
  std::unique_ptr<y::data::database> db;
  bool loaded;
  
  y::data::dateTime openDate;
  y::data::dateTime closeDate;
  std::u16string question[4];
  
  
};

#endif	/* DATACONNECT_H */

