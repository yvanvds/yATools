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
  db->use("yearbookApp");
  loaded = false;
}

void dataconnect::load() {
  if(loaded) return;
  container<y::data::row> rows;
  db->getAllRows("submissions", rows);
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
