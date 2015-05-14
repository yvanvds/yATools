/* 
 * File:   yearbookDB.h
 * Author: yvan
 *
 * Created on May 12, 2015, 11:48 AM
 */

#ifndef YEARBOOKDB_H
#define	YEARBOOKDB_H

#include <string>
#include <admintools.h>

class yearbookDB {
public:
  struct entry {
    std::string ID;
    std::wstring name, surname, servername, group, mail;
    std::wstring answer1, answer2, answer3, answer4, photo;
    y::data::dateTime birthday, submitDate;
    bool approved, changed;
  };
  
  yearbookDB();
  
  void loadConfig();
  void loadAllUsers(const std::string & orderBy = "name", bool reload = false);
  
  bool loadUser(const std::string & uid);
  void saveUser();
  void saveUser(entry & e);
  void saveUser(int index);
  void removeUser(const std::string & uid);
  void removeUser(int index);
  
  void ID        (const std::wstring & value);
  void name      (const std::wstring & value);
  void surname   (const std::wstring & value);
  void servername(const std::wstring & value);
  void group     (const std::wstring & value);
  void mail      (const std::wstring & value);
  void answer1   (const std::wstring & value);
  void answer2   (const std::wstring & value);
  void answer3   (const std::wstring & value);
  void answer4   (const std::wstring & value);
  void photo     (const std::wstring & value);
  void birthday  (const Wt::WDate    & value);
  
  std::wstring ID        ();
  std::wstring name      ();
  std::wstring surname   ();
  std::wstring servername();
  std::wstring group     ();
  std::wstring mail      ();
  std::wstring answer1   ();
  std::wstring answer2   ();
  std::wstring answer3   ();
  std::wstring answer4   ();
  std::wstring photo     ();
  Wt::WDate birthday     ();
  
  std::wstring getQuestion (int nr);
  Wt::WDate    getOpenDate (      );
  Wt::WDate    getCloseDate(      );
  
  void setQuestion(int ID, const std::wstring & text);
  void setOpenDate(const Wt::WDate & date);
  void setCloseDate(const Wt::WDate & date);
  
  void replace(const std::wstring & key, const std::wstring & value);
  
  container<entry> & getEntries();
  container<y::data::row> & getReplacements();
  
  
private:
  std::unique_ptr<y::data::server  > server;
  std::unique_ptr<y::data::database> db    ;
  
  
  std::string _ID;
  std::wstring _name;
  std::wstring _surname;
  std::wstring _servername;
  std::wstring _group;
  std::wstring _mail;
  std::wstring _answer1;
  std::wstring _answer2;
  std::wstring _answer3;
  std::wstring _answer4;
  std::wstring _photo;
  y::data::dateTime _birthday;
  
  bool newEntry;
  
  y::data::dateTime openDate;
  y::data::dateTime closeDate;
  std::wstring question[4];
  
  container<entry> entries;
  container<y::data::row> replacements;
};

yearbookDB & YearbookDB();

#endif	/* YEARBOOKDB_H */

