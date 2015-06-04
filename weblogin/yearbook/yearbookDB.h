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

class yearbookDB : public Wt::WObject {
public:
  struct entry {
    string ID;
    string name, surname, servername, group, mail;
    string answer1, answer2, answer3, answer4, photo;
    y::data::dateTime birthday, submitDate;
    bool approved, changed;
  };
  
  yearbookDB();
  
  void loadConfig();
  void loadAllUsers(const string & orderBy = string("name"), bool reload = false);
  
  bool loadUser(const string & uid);
  void saveUser();
  void saveUser(entry & e);
  void saveUser(int index);
  void removeUser(const string & uid);
  void removeUser(int index);
  
  void ID        (const string    & value);
  void name      (const string    & value);
  void surname   (const string    & value);
  void servername(const string    & value);
  void group     (const string    & value);
  void mail      (const string    & value);
  void answer1   (const string    & value);
  void answer2   (const string    & value);
  void answer3   (const string    & value);
  void answer4   (const string    & value);
  void photo     (const string    & value);
  void birthday  (const Wt::WDate & value);
  
  string ID         ();
  string name       ();
  string surname    ();
  string servername ();
  string group      ();
  string mail       ();
  string answer1    ();
  string answer2    ();
  string answer3    ();
  string answer4    ();
  string photo      ();
  Wt::WDate birthday();
  
  string    getQuestion (int nr);
  Wt::WDate getOpenDate (      );
  Wt::WDate getCloseDate(      );
  
  void setQuestion (int ID, const string & text);
  void setOpenDate (const Wt::WDate & date);
  void setCloseDate(const Wt::WDate & date);
  
  void replace(const string & key, const string & value);
  void saveGroupImage(const string & groupName, const string & imageName);
  
  container<entry> & getEntries();
  container<y::data::row> & getReplacements();
  container<y::data::row> & getGroupImages();
  
  
private: 
  
  string _ID;
  string _name;
  string _surname;
  string _servername;
  string _group;
  string _mail;
  string _answer1;
  string _answer2;
  string _answer3;
  string _answer4;
  string _photo;
  y::data::dateTime _birthday;
  
  bool newEntry;
  
  y::data::dateTime openDate;
  y::data::dateTime closeDate;
  string question[4];
  
  container<entry> entries;
  container<y::data::row> replacements;
  container<y::data::row> groupImages;
};


#endif	/* YEARBOOKDB_H */

