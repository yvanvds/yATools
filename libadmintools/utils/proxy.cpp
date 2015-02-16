/* 
 * File:   proxy.cpp
 * Author: yvan
 * 
 * Created on February 15, 2015, 10:30 PM
 */

#include "proxy.h"
#include <fstream>
#include <stdlib.h>

y::utils::proxy & y ::utils::Proxy() {
  static proxy p;
  return p;
}

y::utils::proxy::proxy() {
  server = std::unique_ptr<y::data::server  >(new y::data::server);
  db     = std::unique_ptr<y::data::database>(new y::data::database(*server));
  
  if(!server->hasDatabase("admintools")) {
    server->create("admintools");
  }
  db->use("admintools");
  
  if(!db->tableExists(PROXY)) {
    y::data::row rooms;
    rooms.addString8("ID");
    rooms["ID"].primaryKey(true).required(true);
    rooms.addInt("status" );
    rooms.addInt("defaultValue");
    db->createTable(PROXY, rooms);
    
    // add rooms we know
    {
      y::data::row row; row.addString8("ID", "CO112"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "CO114"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "CO116");
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "CO117"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "CO126"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "CO127"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "CO137"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "OLC"); 
      row.addInt("status", 2); row.addInt("defaultValue", 2);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "EC202"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "EC203"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString8("ID", "VI215"); 
      row.addInt("status", 1); row.addInt("defaultValue", 1);
      db->addRow(PROXY, row);
    }
  }
  
  
}

bool y::utils::proxy::status(const std::string& room, STATUS status) {
  y::data::field condition;
  condition.name("ID");
  condition.setString8(room);
  container<y::data::row> rows;
  
  db->getRows(PROXY, rows, condition);
  if(!rows.elms()) return false;
  
  y::data::row row;
  row.addInt("status", (int)status);
  db->setRow(PROXY, row, condition);
  return true;
}

y::utils::proxy::STATUS y::utils::proxy::status(const std::string & room) {
  y::data::field condition;
  condition.name("ID");
  condition.setString8(room);
  container<y::data::row> rows;
  
  db->getRows(PROXY, rows, condition);
  if(!rows.elms()) return INVALID;
  
  return (STATUS)rows[0]["status"].asInt();
}

y::utils::proxy & y::utils::proxy::reset() {
  container<y::data::row> rows;
  db->getAllRows(PROXY, rows);
  
  for (int i = 0; i < rows.elms(); i++) {
    y::data::field condition;
    condition.name("ID").setString8(rows[i]["ID"].asString8());
    
    y::data::row data;
    data.addInt("status", rows[i]["defaultValue"].asInt());
    db->setRow(PROXY, data, condition);
  }
  return *this;
}

void y::utils::proxy::getAllRooms(container<y::data::row>& rows) {
  db->getAllRows(PROXY, rows);
}

void y::utils::proxy::apply() {
  container<y::data::row> rows;
  db->getAllRows(PROXY, rows);
  
  // open file and remove current content
  std::ofstream file;
  file.open("/etc/squid3/roomfilter.conf", std::ios::out | std::ios::trunc);
  for (int i = 0; i < rows.elms(); i++) {
    if(rows[i]["status"].asInt() == (int)OPEN) {
      file << "http_access allow lokaal" << rows[i]["ID"].asString8() << std::endl;
    } else if (rows[i]["status"].asInt() ==(int)CLOSED) {
      file << "http_access deny lokaal" << rows[i]["ID"].asString8() << std::endl;
    }
  }
  file.close();
  system("sudo /sbin/restartSquid");
}


