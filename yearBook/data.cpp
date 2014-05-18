/* 
 * File:   data.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 8:30 PM
 */

#include <Wt/WDate>

#include "data.h"
#include <admintools.h>

dataconnect::dataconnect() {
  server = std::unique_ptr<y::data::server>(new y::data::server);
  db = std::unique_ptr<y::data::database>(new y::data::database(*server));
  
  if(!server->hasDatabase("yearbookApp")) {
    server->create("yearbookApp");
    db->use("yearbookApp");
    
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
    
  } else {
    db->use("yearbookApp");
  }
  newEntry = true;
}

bool dataconnect::load(const Wt::WString & ID) {
  y::data::field condition;
  condition.name("ID");
  condition.setString8(ID.toUTF8());
  container<y::data::row> rows;
  db->getRows("submissions", rows, condition);
  if(rows.elms() > 0) {
    y::data::row & result = rows[0];
    _ID = result["ID"].asString8();
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
}

void dataconnect::save() {
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
    row.addString8("ID", _ID);
    db->addRow("submissions", row);
    newEntry = false;
  } else {
    y::data::field condition;
    condition.name("ID");
    condition.setString8(_ID);

    db->setRow("submissions", row, condition);
  }
}

void dataconnect::ID(const Wt::WString& value) {
  _ID = value.toUTF8();
}

void dataconnect::name(const Wt::WString& value) {
  _name = str16(value.toUTF8());
}

void dataconnect::surname(const Wt::WString& value) {
  _surname = str16(value.toUTF8());
}

void dataconnect::servername(const Wt::WString& value) {
  _servername = str16(value.toUTF8());
}

void dataconnect::group(const Wt::WString& value) {
  _group = str16(value.toUTF8());
}

void dataconnect::mail(const Wt::WString& value) {
  _mail = str16(value.toUTF8());
}

void dataconnect::answer1(const Wt::WString& value) {
  _answer1 = str16(value.toUTF8());
}

void dataconnect::answer2(const Wt::WString& value) {
  _answer2 = str16(value.toUTF8());
}

void dataconnect::answer3(const Wt::WString& value) {
  _answer3 = str16(value.toUTF8());
}

void dataconnect::answer4(const Wt::WString& value) {
  _answer4 = str16(value.toUTF8());
}

void dataconnect::photo(const Wt::WString& value) {
  _photo = str16(value.toUTF8());
}

void dataconnect::birthday(const Wt::WDate& value) {
  _birthday.day(value.day());
  _birthday.month(value.month());
  _birthday.year(value.year());
}

Wt::WString dataconnect::ID() {
  return _ID;
}

Wt::WString dataconnect::name() {
  return str8(_name);
}

Wt::WString dataconnect::surname() {
  return str8(_surname);
}

Wt::WString dataconnect::servername() {
  return str8(_servername);
}

Wt::WString dataconnect::group() {
  return str8(_group);
}

Wt::WString dataconnect::mail() {
  return str8(_mail);
}

Wt::WString dataconnect::answer1() {
  return str8(_answer1);
}

Wt::WString dataconnect::answer2() {
  return str8(_answer2);
}

Wt::WString dataconnect::answer3() {
  return str8(_answer3);
}

Wt::WString dataconnect::answer4() {
  return str8(_answer4);
}

Wt::WString dataconnect::photo() {
  return str8(_photo);
}

Wt::WDate dataconnect::birthday() {
  Wt::WDate result;
  result.setDate(_birthday.year(), _birthday.month(), _birthday.day());
  return result;
}


