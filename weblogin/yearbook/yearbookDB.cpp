/* 
 * File:   yearbookDB.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 11:48 AM
 */

#include <Wt/WDate>
#include "yearbookDB.h"


yearbookDB::yearbookDB() {
  y::data::database db;
  db.open();
  
  if(!db.has("yearbookApp")) {
    db.create("yearbookApp");
  }
  
  db.use("yearbookApp");
  
  if(!db.tableExists("submissions")) {  
    // create table for submissions
    y::data::row submissions;
    submissions.addString("ID");
    submissions["ID"].primaryKey(true).required(true);
    submissions.addString("name").addString("surname");
    submissions.addString("servername");
    submissions["name"].stringLength(64);
    submissions["surname"].stringLength(64);
    submissions["servername"].stringLength(64);
    submissions.addDate("birthday").addString("classgroup").addString("mail");
    submissions["mail"].stringLength(64);
    submissions.addString("answer1").addString("answer2").addString("answer3").addString("answer4");
    submissions["answer1"].stringLength(1024);
    submissions["answer2"].stringLength(1024);
    submissions["answer3"].stringLength(1024);
    submissions["answer4"].stringLength(1024);
    submissions.addString("photo");
    submissions["photo"].stringLength(64);
    submissions.addDate("submitDate");
    submissions.addBool("approved");
    
    db.createTable("submissions", submissions);    
  } 
  
  if(!db.tableExists("config")) {
    y::data::row config;
    config.addInt("ID");
    config["ID"].primaryKey(true).required(true).autoIncrement(true);
    config.addDate("openDate");
    config.addDate("closeDate");
    config.addString("question1");
    config.addString("question2");
    config.addString("question3");
    config.addString("question4");
    config["question1"].stringLength(128);
    config["question2"].stringLength(128);
    config["question3"].stringLength(128);
    config["question4"].stringLength(128);
    
    db.createTable("config", config);
    
    config.clear();
    y::data::dateTime date;
    date.year(2000);
    date.month(5);
    date.day(1);
    config.addDate("openDate", date);
    config.addDate("closeDate", date);
    config.addString("question1", "");
    config.addString("question2", "");
    config.addString("question3", "");
    config.addString("question4", "");
    db.addRow("config", config);
  }
  
  if(!db.tableExists("replacements")) {
    y::data::row replacements;
    replacements.addInt("ID");
    replacements["ID"].primaryKey(true).required(true).autoIncrement(true);
    replacements.addString("original").addString("replacement");
    replacements["replacement"].stringLength(128);
    db.createTable("replacements", replacements);
  }
  
  if(!db.tableExists("groupImages")) {
    y::data::row images;
    images.addInt("ID");
    images["ID"].primaryKey(true).required(true).autoIncrement(true);
    images.addString("groupName").addString("imageName");
    images["imageName"].stringLength(128);
    db.createTable("groupImages", images);
  }
  
  if(!db.tableExists("validUsers")) {
    y::data::row users;
    users.addInt("ID");
    users["ID"].primaryKey(true).required(true).autoIncrement(true);
    users.addString("accountName");
    
    db.createTable("validUsers", users);
  } 
  
  newEntry = true;
  db.close();
}


void yearbookDB::loadConfig() {
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  container<y::data::row> config;
  db.getAllRows("config", config);
  if(config.elms()) {
    openDate  = config[0]["openDate" ].asDate();
    closeDate = config[0]["closeDate"].asDate();
    question[0] = config[0]["question1"].asString();
    question[1] = config[0]["question2"].asString();
    question[2] = config[0]["question3"].asString();
    question[3] = config[0]["question4"].asString();
  }
  
  db.getAllRows("replacements", replacements);
  db.getAllRows("groupImages", groupImages);
  db.close();
}

bool yearbookDB::loadUser(const string & uid) {
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  y::data::field condition;
  condition.name("ID");
  condition.setString(uid);
  container<y::data::row> rows;
  db.getRows("submissions", rows, condition);
  
  if(rows.elms() > 0) {
    y::data::row & result = rows[0];
    _ID = result["ID"].asString();
    _name = result["name"].asString();
    _surname = result["surname"].asString();
    _servername = result["servername"].asString();
    _group = result["classgroup"].asString();
    _mail = result["mail"].asString();
    _answer1 = result["answer1"].asString();
    _answer2 = result["answer2"].asString();
    _answer3 = result["answer3"].asString();
    _answer4 = result["answer4"].asString();
    _photo = result["photo"].asString();
    _birthday = result["birthday"].asDate();
    newEntry = false;
    return true;
  } else {
    return false;
  }
  
  db.close();
}

void yearbookDB::saveUser() {
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  y::data::row row;
  row.addString("name", _name);
  row.addString("surname", _surname);
  row.addString("servername", _servername);
  row.addString("classgroup", _group);
  row.addString("mail", _mail);
  row.addString("answer1", _answer1);
  row.addString("answer2", _answer2);
  row.addString("answer3", _answer3);
  row.addString("answer4", _answer4);
  row.addString("photo", _photo);
  row.addBool("approved", false);
  row.addDate("birthday", _birthday.dbFormat());
  
  y::data::dateTime now;
  Wt::WDate temp;
  temp = Wt::WDate::currentServerDate();
  now.day(temp.day());
  now.month(temp.month());
  now.year(temp.year());
  row.addDate("submitDate", now.dbFormat());
  
  if(newEntry) {
    row.addString("ID", _ID);
    db.addRow("submissions", row);
    newEntry = false;
  } else {
    y::data::field condition;
    condition.name("ID");
    condition.setString(_ID);

    db.setRow("submissions", row, condition);
  }
  
  db.close();
}

void yearbookDB::saveUser(entry & e) {
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  y::data::row row;
  row.addString("name", e.name);
  row.addString("surname", e.surname);
  row.addDate("birthday", e.birthday);
  row.addString("classgroup", e.group);
  row.addString("mail", e.mail);
  row.addString("answer1", e.answer1);
  row.addString("answer2", e.answer2);
  row.addString("answer3", e.answer3);
  row.addString("answer4", e.answer4);
  row.addString("photo", e.photo);
  row.addBool("approved", e.approved);
  y::data::field condition("ID", e.ID);
  db.setRow("submissions", row, condition);
  e.changed = false;
  
  db.close();
}

void yearbookDB::saveUser(int index) {
  if(index >= entries.elms()) return;
  
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  entry & e = entries[index];
  y::data::row row;
  row.addString("name", e.name);
  row.addString("surname", e.surname);
  row.addDate("birthday", e.birthday);
  row.addString("classgroup", e.group);
  row.addString("mail", e.mail);
  row.addString("answer1", e.answer1);
  row.addString("answer2", e.answer2);
  row.addString("answer3", e.answer3);
  row.addString("answer4", e.answer4);
  row.addString("photo", e.photo);
  row.addBool("approved", e.approved);
  y::data::field condition("ID", e.ID);
  db.setRow("submissions", row, condition);
  e.changed = false;
  db.close();
}

void yearbookDB::ID(const string & value) {
  _ID = value;
}

void yearbookDB::name(const string & value) {
  _name = value;
}

void yearbookDB::surname(const string & value) {
  _surname = value;
}

void yearbookDB::servername(const string & value) {
  _servername = value;
}

void yearbookDB::group(const string & value) {
  _group = value;
}

void yearbookDB::mail(const string & value) {
  _mail = value;
}

void yearbookDB::answer1(const string & value) {
  _answer1 = value;
}

void yearbookDB::answer2(const string & value) {
  _answer2 = value;
}

void yearbookDB::answer3(const string & value) {
  _answer3 = value;
}

void yearbookDB::answer4(const string & value) {
  _answer4 = value;
}

void yearbookDB::photo(const string & value) {
  _photo = value;
}

void yearbookDB::birthday(const Wt::WDate & value) {
  _birthday.day(value.day());
  _birthday.month(value.month());
  _birthday.year(value.year());
}

string yearbookDB::ID() {
  return _ID;
}

string yearbookDB::name() {
  return _name;
}

string yearbookDB::surname() {
  return _surname;
}

string yearbookDB::servername() {
  return _servername;
}

string yearbookDB::group() {
  return _group;
}

string yearbookDB::mail() {
  return _mail;
}

string yearbookDB::answer1() {
  return _answer1;
}

string yearbookDB::answer2() {
  return _answer2;
}

string yearbookDB::answer3() {
  return _answer3;
}

string yearbookDB::answer4() {
  return _answer4;
}

string yearbookDB::photo() {
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

string yearbookDB::getQuestion(int nr) {
  return question[nr];
}

void yearbookDB::loadAllUsers(const string& orderBy, bool reload) {
  if(!entries.empty() && !reload) return;
  
  entries.clear();
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  container<y::data::row> rows;
  container<y::data::order> order;
  order.New().setKey(orderBy);
  if(orderBy != "classgroup") {
    order.New().setKey("surname");
  }
  db.getAllRows("submissions", rows, order);
  
  for (int i = 0; i < rows.elms(); i++) {
    entry & e = entries.New();
    e.ID = rows[i]["ID"].asString();
    e.name = rows[i]["name"].asString();
    e.surname = rows[i]["surname"].asString();
    e.servername = rows[i]["servername"].asString();
    e.birthday = rows[i]["birthday"].asDate();
    e.group = rows[i]["classgroup"].asString();
    e.mail = rows[i]["mail"].asString();
    e.answer1 = rows[i]["answer1"].asString();
    e.answer2 = rows[i]["answer2"].asString();
    e.answer3 = rows[i]["answer3"].asString();
    e.answer4 = rows[i]["answer4"].asString();
    e.photo = rows[i]["photo"].asString();
    e.submitDate = rows[i]["submitDate"].asDate();
    e.approved = rows[i]["approved"].asBool();
    e.changed = false;
  }
  db.close();
}

void yearbookDB::replace(const string& key, const string& value) {
  bool found = false;
  int i = 0;
  for (; i < replacements.elms(); i++) {
    if(replacements[i]["original"].asString() == key) {
      replacements[i]["replacement"].setString(value);
      found = true;
      break;
    }
  }
  
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  if(found) {
    y::data::field condition("original", key);
    y::data::row row;
    row.addString("replacement", value);
    db.setRow("replacements", row, condition);
  } else {
    y::data::row row;
    row.addString("original", key);
    row.addString("replacement", value);
    db.addRow("replacements", row);
  }
  
  db.close();
}

void yearbookDB::saveGroupImage(const string& groupName, const string& imageName) {
  bool found = false;
  for (int i = 0; i < groupImages.elms(); i++) {
    if(groupImages[i]["groupName"].asString() == groupName) {
      groupImages[i]["imageName"].setString(imageName);
      found = true;
      break;
    }
  }
  
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  if(found) {
    y::data::field condition("groupName", groupName);
    y::data::row row;
    row.addString("imageName", imageName);
    db.setRow("groupImages", row, condition);
  } else {
    y::data::row row;
    row.addString("groupName", groupName);
    row.addString("imageName", imageName);
    db.addRow("groupImages", row);
  }
  db.close();
}

void yearbookDB::setQuestion(int ID, const string& text) {
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  question[ID] = text; 
  y::data::row row;
  switch(ID) {
    case 0: row.addString("question1", question[0]); break;
    case 1: row.addString("question2", question[1]); break;
    case 2: row.addString("question3", question[2]); break;
    case 3: row.addString("question4", question[3]); break;
  }
  y::data::field condition("ID", 1);
  db.setRow("config", row, condition);
  db.close();
}

void yearbookDB::setCloseDate(const Wt::WDate& date) {
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  closeDate.day(date.day());
  closeDate.month(date.month());
  closeDate.year(date.year());
  y::data::row row;
  row.addDate("closeDate", closeDate);
  y::data::field condition("ID", 1);
  db.setRow("config", row, condition);
  db.close();
}

void yearbookDB::setOpenDate(const Wt::WDate& date) {
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  openDate.day(date.day());
  openDate.month(date.month());
  openDate.year(date.year());
  y::data::row row;
  row.addDate("openDate", openDate);
  y::data::field condition("ID", 1);
  db.setRow("config", row, condition);
  db.close();
}

void yearbookDB::removeUser(const string & uid) {
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  y::data::field condition("ID", uid);
  db.delRow("submissions", condition);
  
  for(int i = 0; i < entries.elms(); i++) {
    if (entries[i].ID == uid) {
      entries.remove(i);
      break;
    }
  }
  
  db.close();
}

void yearbookDB::removeUser(int index) {
  if(index >= entries.elms()) return;
 
  y::data::database db;
  db.open();
  db.use("yearbookApp");
  
  y::data::field condition("ID", entries[index].ID);
  db.delRow("submissions", condition);
  db.close();
  
  entries.remove(index);
}

container<yearbookDB::entry> & yearbookDB::getEntries() {
  return entries;
}

container<y::data::row> & yearbookDB::getReplacements() {
  return replacements;
}

container<y::data::row> & yearbookDB::getGroupImages() {
  return groupImages;
}