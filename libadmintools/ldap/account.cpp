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
#include "utils/convert.h"
#include "smartschool/smartschool.h"

y::ldap::account::account() : 
  _uidNumber(UID_NUMBER(0)),
  _uid(UID(L"")),
  _dn(DN(L"")),
  _cn(L""),
  _sn(L""),
  _fullName(FULL_NAME(L"")),
  _homeDir(HOMEDIR(L"")),
  _wisaID(WISA_ID(0)),
  _mail(MAIL(L"")),
  _birthDay(DATE(DAY(1), MONTH(1), YEAR(1))),
  _password(PASSWORD(L"")),
  _group(GID(L"")),
  _groupID(GID_NUMBER(0)),
  _new(true),
  _hasKrbName(false),
  _hasGroup(false),
  _hasWisaID(false),
  _hasMail(false),
  _hasBirthday(false),
  _importStatus(WI_NOT_ACCOUNTED),
  _flaggedForRemoval(false)
  {}

bool y::ldap::account::load(const data& d) {
  if(d.getValue(TYPE_UID_NUMBER).size()) {
    try {
      _uidNumber(UID_NUMBER(std::stoi(d.getValue(TYPE_UID_NUMBER))), true);
    } catch(const std::invalid_argument &e) {
      std::wstring message(L"Invalid ldap::UID_NUMBER conversion: ");
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
  _cn       (d.getValue(TYPE_CN        ), true);
  _sn       (d.getValue(TYPE_SN        ), true);
  _fullName (FULL_NAME (          d.getValue(TYPE_FULL_NAME ) ), true);
  _homeDir  (HOMEDIR   (          d.getValue(TYPE_HOMEDIR   ) ), true);
  _mail     (MAIL      (          d.getValue(TYPE_MAIL      ) ), true);
  _password (PASSWORD  (          d.getValue(TYPE_PASSWORD  ) ), true); 
  _group    (GID       (          d.getValue(TYPE_GID       ) ), true);
  
  if(d.getValue(TYPE_GID_NUMBER).size()) {
    try {
      _groupID(GID_NUMBER(std::stoi(d.getValue(TYPE_GID_NUMBER))), true);
    } catch(const std::invalid_argument &e) {
      std::wstring message(L"Invalid ldap::GID_NUMBER conversion: ");
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
    _birthDay(DATE(L"0"));
  }
  
  if(d.getValue(TYPE_WISA_ID).size()) {
    try {
      _wisaID(WISA_ID(std::stoi(d.getValue(TYPE_WISA_ID))), true);
      _hasWisaID = true;
    } catch(const std::invalid_argument &e) {
      _wisaID(WISA_ID(0));
      _hasWisaID = true;
    }
  } else {
    _wisaID(WISA_ID(0));
  }

  if(d.getValue(L"krbName"   ).size()) _hasKrbName  = true;
  if(d.getValue(TYPE_GID     ).size()) _hasGroup    = true;
  if(d.getValue(TYPE_MAIL    ).size()) _hasMail     = true;
  _new = false;
  return !_new;
}

bool y::ldap::account::load(const UID & id) {
  dataset d;
  std::wstring filter(TYPE_UID);
  filter += L"="; filter.append(id());
  
  if(d.create(filter, L"ou=People")) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(UID_NUMBER id) {
  dataset d;
  std::wstring filter(TYPE_UID_NUMBER);
  filter += L"="; filter.append(std::to_wstring(id()));
  
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
  // remove user if needed
  if(flaggedForRemoval()) {
    y::Smartschool().deleteUser(*this);
    Server().remove(_dn());
    return true;
  }
  
  
  // else apply changes
  dataset values;
  
  // on first save, some new entries have to be added
  if(!_hasKrbName) {
    // add kerberos objectClass
    data & d = values.New(ADD);
    d.add(L"type", L"objectClass");
    d.add(L"values", L"kerberosSecurityObject");
    
    // add kerberos name (for short mail)
    std::wstring krbName(_uid()());
    krbName += L"@";
    krbName += utils::Config().getDomain();
    data & d1 = values.New(ADD);
    d1.add(L"type", L"krbName");
    d1.add(L"values", krbName);    
  }
  
  if(_group.changed()) {
    if(!_hasGroup) {
      data & d = values.New(ADD);
      d.add(L"type", TYPE_GID);
      d.add(L"values", _group()());
    } else {
      data & d = values.New(MODIFY);
      d.add(L"type", TYPE_GID);
      d.add(L"values", _group()());
    }
  }
  
  if(_wisaID.changed()) {
    if(!_hasWisaID) {
      data & d = values.New(ADD);
      d.add(L"type", TYPE_WISA_ID);
      d.add(L"values", std::to_wstring(_wisaID()()));
    } else {
      data & d = values.New(MODIFY);
      d.add(L"type", TYPE_WISA_ID);
      d.add(L"values", std::to_wstring(_wisaID()()));
    }
  }
  
  if(_mail.changed()) {
    if(!_hasMail) {
      data & d = values.New(ADD);
      d.add(L"type", TYPE_MAIL);
      d.add(L"values", _mail()());
    } else {
      data & d = values.New(MODIFY);
      d.add(L"type", TYPE_MAIL);
      d.add(L"values", _mail()());
    }
  }
  
  if(_birthDay.changed()) {
    if(!_hasBirthday) {
      data & d = values.New(ADD);
      d.add(L"type", TYPE_BIRTHDAY);
      d.add(L"values",std::to_wstring(_birthDay()()));
    } else {
      data & d = values.New(MODIFY);
      d.add(L"type", TYPE_BIRTHDAY);
      d.add(L"values", std::to_wstring(_birthDay()()));
    }
  }
  
  if(_cn.changed()) {
    data & d = values.New(MODIFY);
    d.add(L"type", TYPE_CN);
    d.add(L"values", _cn());
  }
  
  if(_sn.changed()) {
    data & d = values.New(MODIFY);
    d.add(L"type", TYPE_SN);
    d.add(L"values", _sn());
  }
  
  if(_fullName.changed()) {
    data & d = values.New(MODIFY);
    d.add(L"type", TYPE_FULL_NAME);
    d.add(L"values", _fullName()());
    
    // this value is also kept in 'gecos' for historical reasons
    //data & d1 = values.New(MODIFY);
    //d1.add(L"type", L"gecos");
    //d1.add(L"values", _fullName()());
  }
  
  if(_homeDir.changed()) {
    data & d = values.New(MODIFY);
    d.add(L"type", TYPE_HOMEDIR);
    d.add(L"values", _homeDir()());
  }
  
  if(_groupID.changed()) {
    data & d = values.New(MODIFY);
    d.add(L"type", TYPE_GID_NUMBER);
    d.add(L"values", std::to_wstring(_groupID()()));
  }
  
  if(_password.changed()) {
    data & d = values.New(MODIFY);
    d.add(L"type", TYPE_PASSWORD);
    d.add(L"values", _password()());
    
#ifndef DEBUG
    samba::changePassword(_uid()(), _passwordClearText);
#endif
    
    if(_group()().compare(L"extern") != 0 && _group()().compare(L"externmail") != 0) {
      if(values.elms() == 1) {
        // this means only the password has changed
        y::Smartschool().savePassword(*this);
        std::wstring message(L"Updating smartschool password for user ");
        message += _fullName()();
        y::utils::Log().add(message);
      }
    }
    
  }
  
  if(values.elms()) {
    Server().modify(_dn(), values);
    
    // check if more than just the password is changed
    if(_group()().compare(L"extern") != 0 && _group()().compare(L"externmail") != 0) {
      if(values.elms() > 1 || values.get(0).getValue(L"type").compare(TYPE_PASSWORD) != 0) {
        y::Smartschool().saveUser(*this);
        std::wstring message(L"Updating smartschool for user ");
        message += _fullName()();
        y::utils::Log().add(message);
        
        // add user to group
        if(this->_groupID()() == 1000) {
          // this is a student
          y::Smartschool().addUserToGroup(*this, str8(_group()()), false);
        } else  if(_group()().compare(L"personeel") == 0) {
          y::Smartschool().addUserToGroup(*this, "Leerkrachten", false);
        } else if (_group()().compare(L"directie") == 0) {
          y::Smartschool().addUserToGroup(*this, "Directie", false);
        }
      }
    }
    
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
  _uid(UID(L""));
  _dn(DN(L""));
  _cn(L"");
  _sn(L"");
  _fullName(FULL_NAME(L""));
  _homeDir(HOMEDIR(L""));
  _wisaID(WISA_ID(0));
  _mail(MAIL(L""));
  _password(PASSWORD(L""));
  _birthDay(DATE(DAY(1), MONTH(1), YEAR(1)));
  _group(GID(L""));
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

const std::wstring & y::ldap::account::cn() const {
  return _cn();
}

const std::wstring & y::ldap::account::sn() const {
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

y::ldap::account & y::ldap::account::cn(const std::wstring & value) {
  _cn(value);
  return *this;
}

y::ldap::account & y::ldap::account::sn(const std::wstring & value) {
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
  
  _password(PASSWORD(strW(y::utils::sha1(str8(_passwordClearText)))));
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

std::wstring y::ldap::account::getPasswordText() {
  return _passwordClearText;
}


y::ldap::WISA_IMPORT y::ldap::account::getImportStatus() {
  return _importStatus;
}

y::ldap::account & y::ldap::account::setImportStatus(WISA_IMPORT status) {
  _importStatus = status;
  return *this;
}

void y::ldap::account::convertToNewAccount() {
  std::cout << str8(_dn()()) << std::endl;
  if(_password()().length() == 0) {  
    std::cout << "is an old account" << std::endl;
  }
  std::cout << "will be converted" << std::endl;
  
  dataset values;
  
  {
    data & d = values.New(ADD);
    d.add(L"type", L"objectClass");
    d.add(L"values", L"schoolPerson");
  }
  
  std::wstring krbName(_uid()());
  krbName += L"@";
  krbName += utils::Config().getDomain();
  {
    data & d = values.New(ADD);
    d.add(L"type", L"mailAlias");
    d.add(L"values", krbName);
  }
  
  {
    data & d = values.New(ADD);
    d.add(L"type", L"gMailPassword");
    d.add(L"values", _password()());
  }
  
  
  
  {
    data & d = values.New(ADD);
    d.add(L"type", L"role");
    if(_group()().compare(L"extern") == 0) {
      d.add(L"values", L"extern");
    } else if (_group()().compare(L"externmail") == 0) {
      d.add(L"values", L"externmail");
    } else if (_group()().compare(L"personeel") == 0) {
      d.add(L"values", L"teacher");
    } else {
      d.add(L"values", L"student");
      {
        data & d = values.New(ADD);
        d.add(L"type", L"class");
        d.add(L"values", _group()());
      }
    }
  }
  
  if(_wisaID()() > 0){
    data & d = values.New(ADD);
    d.add(L"type", L"wisaID");
    d.add(L"values", std::to_wstring(_wisaID()()));
  }
  
  {
    data & d = values.New(ADD);
    d.add(L"type", L"birthday");
    d.add(L"values", std::to_wstring(_birthDay()()));
  }
  
  
  Server().modify(_dn(), values);
}