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
          _description("description" , DESCRIPTION("")),
          _titular    ("titular"     , TITULAR    (DN(""))),
          _adjunct    ("adjunct"     , ADJUNCT    (DN(""))),
          _adminGroup ("adminGroupID", ADMINGROUP (0 )),
          _schoolID   ("schoolID"    , SCHOOL_ID  (0 ))
          {}

bool y::ldap::schoolClass::load(const CN & cn) {
  dataset d(server);
  string filter("cn=" + cn.get());
  
  if(d.create(filter, "ou=classes")) {
    loadData(d.get(0));
  } else {
    _cn(CN(cn));
  }
  
  return !_new;
}

bool y::ldap::schoolClass::loadData(const data& d) {
  _dn.readFromLdap(d);
  _cn.readFromLdap(d);
  _description.readFromLdap(d);
  _titular.readFromLdap(d);
  _adjunct.readFromLdap(d);
  _adminGroup.readFromLdap(d);
  _schoolID.readFromLdap(d);
  
  
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
    if(_students[i] == dn.get()) {
      _students.remove(i);
      _flaggedForCommit = true;
      return true;
    }
  }
  return false;
}

bool y::ldap::schoolClass::addStudent(const DN& dn) {
  for(int i = 0; i < _students.elms(); i++) {
    if(_students[i] == dn.get()) {
      return false; // student is already in this class
    }
  }
  _students.New() = dn.get();
  _flaggedForCommit = true;
  return true;
}

void y::ldap::schoolClass::clear() {
  _students.clear();
  _studentsInLDAP.clear();
  _description.reset(DESCRIPTION(""));
  _titular    .reset(TITULAR    (DN("")));
  _adjunct    .reset(ADJUNCT    (DN("")));
  _adminGroup .reset(ADMINGROUP (0 ));
  _schoolID   .reset(SCHOOL_ID  (0 ));
}

void y::ldap::schoolClass::beforeRemove() {
  y::Smartschool().deleteClass(*this);
}

bool y::ldap::schoolClass::addNew(dataset& values) {
  // create class first
  string dn("cn=" + _cn().get());
  dn += ",ou=classes,";
  dn += utils::Config().getLdapBaseDN();
  _dn(DN(dn), true);

  data & d = values.New(NEW);
  d.add("type", "objectClass");
  d.add("values", "top");
  d.add("values", "schoolClass");
  
  data & cn = values.New(NEW);
  cn.add("type", "cn");
  cn.add("values", _cn().get());
  
  data & description = values.New(NEW);
  description.add("type", "description");
  description.add("values", _description().get());
  
  if(adminGroup().get() != 0) {
    data & adminGroup = values.New(NEW);
    adminGroup.add("type", "adminGroupID");
    adminGroup.add("values", string(_adminGroup().get()));
  }
  
  if(schoolID().get() != 0) {
    data & schoolID = values.New(NEW);
    schoolID.add("type", "schoolID");
    schoolID.add("values", string(_schoolID().get()));
  }
  
  if(!titular().get().get().empty()) {
    data & titular = values.New(NEW);
    titular.add("type", "titular");
    titular.add("values", _titular().get().get());
  }
  /*
  if(!adjunct().get().get().empty()) {
    data & adjunct = values.New(NEW);
    adjunct.add("type", "adjunct");
    adjunct.add("values", _adjunct().get().get());
  }
  
  if(_students.elms()) {
    data & students = values.New(NEW);
    students.add("type", "member");
    for(int i = 0; i < _students.elms(); i++) {
      students.add("values", _students[i]);
    }
  }*/
  
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
  
  _description.saveToLdap(values);
  _adminGroup.saveToLdap(values);
  _schoolID.saveToLdap(values);
  _titular.saveToLdap(values);
  _adjunct.saveToLdap(values);
  
  // update smartschool
  y::Smartschool().addClass(*this);
  return true;
}

const DESCRIPTION & y::ldap::schoolClass::description() const {
  return _description();
}

const TITULAR & y::ldap::schoolClass::titular() const {
  return _titular();
}

const ADJUNCT & y::ldap::schoolClass::adjunct() const {
  return _adjunct();
}

const ADMINGROUP & y::ldap::schoolClass::adminGroup() const {
  return _adminGroup();
}

const SCHOOL_ID & y::ldap::schoolClass::schoolID() const {
  return _schoolID();
}

y::ldap::schoolClass & y::ldap::schoolClass::description(const DESCRIPTION & desc) {
  _description(desc);
  return *this;
}

y::ldap::schoolClass & y::ldap::schoolClass::titular(const TITULAR & value) {
  _titular(value);
  return *this;
}

y::ldap::schoolClass & y::ldap::schoolClass::adjunct(const ADJUNCT & value) {
  _adjunct(value);
  return *this;
}

y::ldap::schoolClass & y::ldap::schoolClass::adminGroup(const ADMINGROUP & value) {
  _adminGroup(value);
  return *this;
}

y::ldap::schoolClass & y::ldap::schoolClass::schoolID(const SCHOOL_ID & value) {
  _schoolID(value);
  return *this;
}
