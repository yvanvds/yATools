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
  
  if(!server->hasDatabase(L"admintools")) {
    server->create(L"admintools");
  }
  db->use(L"admintools");
  
  if(!db->tableExists(PROXY)) {
    y::data::row rooms;
    rooms.addString(L"ID");
    rooms[L"ID"].primaryKey(true).required(true);
    rooms.addInt(L"status" );
    rooms.addInt(L"defaultValue");
    db->createTable(PROXY, rooms);
    
    // add rooms we know
    {
      y::data::row row; row.addString(L"ID", L"CO112"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"CO114"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"CO116");
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"CO117"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"CO126"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"CO127"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"CO137"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"OLC"); 
      row.addInt(L"status", 2); row.addInt(L"defaultValue", 2);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"EC202"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"EC203"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
    {
      y::data::row row; row.addString(L"ID", L"VI215"); 
      row.addInt(L"status", 1); row.addInt(L"defaultValue", 1);
      db->addRow(PROXY, row);
    }
  }
  
  
}

bool y::utils::proxy::status(const std::wstring& room, STATUS status) {
  y::data::field condition;
  condition.name(L"ID");
  condition.setString(room);
  container<y::data::row> rows;
  
  db->getRows(PROXY, rows, condition);
  if(!rows.elms()) return false;
  
  y::data::row row;
  row.addInt(L"status", (int)status);
  db->setRow(PROXY, row, condition);
  return true;
}

y::utils::proxy::STATUS y::utils::proxy::status(const std::wstring & room) {
  y::data::field condition;
  condition.name(L"ID");
  condition.setString(room);
  container<y::data::row> rows;
  
  db->getRows(PROXY, rows, condition);
  if(!rows.elms()) return INVALID;
  
  return (STATUS)rows[0][L"status"].asInt();
}

y::utils::proxy & y::utils::proxy::reset() {
  container<y::data::row> rows;
  db->getAllRows(PROXY, rows);
  
  for (int i = 0; i < rows.elms(); i++) {
    y::data::field condition;
    condition.name(L"ID").setString(rows[i][L"ID"].asString());
    
    y::data::row data;
    data.addInt(L"status", rows[i][L"defaultValue"].asInt());
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
  std::wofstream file;
  file.open("/etc/squid3/roomfilter.conf", std::ios::out | std::ios::trunc);
  for (int i = 0; i < rows.elms(); i++) {
    if(rows[i][L"status"].asInt() == (int)OPEN) {
      file << L"http_access allow lokaal" << rows[i][L"ID"].asString() << std::endl;
    } else if (rows[i][L"status"].asInt() ==(int)CLOSED) {
      file << L"http_access deny lokaal" << rows[i][L"ID"].asString() << std::endl;
    }
  }
  file.close();
  system("sudo /sbin/restartSquid");
}


