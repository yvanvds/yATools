/* 
 * File:   account.cpp
 * Author: yvan
 * 
 * Created on January 14, 2014, 6:48 PM
 */

#include "ldap/account.h"
#include "dataset.h"
#include "samba/samba.h"
#include "server.h"
#include "utils/sha1.h"

y::ldap::account::account() : 
  _uidNumber(UID_NUMBER(0)),
  _uid(UID("")),
  _dn(DN("")),
  _cn(CN("")),
  _sn(SN("")),
  _fullName(FULL_NAME("")),
  _homeDir(HOMEDIR("")),
  _wisaID(WISA_ID(0)),
  _mail(MAIL("")),
  _birthDay(DATE(DAY(1), MONTH(1), YEAR(1))),
  _password(PASSWORD("")),
  _group(GID("")),
  _groupID(GID_NUMBER(0)),
  _new(true) 
  {}

bool y::ldap::account::load(const data& d) {
  _uidNumber(UID_NUMBER(std::stoi(d.getValue("uidNumber"))), true);
  _uid(UID(d.getValue("uid")), true);
  _dn(DN(d.getValue("DN")), true);
  _cn(CN(d.getValue("cn")), true);
  _sn(SN(d.getValue("sn")), true);
  _fullName(FULL_NAME(d.getValue("displayName")), true);
  _homeDir(HOMEDIR(d.getValue("homeDirectory")), true);
  _wisaID(WISA_ID(std::stoi(d.getValue("employeeNumber"))), true);
  _mail(MAIL(d.getValue("mail")), true);
  _password(PASSWORD(d.getValue("title")), true);
  _birthDay(DATE(d.getValue("roomNumber")), true);
  _group(GID(d.getValue("departmentNumber")), true);
  _groupID(GID_NUMBER(std::stoi(d.getValue("gidNumber"))), true);
  _new = false;
  return !_new;
}

bool y::ldap::account::load(const UID & id) {
  dataset d;
  std::string filter;
  filter = "uid="; filter.append(id());
  
  if(d.create(filter, "ou=People")) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(UID_NUMBER id) {
  dataset d;
  std::string filter;
  filter = "uidNumber="; filter.append(std::to_string(id()));
  
  if(d.create(filter)) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(const DN & id) {
  dataset d;
  std::string filter;
  filter = "DN="; filter.append(id());
  
  if(d.create(filter)) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::save() {
  dataset values;
  if(_password.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", "title");
    d.add("values", _password()());
  }
  
  if(values.elms()) {
    Server().setData(_dn(), values);
    return true;
  }
  return false;
}

bool y::ldap::account::isNew() {
  return _new;
}

void y::ldap::account::clear() {
  _new = true; 
  _uidNumber(UID_NUMBER(0));
  _uid(UID(""));
  _dn(DN(""));
  _cn(CN(""));
  _sn(SN(""));
  _fullName(FULL_NAME(""));
  _homeDir(HOMEDIR(""));
  _wisaID(WISA_ID(0));
  _mail(MAIL(""));
  _password(PASSWORD(""));
  _birthDay(DATE(DAY(1), MONTH(1), YEAR(1)));
  _group(GID(""));
  _groupID(GID_NUMBER(0));
}

const y::ldap::UID_NUMBER & y::ldap::account::uidNumber() const {
  return _uidNumber();
}

const y::ldap::UID & y::ldap::account::uid() const {
  return _uid();
}

const y::ldap::DN & y::ldap::account::dn() const {
  return _dn();
}

const y::ldap::CN & y::ldap::account::cn() const {
  return _cn();
}

const y::ldap::SN & y::ldap::account::sn() const {
  return _sn();
}

const y::ldap::FULL_NAME & y::ldap::account::fullName() const {
  return _fullName();
}

const y::ldap::HOMEDIR & y::ldap::account::homeDir() const {
  return _homeDir();
}

const y::ldap::WISA_ID & y::ldap::account::wisaID() const {
  return _wisaID();
}

const y::ldap::MAIL & y::ldap::account::mail() const {
  return _mail();
}

const y::ldap::DATE & y::ldap::account::birthDay() const {
  return _birthDay();
}

const y::ldap::PASSWORD & y::ldap::account::password() const {
  return _password();
}

const y::ldap::GID & y::ldap::account::group() const {
  return _group();
}

const y::ldap::GID_NUMBER & y::ldap::account::groupID() const {
  return _groupID();
}

y::ldap::account & y::ldap::account::uidNumber(const UID_NUMBER& value) {
  _uidNumber(value);
  return *this;
}

y::ldap::account & y::ldap::account::uid(const UID& value) {
  _uid(value);
  return *this;
}

y::ldap::account & y::ldap::account::cn(const CN& value) {
  _cn(value);
  return *this;
}

y::ldap::account & y::ldap::account::sn(const SN& value) {
  _sn(value);
  return *this;
}

y::ldap::account & y::ldap::account::fullName(const FULL_NAME& value) {
  _fullName(value);
  return *this;
}

y::ldap::account & y::ldap::account::homeDir(const HOMEDIR& value) {
  _homeDir(value);
  return *this;
}

y::ldap::account & y::ldap::account::wisaID(const WISA_ID& value) {
  _wisaID(value);
  return *this;
}

y::ldap::account & y::ldap::account::mail(const MAIL& value) {
  _mail(value);
  return *this;
}

y::ldap::account & y::ldap::account::birthDay(const DATE& value) {
  _birthDay(value);
  return *this;
}

y::ldap::account & y::ldap::account::password(const PASSWORD& value) {
  std::string origin = value();
  
  // let samba change the password for us
  //samba::changePassword(_uid()(), origin);
  
  // the password value from ldap sets the title value, which is used
  // to sync with google
  _password(PASSWORD(y::utils::sha1(origin)));
  return *this;
}

y::ldap::account & y::ldap::account::group(const GID& value) {
  _group(value);
  return *this;
}

y::ldap::account & y::ldap::account::groupID(const GID_NUMBER& value) {
  _groupID(value);
  return *this;
}

