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

TODO(base account on ldapObject)

y::ldap::account::account(y::ldap::server * server) :
  server(server),
  _uidNumber(UID_NUMBER(0)),
  _uid(UID("")),
  _dn(DN("")),
  _cn(""),
  _sn(""),
  _fullName(FULL_NAME("")),
  _homeDir(HOMEDIR("")),
  _wisaID(WISA_ID(0)),
  _wisaName(""),
  _mail(MAIL("")),
  _birthDay(DATE(DAY(1), MONTH(1), YEAR(1))),
  _password(PASSWORD("")),
  _group(GID(y::ldap::ROLE_NONE)),
  _groupID(GID_NUMBER(0)),
  _new(true),
  _hasKrbName(false),
  _hasGroup(false),
  _hasWisaID(false),
  _hasWisaName(false),
  _hasMail(false),
  _hasBirthday(false),
  _hasSchoolPersonClass(false),
  _importStatus(WI_NOT_ACCOUNTED),
  _flaggedForRemoval(false)
  {}

bool y::ldap::account::load(const data& d) {
  if(!d.getValue(TYPE_UID_NUMBER).empty()) {
    try {
      _uidNumber(UID_NUMBER(d.getValue(TYPE_UID_NUMBER).asInt()), true);
    } catch(const std::invalid_argument &e) {
      string message("Invalid ldap::UID_NUMBER conversion: ");
      message += d.getValue(TYPE_UID_NUMBER);
      utils::Log().add(message);
      return false;
    }
  } else {
    _uidNumber(UID_NUMBER(0));
    //assert(false);
  }
  
  for(int i = 0; i < d.elms("objectClass"); i++) {
    if(d.getValue("objectClass", i) == "schoolPerson") {
      _hasSchoolPersonClass = true;
      break;
    } 
  }
  
  _uid      (UID       (          d.getValue(TYPE_UID       ) ), true);
  _dn       (DN        (          d.getValue(TYPE_DN        ) ), true);
  _cn       (d.getValue(TYPE_CN        ), true);
  _sn       (d.getValue(TYPE_SN        ), true);
  _fullName (FULL_NAME (          d.getValue(TYPE_FULL_NAME ) ), true);
  _homeDir  (HOMEDIR   (          d.getValue(TYPE_HOMEDIR   ) ), true);
  _mail     (MAIL      (          d.getValue(TYPE_MAIL      ) ), true);
  _password (PASSWORD  (          d.getValue(TYPE_PASSWORD  ) ), true);
  string role = d.getValue(TYPE_GID);
  if(role == SchoolRoleText(ROLE_TEACHER)) {
    _group(GID(ROLE_TEACHER), true);
  } else if(role == SchoolRoleText(ROLE_STUDENT)) {
    _group(GID(ROLE_STUDENT), true);
  } else if(role == SchoolRoleText(ROLE_DIRECTOR)) {
    _group(GID(ROLE_DIRECTOR), true);
  } else if(role == SchoolRoleText(ROLE_ADMIN)) {
    _group(GID(ROLE_ADMIN), true);
  } else if(role == SchoolRoleText(ROLE_SUPPORT)) {
    _group(GID(ROLE_SUPPORT), true);
  } else if(role == SchoolRoleText(ROLE_EXTERN)) {
    _group(GID(ROLE_EXTERN), true);
  } else if(role == SchoolRoleText(ROLE_EXTERN_WITH_MAIL)) {
    _group(GID(ROLE_EXTERN_WITH_MAIL), true);
  } else {
    _group(GID(ROLE_NONE), true);
    y::utils::Log().add("a user exists without a valid schoolrole");
  }
  
  if(d.getValue(TYPE_WISA_NAME).size()) {
    _wisaName (d.getValue(TYPE_WISA_NAME), true);
    _hasWisaName = true;
  }
  
  if(d.getValue(TYPE_GID_NUMBER).size()) {
    try {
      _groupID(GID_NUMBER(d.getValue(TYPE_GID_NUMBER).asInt()), true);
    } catch(const std::invalid_argument &e) {
      string message("Invalid ldap::GID_NUMBER conversion: ");
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
      _wisaID(WISA_ID(d.getValue(TYPE_WISA_ID).asInt()), true);
      _hasWisaID = true;
    } catch(const std::invalid_argument &e) {
      _wisaID(WISA_ID(0));
      _hasWisaID = true;
    }
  } else {
    _wisaID(WISA_ID(0));
  }
  
  
  
  if(_fullName()() == "System User") {
    string fn = _cn();
    fn += " ";
    fn += _sn();
    _fullName(FULL_NAME(fn), false);
  }

  if(d.getValue("krbName" ).size()) _hasKrbName  = true;
  if(d.getValue(TYPE_GID  ).size()) _hasGroup    = true;
  if(d.getValue(TYPE_MAIL ).size()) _hasMail     = true;
  _new = false;
  return !_new;
}

bool y::ldap::account::load(const UID & id) {
  dataset d(server);
  string filter(TYPE_UID);
  filter += "=" + id();
  
  if(d.create(filter, "ou=People")) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(UID_NUMBER id) {
  dataset d(server);
  string filter(TYPE_UID_NUMBER);
  filter += "=" + string(id());
  
  if(d.create(filter)) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(const DN & id) {
  dataset d(server);  
  if(d.createFromDN(id())) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::save() {
  // remove user if needed
  if(flaggedForRemoval()) {
    y::Smartschool().deleteUser(*this);
    server->remove(_dn());
    return true;
  }
  
  
  // else apply changes
  dataset values(server);
  
  // on first save, some new entries have to be added
  if(!_hasKrbName) {
    // add kerberos objectClass
    data & d = values.New(ADD);
    d.add("type", "objectClass");
    d.add("values", "kerberosSecurityObject");
    
    // add kerberos name (for short mail)
    string krbName(_uid()());
    krbName += "@";
    krbName += utils::Config().getDomain();
    data & d1 = values.New(ADD);
    d1.add("type", "krbName");
    d1.add("values", krbName);
    _hasKrbName = true;
  }
  
  if(!_hasSchoolPersonClass) {
    data & d = values.New(ADD);
    d.add("type", "objectClass");
    d.add("values", "schoolPerson");
    _hasSchoolPersonClass = true;
  }
  
  if(_group.changed()) {
    if(!_hasGroup) {
      data & d = values.New(ADD);
      d.add("type", TYPE_GID);
      d.add("values", SchoolRoleText(_group()()));
    } else {
      data & d = values.New(MODIFY);
      d.add("type", TYPE_GID);
      d.add("values", SchoolRoleText(_group()()));
    }
    _group.unFlag();
  }
  
  if(_wisaID.changed()) {
    if(!_hasWisaID) {
      data & d = values.New(ADD);
      d.add("type", TYPE_WISA_ID);
      d.add("values", string(_wisaID()()));
    } else {
      data & d = values.New(MODIFY);
      d.add("type", TYPE_WISA_ID);
      d.add("values", string(_wisaID()()));
    }
    _wisaID.unFlag();
  }
  
  if(_wisaName.changed() && !_wisaName().empty()) {
    if(!_hasWisaName) {
      data & d = values.New(ADD);
      d.add("type", TYPE_WISA_NAME);
      d.add("values", _wisaName());
    } else {
      data & d = values.New(MODIFY);
      d.add("type", TYPE_WISA_NAME);
      d.add("values", _wisaName());
    }
    _wisaName.unFlag();
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
    _mail.unFlag();
  }
  
  if(_birthDay.changed()) {
    if(!_hasBirthday) {
      data & d = values.New(ADD);
      d.add("type", TYPE_BIRTHDAY);
      d.add("values", string(_birthDay()()));
      
    } else {
      data & d = values.New(MODIFY);
      d.add("type", TYPE_BIRTHDAY);
      d.add("values", string(_birthDay()()));
    }
    _birthDay.unFlag();
  }
  
  if(_cn.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_CN);
    d.add("values", _cn());
    _cn.unFlag();
  }
  
  if(_sn.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_SN);
    d.add("values", _sn());
    _sn.unFlag();
  }
  
  if(_fullName.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_FULL_NAME);
    d.add("values", _fullName()());
    _fullName.unFlag();
  }
  
  if(_homeDir.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_HOMEDIR);
    d.add("values", _homeDir()());
    _homeDir.unFlag();
  }
  
  if(_groupID.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_GID_NUMBER);
    d.add("values", string(_groupID()()));
    _groupID.unFlag();
  }
  
  if(_password.changed()) {
    data & d = values.New(MODIFY);
    d.add("type", TYPE_PASSWORD);
    d.add("values", _password()());
    _password.unFlag();
    
#ifndef DEBUG
    samba::changePassword(_uid()(), _passwordClearText);
#endif
    
    if(isStaff() || isStudent()) {
      if(values.elms() == 1) {
        // this means only the password has changed
        y::Smartschool().savePassword(*this);
        string message("Updating smartschool password for user ");
        message += _fullName()();
        y::utils::Log().add(message);
      }
    }
    
  }
  
  if(values.elms()) {
    server->modify(_dn(), values);
    
    // check if more than just the password is changed
    if(isStaff() || isStudent()) {
      if(values.elms() > 1 || values.get(0).getValue("type") != TYPE_PASSWORD) {
        y::Smartschool().saveUser(*this);
        string message("Updating smartschool for user ");
        message += _fullName()();
        y::utils::Log().add(message);
        
        // add user to group
        if(isStudent()) {
          // this is a student
          y::Smartschool().addUserToGroup(*this, _schoolClass(), false);
        } else  if(_group()() == ROLE_DIRECTOR) {
          y::Smartschool().addUserToGroup(*this, "Directie", false);
        } else if (_group()() == ROLE_SUPPORT) {
          y::Smartschool().addUserToGroup(*this, "Secretariaat", false);
        } else if (isStaff()) {
          y::Smartschool().addUserToGroup(*this, "Leerkrachten", false);
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
  _hasKrbName = false;
  _hasGroup = false;
  _hasWisaID = false;
  _hasWisaName = false;
  _hasMail = false;
  _hasBirthday = false;
  _hasSchoolPersonClass = false;
  _uidNumber(UID_NUMBER(0));
  _uid(UID(""));
  _dn(DN(""));
  _cn("");
  _sn("");
  _fullName(FULL_NAME(""));
  _homeDir(HOMEDIR(""));
  _wisaID(WISA_ID(0));
  _wisaName("");
  _mail(MAIL(""));
  _password(PASSWORD(""));
  _birthDay(DATE(DAY(1), MONTH(1), YEAR(1)));
  _group(GID(ROLE_NONE));
  _groupID(GID_NUMBER(0));
  _flaggedForRemoval = false;
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

const string & y::ldap::account::cn() const {
  return _cn();
}

const string & y::ldap::account::sn() const {
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

const string & y::ldap::account::wisaName() const {
  return _wisaName();
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

y::ldap::account & y::ldap::account::cn(const string & value) {
  _cn(value);
  return *this;
}

y::ldap::account & y::ldap::account::sn(const string & value) {
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

y::ldap::account & y::ldap::account::wisaName(const string & value) {
  _wisaName(value);
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
  
  _password(PASSWORD(string(y::utils::sha1(_passwordClearText.utf8()))));
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

string y::ldap::account::getPasswordText() {
  return _passwordClearText;
}


y::ldap::WISA_IMPORT y::ldap::account::getImportStatus() {
  return _importStatus;
}

y::ldap::account & y::ldap::account::setImportStatus(WISA_IMPORT status) {
  _importStatus = status;
  return *this;
}

bool y::ldap::account::isStaff() const {
  if(_group()() == ROLE_TEACHER ) return true;
  if(_group()() == ROLE_ADMIN   ) return true;
  if(_group()() == ROLE_DIRECTOR) return true;
  if(_group()() == ROLE_SUPPORT ) return true;
  return false;
}

bool y::ldap::account::isStudent() const {
  if(_group()() == ROLE_STUDENT) return true;
  return false;
}

const string & y::ldap::account::schoolClass() const {
  return _schoolClass();
}

y::ldap::account & y::ldap::account::schoolClass(const string& value) {
  _schoolClass(value);
  return *this;
}