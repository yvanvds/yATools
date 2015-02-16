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
#include "utils/config.h"
#include "utils/log.h"
#include "smartschool/smartschool.h"

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
  _new(true),
  _hasKrbName(false),
  _hasGroup(false),
  _hasWisaID(false),
  _hasMail(false),
  _hasBirthday(false)
  {}

bool y::ldap::account::load(const data& d) {
  if(d.getValue(TYPE_UID_NUMBER).size()) {
    try {
      _uidNumber(UID_NUMBER(std::stoi(d.getValue(TYPE_UID_NUMBER))), true);
    } catch(const std::invalid_argument &e) {
      std::string message("Invalid ldap::UID_NUMBER conversion: ");
      message += d.getValue(TYPE_UID_NUMBER);
      utils::Log().add(message);
      return false;
    }
  } else {
    _uidNumber(UID_NUMBER(0));
    //assert(false);
  }
  
  _uid      (UID       (          d.getValue(TYPE_UID       ) ), true);
  _dn       (DN        (          d.getValue(TYPE_DN        ) ), true);
  _cn       (CN        (          d.getValue(TYPE_CN        ) ), true);
  _sn       (SN        (          d.getValue(TYPE_SN        ) ), true);
  _fullName (FULL_NAME (          d.getValue(TYPE_FULL_NAME ) ), true);
  _homeDir  (HOMEDIR   (          d.getValue(TYPE_HOMEDIR   ) ), true);
  _mail     (MAIL      (          d.getValue(TYPE_MAIL      ) ), true);
  _password (PASSWORD  (          d.getValue(TYPE_PASSWORD  ) ), true); 
  _group    (GID       (          d.getValue(TYPE_GID       ) ), true);
  
  if(d.getValue(TYPE_GID_NUMBER).size()) {
    try {
      _groupID(GID_NUMBER(std::stoi(d.getValue(TYPE_GID_NUMBER))), true);
    } catch(const std::invalid_argument &e) {
      std::string message("Invalid ldap::GID_NUMBER conversion: ");
      message += d.getValue(TYPE_GID_NUMBER);
      utils::Log().add(message);
      return false;
    }  
  } else {
    _groupID(GID_NUMBER(0));
    //assert(false);
  }
  
  if(d.getValue(TYPE_BIRTHDAY).size()) {
    _birthDay (DATE(d.getValue(TYPE_BIRTHDAY)), true);
    _hasBirthday = true;
  } else {
    _birthDay(DATE("0"));
  }
  
  if(d.getValue(TYPE_WISA_ID).size()) {
    try {
      _wisaID(WISA_ID(std::stoi(d.getValue(TYPE_WISA_ID))), true);
      _hasWisaID = true;
    } catch(const std::invalid_argument &e) {
      std::string message("Invalid ldap::WISA_ID conversion: ");
      message += d.getValue(TYPE_WISA_ID);
      utils::Log().add(message);
      return false;
    }
  } else {
    _wisaID(WISA_ID(0));
  }

  if(d.getValue("krbName"    ).size()) _hasKrbName  = true;
  if(d.getValue(TYPE_GID     ).size()) _hasGroup    = true;
  if(d.getValue(TYPE_MAIL    ).size()) _hasMail     = true;
  _new = false;
  return !_new;
}

bool y::ldap::account::load(const UID & id) {
  dataset d;
  std::string filter(TYPE_UID);
  filter += "="; filter.append(id());
  
  if(d.create(filter, "ou=People")) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(UID_NUMBER id) {
  dataset d;
  std::string filter(TYPE_UID_NUMBER);
  filter += "="; filter.append(std::to_string(id()));
  
  if(d.create(filter)) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(const DN & id) {
  dataset d;  
  if(d.createFromDN(id())) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::save() {
  dataset values;
  
  // on first save, some new entries have to be added
  if(!_hasKrbName) {
    // add kerberos objectClass
    data & d = values.New(ADD);
    d.add("type", "objectClass");
    d.add("values", "kerberosSecurityObject");
    
    // add kerberos name (for short mail)
    std::string krbName(_uid()());
    krbName += "@";
    krbName += utils::Config().getDomain();
    data & d1 = values.New(ADD);
    d1.add("type", "krbName");
    d1.add("values", krbName);    
  }
  
  if(_group.changed()) {
    if(!_hasGroup) {
      data & d = values.New(ADD);
      d.add("type", TYPE_GID);
      d.add("values", _group()());
    } else {
      data & d = values.New(MODIFY);
      d.add("type", TYPE_GID);
      d.add("values", _group()());
    }
  }
  
  if(_wisaID.changed()) {
    if(!_hasWisaID) {
      data & d = values.New(ADD);
      d.add("type", TYPE_WISA_ID);
      d.add("values", std::to_string(_wisaID()()));
    } else {
      data & d = values.New(MODIFY);
      d.add("type", TYPE_WISA_ID);
      d.add("values", std::to_string(_wisaID()()));
    }
  }
  
  if(_mail.changed()) {
    if(!_hasMail) {
      data & d = values.New(ADD);
      d.add("type", TYPE_MAIL);
      d.add("values", _mail()());
    } else {
      data & d = values.New(MODIFY);
      d.add("type", TYPE_MAIL);
      d.add("values", _mail()());
    }
  }
  
  if(_birthDay.changed()) {
    if(!_hasBirthday) {
      data & d = values.New(ADD);
      d.add("type", TYPE_BIRTHDAY);
      d.add("values",std::to_string(_birthDay()()));
    } else {
      data & d = values.New(MODIFY);
      d.add("type", TYPE_BIRTHDAY);
      d.add("values", std::to_string(_birthDay()()));
    }
  }
  
  if(_cn.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_CN);
    d.add("values", _cn()());
  }
  
  if(_sn.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_SN);
    d.add("values", _sn()());
  }
  
  if(_fullName.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_FULL_NAME);
    d.add("values", _fullName()());
    
    // this value is also kept in 'gecos' for historical reasons
    data & d1 = values.New(MODIFY);
    d1.add("type", "gecos");
    d1.add("values", _fullName()());
  }
  
  if(_homeDir.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_HOMEDIR);
    d.add("values", _homeDir()());
  }
  
  if(_groupID.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_GID_NUMBER);
    d.add("values", std::to_string(_groupID()()));
  }
  
  if(_password.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_PASSWORD);
    d.add("values", _password()());
    samba::changePassword(_uid()(), _passwordClearText);
    y::Smartschool().saveUser(*this);
  }
  
  if(values.elms()) {
    Server().modify(_dn(), values);
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
  _passwordClearText = value();
  
  _password(PASSWORD(y::utils::sha1(_passwordClearText)));
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

std::string y::ldap::account::getPasswordText() {
  return _passwordClearText;
}
