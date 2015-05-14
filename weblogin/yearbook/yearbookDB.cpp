/* 
 * File:   yearbookDB.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 11:48 AM
 */

#include <Wt/WDate>
#include "yearbookDB.h"

yearbookDB & YearbookDB() {
  static yearbookDB s;
  return s;
}

yearbookDB::yearbookDB() {
  server = std::unique_ptr<y::data::server>(new y::data::server);
  db = std::unique_ptr<y::data::database>(new y::data::database(*server));
  
  if(!server->hasDatabase(L"yearbookApp")) {
    server->create(L"yearbookApp");
  }
  
  db->use(L"yearbookApp");
  
if(!db->tableExists(L"submissions")) {  
    // create table for submissions
    y::data::row submissions;
    submissions.addString8(L"ID");
    submissions[L"ID"].primaryKey(true).required(true);
    submissions.addString(L"name").addString(L"surname");
    submissions.addString(L"servername");
    submissions[L"name"].stringLength(64);
    submissions[L"surname"].stringLength(64);
    submissions[L"servername"].stringLength(64);
    submissions.addDate(L"birthday").addString(L"classgroup").addString(L"mail");
    submissions[L"mail"].stringLength(64);
    submissions.addString(L"answer1").addString(L"answer2").addString(L"answer3").addString(L"answer4");
    submissions[L"answer1"].stringLength(1024);
    submissions[L"answer2"].stringLength(1024);
    submissions[L"answer3"].stringLength(1024);
    submissions[L"answer4"].stringLength(1024);
    submissions.addString(L"photo");
    submissions[L"photo"].stringLength(64);
    submissions.addDate(L"submitDate");
    submissions.addBool(L"approved");
    
    db->createTable(L"submissions", submissions);    
  } 
  
  if(!db->tableExists(L"config")) {
    y::data::row config;
    config.addInt(L"ID");
    config[L"ID"].primaryKey(true).required(true).autoIncrement(true);
    config.addDate(L"openDate");
    config.addDate(L"closeDate");
    config.addString(L"question1");
    config.addString(L"question2");
    config.addString(L"question3");
    config.addString(L"question4");
    config[L"question1"].stringLength(128);
    config[L"question2"].stringLength(128);
    config[L"question3"].stringLength(128);
    config[L"question4"].stringLength(128);
    
    db->createTable(L"config", config);
    
    config.clear();
    y::data::dateTime date;
    date.year(2000);
    date.month(5);
    date.day(1);
    config.addDate(L"openDate", date);
    config.addDate(L"closeDate", date);
    config.addString(L"question1", L"");
    config.addString(L"question2", L"");
    config.addString(L"question3", L"");
    config.addString(L"question4", L"");
    db->addRow(L"config", config);
  }
  
  if(!db->tableExists(L"replacements")) {
    y::data::row replacements;
    replacements.addInt(L"ID");
    replacements[L"ID"].primaryKey(true).required(true).autoIncrement(true);
    replacements.addString(L"original").addString(L"replacement");
    replacements[L"replacement"].stringLength(128);
    db->createTable(L"replacements", replacements);
  }
  
  if(!db->tableExists(L"validUsers")) {
    y::data::row users;
    users.addInt(L"ID");
    users[L"ID"].primaryKey(true).required(true).autoIncrement(true);
    users.addString8(L"accountName");
    
    db->createTable(L"validUsers", users);
  } 
  
  newEntry = true;
}

void yearbookDB::loadConfig() {
  container<y::data::row> config;
  db->getAllRows(L"config", config);
  if(config.elms()) {
    openDate  = config[0][L"openDate" ].asDate();
    closeDate = config[0][L"closeDate"].asDate();
    question[0] = config[0][L"question1"].asString();
    question[1] = config[0][L"question2"].asString();
    question[2] = config[0][L"question3"].asString();
    question[3] = config[0][L"question4"].asString();
  }
}

bool yearbookDB::loadUser(const std::string & uid) {
  y::data::field condition;
  condition.name(L"ID");
  condition.setString8(uid);
  container<y::data::row> rows;
  db->getRows(L"submissions", rows, condition);
  
  if(rows.elms() > 0) {
    y::data::row & result = rows[0];
    _ID = result[L"ID"].asString8();
    _name = result[L"name"].asString();
    _surname = result[L"surname"].asString();
    _servername = result[L"servername"].asString();
    _group = result[L"classgroup"].asString();
    _mail = result[L"mail"].asString();
    _answer1 = result[L"answer1"].asString();
    _answer2 = result[L"answer2"].asString();
    _answer3 = result[L"answer3"].asString();
    _answer4 = result[L"answer4"].asString();
    _photo = result[L"photo"].asString();
    _birthday = result[L"birthday"].asDate();
    newEntry = false;
    return true;
  } else {
    return false;
  }
}

void yearbookDB::saveUser() {
  y::data::row row;
  row.addString(L"name", _name);
  row.addString(L"surname", _surname);
  row.addString(L"servername", _servername);
  row.addString(L"classgroup", _group);
  row.addString(L"mail", _mail);
  row.addString(L"answer1", _answer1);
  row.addString(L"answer2", _answer2);
  row.addString(L"answer3", _answer3);
  row.addString(L"answer4", _answer4);
  row.addString(L"photo", _photo);
  row.addBool(L"approved", false);
  row.addDate(L"birthday", _birthday.dbFormat());
  
  y::data::dateTime now;
  Wt::WDate temp;
  temp = Wt::WDate::currentServerDate();
  now.day(temp.day());
  now.month(temp.month());
  now.year(temp.year());
  row.addDate(L"submitDate", now.dbFormat());
  
  if(newEntry) {
    row.addString8(L"ID", _ID);
    db->addRow(L"submissions", row);
    newEntry = false;
  } else {
    y::data::field condition;
    condition.name(L"ID");
    condition.setString8(_ID);

    db->setRow(L"submissions", row, condition);
  }
}

void yearbookDB::saveUser(entry & e) {
  y::data::row row;
  row.addString(L"name", e.name);
  row.addString(L"surname", e.surname);
  row.addDate(L"birthday", e.birthday);
  row.addString(L"classgroup", e.group);
  row.addString(L"mail", e.mail);
  row.addString(L"answer1", e.answer1);
  row.addString(L"answer2", e.answer2);
  row.addString(L"answer3", e.answer3);
  row.addString(L"answer4", e.answer4);
  row.addString(L"photo", e.photo);
  row.addBool(L"approved", e.approved);
  y::data::field condition(L"ID", e.ID);
  db->setRow(L"submissions", row, condition);
  e.changed = false;
}

void yearbookDB::saveUser(int index) {
  if(index >= entries.elms()) return;
  
  entry & e = entries[index];
  y::data::row row;
  row.addString(L"name", e.name);
  row.addString(L"surname", e.surname);
  row.addDate(L"birthday", e.birthday);
  row.addString(L"classgroup", e.group);
  row.addString(L"mail", e.mail);
  row.addString(L"answer1", e.answer1);
  row.addString(L"answer2", e.answer2);
  row.addString(L"answer3", e.answer3);
  row.addString(L"answer4", e.answer4);
  row.addString(L"photo", e.photo);
  row.addBool(L"approved", e.approved);
  y::data::field condition(L"ID", e.ID);
  db->setRow(L"submissions", row, condition);
  e.changed = false;
}

void yearbookDB::ID(const std::wstring & value) {
  _ID = str8(value);
}

void yearbookDB::name(const std::wstring & value) {
  _name = value;
}

void yearbookDB::surname(const std::wstring & value) {
  _surname = value;
}

void yearbookDB::servername(const std::wstring & value) {
  _servername = value;
}

void yearbookDB::group(const std::wstring & value) {
  _group = value;
}

void yearbookDB::mail(const std::wstring & value) {
  _mail = value;
}

void yearbookDB::answer1(const std::wstring & value) {
  _answer1 = value;
}

void yearbookDB::answer2(const std::wstring & value) {
  _answer2 = value;
}

void yearbookDB::answer3(const std::wstring & value) {
  _answer3 = value;
}

void yearbookDB::answer4(const std::wstring & value) {
  _answer4 = value;
}

void yearbookDB::photo(const std::wstring & value) {
  _photo = value;
}

void yearbookDB::birthday(const Wt::WDate & value) {
  _birthday.day(value.day());
  _birthday.month(value.month());
  _birthday.year(value.year());
}

std::wstring yearbookDB::ID() {
  return strW(_ID);
}

std::wstring yearbookDB::name() {
  return _name;
}

std::wstring yearbookDB::surname() {
  return _surname;
}

std::wstring yearbookDB::servername() {
  return _servername;
}

std::wstring yearbookDB::group() {
  return _group;
}

std::wstring yearbookDB::mail() {
  return _mail;
}

std::wstring yearbookDB::answer1() {
  return _answer1;
}

std::wstring yearbookDB::answer2() {
  return _answer2;
}

std::wstring yearbookDB::answer3() {
  return _answer3;
}

std::wstring yearbookDB::answer4() {
  return _answer4;
}

std::wstring yearbookDB::photo() {
  return _photo;
}

Wt::WDate yearbookDB::birthday() {
  Wt::WDate result;
  result.setDate(_birthday.year(), _birthday.month(), _birthday.day());
  return result;
}

Wt::WDate yearbookDB::getOpenDate() {
  Wt::WDate date;
  date.setDate(openDate.year(), openDate.month(), openDate.day());
  return date;
}

Wt::WDate yearbookDB::getCloseDate() {
  Wt::WDate date;
  date.setDate(closeDate.year(), closeDate.month(), closeDate.day());
  return date;
}

std::wstring yearbookDB::getQuestion(int nr) {
  return question[nr];
}

void yearbookDB::loadAllUsers(const std::string& orderBy, bool reload) {
  if(!entries.empty() && !reload) return;
  
  entries.clear();
  
  container<y::data::row> rows;
  container<y::data::order> order;
  order.New().setKey(orderBy);
  if(orderBy.compare("classgroup")) {
    order.New().setKey("surname");
  }
  db->getAllRows(L"submissions", rows, order);
  
  for (int i = 0; i < rows.elms(); i++) {
    entry & e = entries.New();
    e.ID = rows[i][L"ID"].asString8();
    e.name = rows[i][L"name"].asString();
    e.surname = rows[i][L"surname"].asString();
    e.servername = rows[i][L"servername"].asString();
    e.birthday = rows[i][L"birthday"].asDate();
    e.group = rows[i][L"classgroup"].asString();
    e.mail = rows[i][L"mail"].asString();
    e.answer1 = rows[i][L"answer1"].asString();
    e.answer2 = rows[i][L"answer2"].asString();
    e.answer3 = rows[i][L"answer3"].asString();
    e.answer4 = rows[i][L"answer4"].asString();
    e.photo = rows[i][L"photo"].asString();
    e.submitDate = rows[i][L"submitDate"].asDate();
    e.approved = rows[i][L"approved"].asBool();
    e.changed = false;
  }
}

void yearbookDB::replace(const std::wstring& key, const std::wstring& value) {
  bool found = false;
  int i = 0;
  for (; i < replacements.elms(); i++) {
    if(replacements[i][L"original"].asString().compare(key) == 0) {
      replacements[i][L"replacement"].setString(value);
      found = true;
      break;
    }
  }
  
  if(found) {
    y::data::field condition(L"original", key);
    y::data::row row;
    row.addString(L"replacement", value);
    db->setRow(L"replacements", row, condition);
  } else {
    y::data::row row;
    row.addString(L"original", key);
    row.addString(L"replacement", value);
    db->addRow(L"replacements", row);
  }
}

void yearbookDB::setQuestion(int ID, const std::wstring& text) {
  question[ID] = text; 
  y::data::row row;
  switch(ID) {
    case 0: row.addString(L"question1", question[0]); break;
    case 1: row.addString(L"question2", question[1]); break;
    case 2: row.addString(L"question3", question[2]); break;
    case 3: row.addString(L"question4", question[3]); break;
  }
  y::data::field condition(L"ID", 1);
  db->setRow(L"config", row, condition);
}

void yearbookDB::setCloseDate(const Wt::WDate& date) {
  closeDate.day(date.day());
  closeDate.month(date.month());
  closeDate.year(date.year());
  y::data::row row;
  row.addDate(L"closeDate", closeDate);
  y::data::field condition(L"ID", 1);
  db->setRow(L"config", row, condition);
}

void yearbookDB::setOpenDate(const Wt::WDate& date) {
  openDate.day(date.day());
  openDate.month(date.month());
  openDate.year(date.year());
  y::data::row row;
  row.addDate(L"openDate", openDate);
  y::data::field condition(L"ID", 1);
  db->setRow(L"config", row, condition);
}

void yearbookDB::removeUser(const std::string & uid) {
  y::data::field condition(L"ID", uid);
  db->delRow(L"submissions", condition);
  
  for(int i = 0; i < entries.elms(); i++) {
    if (entries[i].ID.compare(uid) == 0) {
      entries.remove(i);
      break;
    }
  }
}

void yearbookDB::removeUser(int index) {
  if(index >= entries.elms()) return;
 
  y::data::field condition(L"ID", entries[index].ID);
  db->delRow(L"submissions", condition);
  
  entries.remove(index);
}

container<yearbookDB::entry> & yearbookDB::getEntries() {
  return entries;
}

container<y::data::row> & yearbookDB::getReplacements() {
  return replacements;
}