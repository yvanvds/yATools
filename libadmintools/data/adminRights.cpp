/* 
 * File:   adminRights.cpp
 * Author: yvan
 * 
 * Created on June 17, 2015, 6:07 PM
 */

#include "adminRights.h"
#include "database.h"

y::data::adminRights::adminRights() {
  y::data::database db;
  db.open();
  db.use("admintools");
  
  if(!db.tableExists("adminrights")) {
    y::data::row desc;
    desc.addInt("ID");
    desc["ID"].primaryKey(true).required(true).autoIncrement(true);
    desc.addString("userName");
    desc["userName"].stringLength(16);
    desc.addShort("category");
    
    db.createTable("adminrights", desc);
  }
  db.close();
  
  refreshData();
}

void y::data::adminRights::refreshData() {
  data.clear();
  y::data::database db;
  db.open();
  db.use("admintools");
  
  for(int i = 0; i < ADMIN_NUM; i++) {
    data.New();
  }
  
  container<y::data::row> rows;
  db.getAllRows("adminrights", rows);
  for(int i = 0; i < rows.elms(); i++) {
    nameIDPair & np = data[rows[i]["category"].asShort()].New();
    np.name= rows[i]["userName"].asString();
    np.ID = rows[i]["ID"].asInt();
  }
  db.close();
}

bool y::data::adminRights::has(const ::UID & name, ADMINRIGHTS category) {
  for(int i = 0; i < data[category].elms(); i++) {
    if(data[category][i].name == name.get()) return true;
  }
  return false;
}

void y::data::adminRights::add(const ::UID & name, ADMINRIGHTS category) {
  for(int i = 0; i < data[category].elms(); i++) {
    if(data[category][i].name == name.get()) return;
  }
  
  y::data::database db;
  db.open();
  db.use("admintools");
  y::data::row row;
  row.addString("userName", name.get());
  row.addShort("category", category);
  db.addRow("adminrights", row);
  db.close();
  
  refreshData();
}

void y::data::adminRights::remove(const ::UID & name, ADMINRIGHTS category) {
  for(int i = 0; i < data[category].elms(); i++) {
    if(data[category][i].name == name.get()) {
      y::data::database db;
      db.open();
      db.use("admintools");
      y::data::field condition("ID", data[category][i].ID);
      db.delRow("adminrights", condition);
      db.close();
      
      refreshData();
      return;
    }
  }
}

