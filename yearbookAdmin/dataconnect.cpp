/* 
 * File:   dataconnect.cpp
 * Author: yvan
 * 
 * Created on May 20, 2014, 10:46 PM
 */

#include "dataconnect.h"
#include <admintools.h>

dataconnect::dataconnect() {
  server = std::unique_ptr<y::data::server>(new y::data::server);
  db = std::unique_ptr<y::data::database>(new y::data::database(*server));
  
  if(!server->hasDatabase("yearbookApp")) {
    server->create("yearbookApp");
  }
  db->use("yearbookApp");
    
  if(!db->tableExists("submissions")) {
    // create table for submissions
    y::data::row submissions;
    submissions.addString8("ID");
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

    db->createTable("submissions", submissions);
  }
    
  if(!db->tableExists("config")) {
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
    
    db->createTable("config", config);
    
    config.clear();
    y::data::dateTime date;
    date.year(2000);
    date.month(5);
    date.day(1);
    config.addDate("openDate", date);
    config.addDate("closeDate", date);
    config.addString("question1", str16(""));
    config.addString("question2", str16(""));
    config.addString("question3", str16(""));
    config.addString("question4", str16(""));
    db->addRow("config", config);
  }
  
  if(!db->tableExists("replacements")) {
    y::data::row replacements;
    replacements.addInt("ID");
    replacements["ID"].primaryKey(true).required(true).autoIncrement(true);
    replacements.addString("original").addString("replacement");
    replacements["replacement"].stringLength(128);
    db->createTable("replacements", replacements);
  }
  
  if(!db->tableExists("validUsers")) {
    y::data::row users;
    users.addInt("ID");
    users["ID"].primaryKey(true).required(true).autoIncrement(true);
    users.addString8("accountName");
    
    db->createTable("validUsers", users);
  }
    
  loaded = false;
}

void dataconnect::load() {
  if(loaded) return;
  container<y::data::row> rows;
  container<y::data::order> order;
  order.New().setKey("name");
  db->getAllRows("submissions", rows, order);
  for (int i = 0; i < rows.elms(); i++) {
    entries.emplace_back();
    entries.back().ID = rows[i]["ID"].asString8();
    entries.back().name = rows[i]["name"].asString();
    entries.back().surname = rows[i]["surname"].asString();
    entries.back().servername = rows[i]["servername"].asString();
    entries.back().birthday = rows[i]["birthday"].asDate();
    entries.back().group = rows[i]["classgroup"].asString();
    entries.back().mail = rows[i]["mail"].asString();
    entries.back().answer1 = rows[i]["answer1"].asString();
    entries.back().answer2 = rows[i]["answer2"].asString();
    entries.back().answer3 = rows[i]["answer3"].asString();
    entries.back().answer4 = rows[i]["answer4"].asString();
    entries.back().photo = rows[i]["photo"].asString();
    entries.back().submitDate = rows[i]["submitDate"].asDate();
    entries.back().approved = rows[i]["approved"].asBool();
    entries.back().changed = false;
  }
  
  container<y::data::row> config;
  db->getAllRows("config", config);
  if(config.elms()) {
    openDate  = config[0]["openDate" ].asDate();
    closeDate = config[0]["closeDate"].asDate();
    question[0] = config[0]["question1"].asString();
    question[1] = config[0]["question2"].asString();
    question[2] = config[0]["question3"].asString();
    question[3] = config[0]["question4"].asString();
  }
  
  db->getAllRows("replacements", replacements);
  
  db->getAllRows("validUsers", validUsers);
  
  
  loaded = true;
}

void dataconnect::save(int entry) {
  y::data::row row;
  row.addString("name", entries[entry].name);
  row.addString("surname", entries[entry].surname);
  row.addDate("birthday", entries[entry].birthday);
  row.addString("classgroup", entries[entry].group);
  row.addString("mail", entries[entry].mail);
  row.addString("answer1", entries[entry].answer1);
  row.addString("answer2", entries[entry].answer2);
  row.addString("answer3", entries[entry].answer3);
  row.addString("answer4", entries[entry].answer4);
  row.addString("photo", entries[entry].photo);
  row.addBool("approved", entries[entry].approved);
  y::data::field condition("ID", entries[entry].ID);
  db->setRow("submissions", row, condition);
  entries[entry].changed = false;
}

void dataconnect::remove(int value) {
  y::data::field condition("ID", entries[value].ID);
  db->delRow("submissions", condition);
  entries.erase(entries.begin() + value);
}

Wt::WDate dataconnect::getOpenDate() {
  Wt::WDate date;
  date.setDate(openDate.year(), openDate.month(), openDate.day());
  return date;
}

void dataconnect::setOpenDate(const Wt::WDate& date) {
  openDate.day(date.day());
  openDate.month(date.month());
  openDate.year(date.year());
  y::data::row row;
  row.addDate("openDate", openDate);
  y::data::field condition("ID", 1);
  db->setRow("config", row, condition);
}

Wt::WDate dataconnect::getCloseDate() {
  Wt::WDate date;
  date.setDate(closeDate.year(), closeDate.month(), closeDate.day());
  return date;
}

void dataconnect::setCloseDate(const Wt::WDate& date) {
  closeDate.day(date.day());
  closeDate.month(date.month());
  closeDate.year(date.year());
  y::data::row row;
  row.addDate("closeDate", closeDate);
  y::data::field condition("ID", 1);
  db->setRow("config", row, condition);
}

Wt::WString dataconnect::getQuestion(int nr) {
  return strWt(question[nr]);
}

void dataconnect::setQuestion(int nr, const Wt::WString& question) {
  this->question[nr] = str16(question.toUTF8()); 
  y::data::row row;
  switch(nr) {
    case 0: row.addString("question1", this->question[0]); break;
    case 1: row.addString("question2", this->question[1]); break;
    case 2: row.addString("question3", this->question[2]); break;
    case 3: row.addString("question4", this->question[3]); break;
  }
  y::data::field condition("ID", 1);
  db->setRow("config", row, condition);
}

void dataconnect::addUser(const std::string& name) {
  y::data::row row;
  row.addString8("accountName", name);
  db->addRow("validUsers", row);
  
  validUsers.clear();
  db->getAllRows("validUsers", validUsers);
}

void dataconnect::delUser(const std::string& name) {
  y::data::field condition("accountName", name);
  db->delRow("validUsers", condition);
  
  validUsers.clear();
  db->getAllRows("validUsers", validUsers);
}

void dataconnect::reloadEntries(const std::string& orderBy) {
  entries.clear();
  
  container<y::data::row> rows;
  container<y::data::order> order;
  order.New().setKey(orderBy);
  if(orderBy.compare("classgroup")) {
    order.New().setKey("surname");
  }
  db->getAllRows("submissions", rows, order);
  
  for (int i = 0; i < rows.elms(); i++) {
    entries.emplace_back();
    entries.back().ID = rows[i]["ID"].asString8();
    entries.back().name = rows[i]["name"].asString();
    entries.back().surname = rows[i]["surname"].asString();
    entries.back().servername = rows[i]["servername"].asString();
    entries.back().birthday = rows[i]["birthday"].asDate();
    entries.back().group = rows[i]["classgroup"].asString();
    entries.back().mail = rows[i]["mail"].asString();
    entries.back().answer1 = rows[i]["answer1"].asString();
    entries.back().answer2 = rows[i]["answer2"].asString();
    entries.back().answer3 = rows[i]["answer3"].asString();
    entries.back().answer4 = rows[i]["answer4"].asString();
    entries.back().photo = rows[i]["photo"].asString();
    entries.back().submitDate = rows[i]["submitDate"].asDate();
    entries.back().approved = rows[i]["approved"].asBool();
    entries.back().changed = false;
  }
}

void dataconnect::setReplacement(const std::u16string& key, const std::u16string& value) {
  bool found = false;
  int i = 0;
  for (; i < replacements.elms(); i++) {
    if(replacements[i]["original"].asString().compare(key) == 0) {
      replacements[i]["replacement"].setString(value);
      found = true;
      break;
    }
  }
  
  if(found) {
    y::data::field condition("original", key);
    y::data::row row;
    row.addString("replacement", value);
    db->setRow("replacements", row, condition);
  } else {
    y::data::row row;
    row.addString("original", key);
    row.addString("replacement", value);
    db->addRow("replacements", row);
  }
  
  
}