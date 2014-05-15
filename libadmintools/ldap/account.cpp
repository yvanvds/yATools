/* 
 * File:   account.cpp
 * Author: yvan
 * 
 * Created on January 14, 2014, 6:48 PM
 */

#include "ldap/account.h"
#include "dataset.h"

y::ldap::account::account() : 
  _new(true), 
  _uidNumber(UID_NUMBER(0)),
  _uid(UID("")),
  _dn(DN("")),
  _cn(CN("")),
  _sn(SN("")),
  _fullName(FULL_NAME("")),
  _homeDir(HOMEDIR("")),
  _wisaID(WISA_ID(0)),
  _mail(MAIL("")),
  _password(PASSWORD("")),
  _birthDay(DATE(DAY(1), MONTH(1), YEAR(1))),
  _group(GID("")),
  _groupID(GID_NUMBER(0))
  {}

bool y::ldap::account::load(const UID & id) {
  dataset d;
  std::string filter;
  filter = "uid="; filter.append(id());
  
  if(d.create(filter)) {
    data & temp = d.get(0);
    _uidNumber(UID_NUMBER(std::stoi(temp.getValue("uidNumber"))), true);
    _uid(UID(temp.getValue("uid")), true);
    _dn(DN(temp.getValue("DN")), true);
    _cn(CN(temp.getValue("cn")), true);
    _sn(SN(temp.getValue("sn")), true);
    _fullName(FULL_NAME(temp.getValue("displayName")), true);
    _homeDir(HOMEDIR(temp.getValue("homeDirectory")), true);
    _wisaID(WISA_ID(std::stoi(temp.getValue("employeeNumber"))), true);
    _mail(MAIL(temp.getValue("mail")), true);
    _password(PASSWORD(temp.getValue("userPassword")), true);
    _birthDay(DATE(temp.getValue("roomNumber")), true);
    _group(GID(temp.getValue("departmentNumber")), true);
    _groupID(GID_NUMBER(std::stoi(temp.getValue("gidNumber"))), true);
    _new = false;
  }
  
  return !_new;
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
}

y::ldap::account & y::ldap::account::uid(const UID& value) {
  _uid(value);
}

y::ldap::account & y::ldap::account::cn(const CN& value) {
  _cn(value);
}

y::ldap::account & y::ldap::account::sn(const SN& value) {
  _sn(value);
}

y::ldap::account & y::ldap::account::fullName(const FULL_NAME& value) {
  _fullName(value);
}

y::ldap::account & y::ldap::account::homeDir(const HOMEDIR& value) {
  _homeDir(value);
}

y::ldap::account & y::ldap::account::wisaID(const WISA_ID& value) {
  _wisaID(value);
}

y::ldap::account & y::ldap::account::mail(const MAIL& value) {
  _mail(value);
}

y::ldap::account & y::ldap::account::birthDay(const DATE& value) {
  _birthDay(value);
}

y::ldap::account & y::ldap::account::password(const PASSWORD& value) {
  _password(value);
}

y::ldap::account & y::ldap::account::group(const GID& value) {
  _group(value);
}

y::ldap::account & y::ldap::account::groupID(const GID_NUMBER& value) {
  _groupID(value);
}

