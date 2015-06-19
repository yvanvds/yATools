/* 
 * File:   schoolClass.cpp
 * Author: yvan
 * 
 * Created on June 12, 2015, 4:07 PM
 */

#include "schoolClass.h"
#include "dataset.h"
#include "utils/config.h"
#include "server.h"
#include "smartschool/smartschool.h"
#include <assert.h>
#include "defines.h"
#include "utils/log.h"
#include <exception>

y::ldap::schoolClass::schoolClass(y::ldap::server* server) 
        : ldapObject(server),
          _description(""),
          _titular(""),
          _adjunct(""),
          _adminCode(0),
          _schoolID(0)
          {}

bool y::ldap::schoolClass::load(const string & cn) {
  dataset d(server);
  string filter("cn=" + cn);
  
  if(d.create(filter, "ou=classes")) {
    loadData(d.get(0));
  } else {
    _cn(cn);
  }
  
  return !_new;
}

bool y::ldap::schoolClass::loadData(const data& d) {
  _dn(DN(d.getValue("DN")), true);
  _cn(d.getValue("cn"), true);
  _description(d.getValue("description"), true);
  _titular(d.getValue("titular"), true);
  _adjunct(d.getValue("adjunct"), true);
  try {
    _adminCode(d.getValue("adminGroupID").asInt(), true);
  } catch (std::exception & e) {
    string message("Error in schoolClass::loadData adminGroupID: ");
    message += e.what();
    utils::Log().add(message);
    _adminCode(0);
  }
  
  try {
    _schoolID(d.getValue("schoolID").asInt(), true);
  } catch (std::exception & e) {
    string message("Error in schoolClass::loadData schoolID: ");
    message += e.what();
    utils::Log().add(message);
    _schoolID(0);
  }
  
  for(int i = 0; i < d.elms("member"); i++) {
    string & student = _students.New();
    student = d.getValue("member", i);
    _studentsInLDAP.New() = student;
  }
  _new = false;
  return true;
}

container<string> & y::ldap::schoolClass::students() {
  return _students;
}

bool y::ldap::schoolClass::removeStudent(const DN& dn) {
  for(int i = 0; i < _students.elms(); i++) {
    if(_students[i] == dn()) {
      _students.remove(i);
      _flaggedForCommit = true;
      return true;
    }
  }
  return false;
}

bool y::ldap::schoolClass::addStudent(const DN& dn) {
  for(int i = 0; i < _students.elms(); i++) {
    if(_students[i] == dn()) {
      return false; // student is already in this class
    }
  }
  _students.New() = dn();
  _flaggedForCommit = true;
  return true;
}

void y::ldap::schoolClass::clear() {
  _students.clear();
  _studentsInLDAP.clear();
  _description("");
  _titular("");
  _adjunct("");
  _adminCode(0);
  _schoolID(0);
}

void y::ldap::schoolClass::beforeRemove() {
  y::Smartschool().deleteClass(*this);
}

bool y::ldap::schoolClass::addNew(dataset& values) {
  // create class first
  string dn("cn=" + _cn());
  dn += ",ou=classes,";
  dn += utils::Config().getLdapBaseDN();
  _dn(DN(dn), true);

  data & d = values.New(NEW);
  d.add("type", "objectClass");
  d.add("values", "top");
  d.add("values", "schoolClass");
  
  data & cn = values.New(NEW);
  cn.add("type", "cn");
  cn.add("values", _cn());
  
  data & description = values.New(NEW);
  description.add("type", "description");
  description.add("values", _description());
  
  if(adminCode() != 0) {
    data & adminCode = values.New(NEW);
    adminCode.add("type", "adminGroupID");
    adminCode.add("values", string(_adminCode()));
  }
  
  if(schoolID() != 0) {
    data & schoolID = values.New(NEW);
    schoolID.add("type", "schoolID");
    schoolID.add("values", string(_schoolID()));
  }
  
  if(!titular()().empty()) {
    data & titular = values.New(NEW);
    titular.add("type", "titular");
    titular.add("values", _titular());
  }
  
  if(!adjunct()().empty()) {
    data & adjunct = values.New(NEW);
    adjunct.add("type", "adjunct");
    adjunct.add("values", _adjunct());
  }
  
  if(_students.elms()) {
    data & students = values.New(NEW);
    students.add("type", "member");
    for(int i = 0; i < _students.elms(); i++) {
      students.add("values", _students[i]);
    }
  }
  
  y::Smartschool().addClass(*this);
  
  return true;
}

bool y::ldap::schoolClass::update(dataset& values) {
  // remove students if needed
  data * studentDelete = nullptr;
  for(int i = 0; i < _studentsInLDAP.elms(); i++) {
    const string & student = _studentsInLDAP[i];
    bool found = false;
    for(int j = 0; j < _students.elms(); j++) {
      if(student == _students[j]) found = true;
    }
    if(!found) {
      if(!studentDelete) {
        studentDelete = &values.New(DELETE);
        studentDelete->add("type", "member");
      }
      studentDelete->add("values", student);
    }
  }
  
  // add students if needed
  data * studentAdd = nullptr;
  for(int i = 0; i < _students.elms(); i++) {
    const string & student = _students[i];
    bool found = false;
    for(int j = 0; j < _studentsInLDAP.elms(); j++) {
      if(student == _studentsInLDAP[j]) found = true;
    }
    if(!found) {
      if(!studentAdd) {
        studentAdd = &values.New(ADD);
        studentAdd->add("type", "member");
      }
      studentAdd->add("values", student);
    }
  }
  
  if(_description.changed()) {
    data & description = values.New(MODIFY);
    description.add("type", "description");
    description.add("values", _description());
  }
  
  if(_adminCode.changed()) {
    data & adminCode = values.New(MODIFY);
    adminCode.add("type", "adminGroupID");
    adminCode.add("values", string(_adminCode()));
  }
  
  if(_schoolID.changed()) {
    data & schoolID = values.New(MODIFY);
    schoolID.add("type", "schoolID");
    schoolID.add("values", string(_schoolID()));
  }
  
  if(_titular.changed()) {
    data & titular = values.New(MODIFY);
    titular.add("type", "titular");
    titular.add("values", _titular());
  }
  
  if(_adjunct.changed()) {
    data & adjunct = values.New(MODIFY);
    adjunct.add("type", "adjunct");
    adjunct.add("values", _adjunct());
  }
  
  // update smartschool
  y::Smartschool().addClass(*this);
  return true;
}

const string & y::ldap::schoolClass::description() const {
  return _description();
}

DN y::ldap::schoolClass::titular() const {
  return DN(_titular());
}

DN y::ldap::schoolClass::adjunct() const {
  return DN(_adjunct());
}

int y::ldap::schoolClass::adminCode() const {
  return _adminCode();
}

int y::ldap::schoolClass::schoolID() const {
  return _schoolID();
}

y::ldap::schoolClass & y::ldap::schoolClass::description(const string& desc) {
  _description(desc);
  return *this;
}

y::ldap::schoolClass & y::ldap::schoolClass::titular(const DN& dn) {
  _titular(dn());
  return *this;
}

y::ldap::schoolClass & y::ldap::schoolClass::adjunct(const DN& dn) {
  _adjunct(dn());
  return *this;
}

y::ldap::schoolClass & y::ldap::schoolClass::adminCode(int id) {
  _adminCode(id);
  return *this;
}

y::ldap::schoolClass & y::ldap::schoolClass::schoolID(int id) {
  _schoolID(id);
  return *this;
}
