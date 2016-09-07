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
  // var          name in ldap          type and init    is int?      
  _uidNumber     (TYPE_UIDNUMBER      , UID_NUMBER (0 )),
  _uid           (TYPE_UID            , UID        ("")),
  _dn            ("DN"                , DN         ("")),
  _cn            (TYPE_CN             , CN         ("")),
  _sn            ("sn"                , SN         ("")),
  _fullName      ("displayName"       , FULL_NAME  ("")),
  _homeDir       ("homeDirectory"     , HOMEDIR    ("")),
  _wisaID        ("wisaID"            , WISA_ID    (0 )),
  _wisaName      (TYPE_WISANAME       , WISA_NAME  ("")),
  _mail          ("mail"              , MAIL       ("")),
  _mailAlias     ("mailAlias"         , MAIL_ALIAS ("")),
  _birthDay      ("birthday"          , DATE(DAY(1), MONTH(1), YEAR(1))),
  _password      ("gMailPassword"     , PASSWORD   ("")),
  _role          ("schoolRole"        , ROLE(ROLE::NONE)),
  _groupID       ("gidNumber"         , GID_NUMBER (0 )),
  _schoolClass   ("class"             , SCHOOLCLASS("")),
  _classChange   ("classChangeDate"   , DATE(DAY(1), MONTH(1), YEAR(1))),
  _birthPlace    ("placeOfBirth"      , BIRTHPLACE ("")),
  _gender        ("gender"            , GENDER(GENDER::MALE) ),
  _adminGroup    ("adminGroupID"      , ADMINGROUP (0 )),
  _registerID    ("nationalRegisterID", REGISTER_ID("")),
  _nationality   ("nationality"       , NATION     ("")),
  _stemID        ("stemID"            , STEM_ID    (0 )),
  _schoolID      ("schoolID"          , SCHOOL_ID  (0 )),   
  _houseNumber   ("houseNumber"       , HOUSENUMBER(0 )),
  _houseNumberAdd("houseNumberAdd"    , HOUSENUMBER_ADD("")  ),
  _city          ("location"          , CITY       ("")),
  _postalCode    ("postalCode"        , POSTAL_CODE("")),
  _street        ("street"            , STREET     ("")),
  _country       ("co"                , COUNTRY    ("")),

  _new(true),
  _hasKrbName(false),
  _hasSchoolPersonClass(false),
  _importStatus(WI_NOT_ACCOUNTED),
  _flaggedForRemoval(false)
  {}

bool y::ldap::account::load(const data& d) {
  _uidNumber.readFromLdap(d);
  if(_uidNumber().get() == 0) {
    return false;
  }
  
  for(int i = 0; i < d.elms("objectClass"); i++) {
    if(d.getValue("objectClass", i) == "schoolPerson") {
      _hasSchoolPersonClass = true;
      break;
    } 
  }
  
  _uid           .readFromLdap(d);
  _dn            .readFromLdap(d);
  _cn            .readFromLdap(d);
  _sn            .readFromLdap(d);
  _fullName      .readFromLdap(d);
  _homeDir       .readFromLdap(d);
  _wisaID        .readFromLdap(d);
  _wisaName      .readFromLdap(d);
  _mail          .readFromLdap(d);
  _mailAlias     .readFromLdap(d);
  _birthDay      .readFromLdap(d);
  _password      .readFromLdap(d);
  _role          .readFromLdap(d);
  _groupID       .readFromLdap(d);
  _schoolClass   .readFromLdap(d);
  _classChange   .readFromLdap(d);
  _birthPlace    .readFromLdap(d);
  _gender        .readFromLdap(d);
  _adminGroup    .readFromLdap(d);
  _registerID    .readFromLdap(d);
  _nationality   .readFromLdap(d);
  _stemID        .readFromLdap(d);
  _schoolID      .readFromLdap(d);
  _houseNumber   .readFromLdap(d);
  _houseNumberAdd.readFromLdap(d);
  _city          .readFromLdap(d);
  _postalCode    .readFromLdap(d);
  _street        .readFromLdap(d);
  _country       .readFromLdap(d);
  
  if(_role().get() == ROLE::NONE) {
    y::utils::Log().add("a user exists without a valid schoolrole: ");
    y::utils::Log().add(_dn().get());
  }
  if(d.getValue("krbName" ).size()) _hasKrbName  = true;

  TODO(this can be removed later)
  if(_fullName().get() == "System User") {
    string fn = _cn().get();
    fn += " ";
    fn += _sn().get();
    _fullName(FULL_NAME(fn), false);
  }

  _new = false;
  return !_new;
}

bool y::ldap::account::load(const UID & id) {
  dataset d(server);
  string filter(TYPE_UID);
  filter += "=" + id.get();
  
  if(d.create(filter, "ou=People")) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(const UID_NUMBER & id) {
  dataset d(server);
  string filter(TYPE_UIDNUMBER);
  filter += "=" + string(id.get());
  
  if(d.create(filter)) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(const DN & id) {
  dataset d(server);  
  if(d.createFromDN(id.get())) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::load(const WISA_NAME & id) {
  dataset d(server);
  string filter(TYPE_WISANAME);
  filter += "=" + string(id.get());
  
  if(d.create(filter)) {
    load(d.get(0));
  }
  
  return !_new;
}

bool y::ldap::account::save() {
  
  // remove user if needed
  if(flaggedForRemoval() && !dn().get().empty()) {
    if(isStudent()) {
      y::Smartschool().unregisterStudent(*this);
    } else {
      y::Smartschool().deleteUser(*this);
    }    
    y::samba::delUser(*this);
    
    if(isStudent())
    
    return true;
  }
  
  // accounts without DN are not valid
  if(dn().get().empty()) {
    flagForRemoval();
    return false; 
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
    string krbName(_uid().get());
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
  
  _cn.saveToLdap(values);
  _sn.saveToLdap(values);
  _fullName.saveToLdap(values);
  _homeDir.saveToLdap(values);
  _wisaID.saveToLdap(values);
  _wisaName.saveToLdap(values);
  _mail.saveToLdap(values);
  _mailAlias.saveToLdap(values);
  _birthDay.saveToLdap(values);
  _role.saveToLdap(values);
  _groupID.saveToLdap(values);
  _schoolClass.saveToLdap(values);
  _classChange.saveToLdap(values);
  _birthPlace.saveToLdap(values);
  _gender.saveToLdap(values);
  _adminGroup.saveToLdap(values);
  _registerID.saveToLdap(values);
  _nationality.saveToLdap(values);
  _stemID.saveToLdap(values);
  _schoolID.saveToLdap(values);
  _houseNumber.saveToLdap(values);
  _houseNumberAdd.saveToLdap(values);
  _city.saveToLdap(values);
  _postalCode.saveToLdap(values);
  _street.saveToLdap(values);
  _country.saveToLdap(values);
  
  if(_password.changed()) {
    _password.saveToLdap(values);
    
#ifndef DEBUG
    samba::changePassword(_uid().get(), _passwordClearText);
#endif
      
  }
  
  if(values.elms()) {
    bool roleChanged = _role.changed();
    bool classChanged = _schoolClass.changed();
    
    server->modify(_dn(), values);
    
    if(isStaff() || isStudent()) {
      y::Smartschool().saveUser(*this);
      string message("Updating smartschool for user ");
      message += _fullName().get();
      y::utils::Log().add(message);

      // add user to group
      if(isStudent() && classChanged) {
        // this is a student
        y::Smartschool().moveUserToClass(*this, _schoolClass().get());
      } else  if(roleChanged && _role().get() == ROLE::DIRECTOR) {
        y::Smartschool().addUserToGroup(*this, "Directie", false);
      } else if (roleChanged && _role().get() == ROLE::SUPPORT) {
        y::Smartschool().addUserToGroup(*this, "Secretariaat", false);
      } else if (roleChanged && isStaff()) {
        y::Smartschool().addUserToGroup(*this, "Leerkrachten", true);
      }   
    }   
    return true;
  }
  
  if(!_ssPassword.empty()) {
    y::Smartschool().savePassword(*this);
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
  _hasSchoolPersonClass = false;
  _uidNumber     .reset(UID_NUMBER (0 ));
  _uid           .reset(UID        (""));
  _dn            .reset(DN         (""));
  _cn            .reset(CN         (""));
  _sn            .reset(SN         (""));
  _fullName      .reset(FULL_NAME  (""));
  _homeDir       .reset(HOMEDIR    (""));
  _wisaID        .reset(WISA_ID    (0 ));
  _wisaName      .reset(WISA_NAME  (""));
  _mail          .reset(MAIL       (""));
  _mailAlias     .reset(MAIL_ALIAS (""));
  _birthDay      .reset(DATE(DAY(1), MONTH(1), YEAR(1)));
  _password      .reset(PASSWORD   (""));
  _role          .reset(ROLE(ROLE::NONE));
  _groupID       .reset(GID_NUMBER (0 ));
  _schoolClass   .reset(SCHOOLCLASS(""));
  _birthPlace    .reset(BIRTHPLACE (""));
  _gender        .reset(GENDER(GENDER::MALE));
  _adminGroup    .reset(ADMINGROUP (0 ));
  _registerID    .reset(REGISTER_ID(""));
  _nationality   .reset(NATION     (""));
  _stemID        .reset(STEM_ID    (0 ));
  _schoolID      .reset(SCHOOL_ID  (0 ));
  _street        .reset(STREET     (""));  
  _houseNumber   .reset(HOUSENUMBER(0 ));
  _houseNumberAdd.reset(HOUSENUMBER_ADD(""));
  _city          .reset(CITY       (""));
  _postalCode    .reset(POSTAL_CODE(""));
  _country       .reset(COUNTRY    (""));
  _flaggedForRemoval = false;
}

const UID_NUMBER & y::ldap::account::uidNumber() const {
  return _uidNumber();
}

const UID & y::ldap::account::uid() const {
  return _uid();
}

const DN & y::ldap::account::dn() const {
  return _dn();
}

const CN & y::ldap::account::cn() const {
  return _cn();
}

const SN & y::ldap::account::sn() const {
  return _sn();
}

const FULL_NAME & y::ldap::account::fullName() const {
  return _fullName();
}

const HOMEDIR & y::ldap::account::homeDir() const {
  return _homeDir();
}

const WISA_ID & y::ldap::account::wisaID() const {
  return _wisaID();
}

const WISA_NAME & y::ldap::account::wisaName() const {
  return _wisaName();
}

const MAIL & y::ldap::account::mail() const {
  return _mail();
}

const DATE & y::ldap::account::birthDay() const {
  return _birthDay();
}

const PASSWORD & y::ldap::account::password() const {
  return _password();
}

const ROLE & y::ldap::account::role() const {
  return _role();
}

const GID_NUMBER & y::ldap::account::groupID() const {
  return _groupID();
}

const MAIL_ALIAS & y::ldap::account::mailAlias() const {
  return _mailAlias();
}

const SCHOOLCLASS & y::ldap::account::schoolClass() const {
  return _schoolClass();
}

const DATE & y::ldap::account::classChange() const {
  return _classChange();
}

const BIRTHPLACE & y::ldap::account::birthPlace() const {
  return _birthPlace();
}

const GENDER & y::ldap::account::gender() const {
  return _gender();
}

const ADMINGROUP & y::ldap::account::adminGroup() const {
  return _adminGroup();
}

const REGISTER_ID & y::ldap::account::registerID() const {
  return _registerID();
}

const NATION & y::ldap::account::nationality() const {
  return _nationality();
}

const STEM_ID & y::ldap::account::stemID() const {
  return _stemID();
}

const SCHOOL_ID & y::ldap::account::schoolID() const {
  return _schoolID();
}

const HOUSENUMBER & y::ldap::account::houseNumber() const {
  return _houseNumber();
}

const HOUSENUMBER_ADD & y::ldap::account::houseNumberAdd() const {
  return _houseNumberAdd();
}

const CITY & y::ldap::account::city() const {
  return _city();
}

const POSTAL_CODE & y::ldap::account::postalCode() const {
  return _postalCode();
}

const STREET & y::ldap::account::street() const {
  return _street();
}

const COUNTRY & y::ldap::account::country() const {
  return _country();
}

y::ldap::account & y::ldap::account::uidNumber(const UID_NUMBER& value) {
  _uidNumber(value);
  return *this;
}

y::ldap::account & y::ldap::account::uid(const UID& value) {
  _uid(value);
  return *this;
}

y::ldap::account & y::ldap::account::cn(const CN & value) {
  _cn(value);
  return *this;
}

y::ldap::account & y::ldap::account::sn(const SN & value) {
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

y::ldap::account & y::ldap::account::wisaName(const WISA_NAME & value) {
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
  _passwordClearText = value.get();
  
  _password(PASSWORD(string(y::utils::sha1(_passwordClearText.utf8()))));
  return *this;
}

y::ldap::account & y::ldap::account::role(const ROLE& value) {
  _role(value);
  return *this;
}

y::ldap::account & y::ldap::account::groupID(const GID_NUMBER& value) {
  _groupID(value);
  return *this;
}

y::ldap::account & y::ldap::account::mailAlias(const MAIL_ALIAS & value) {
  _mailAlias(value);
  return *this;
}

y::ldap::account & y::ldap::account::schoolClass(const SCHOOLCLASS & value) {
  server->getClass(CN(_schoolClass().get())).removeStudent(_dn());
  _schoolClass(value);
  server->getClass(CN(_schoolClass().get())).addStudent(_dn());
  return *this;
}

y::ldap::account & y::ldap::account::classChange(const DATE & value) {
  _classChange(value);
  return *this;
}

y::ldap::account & y::ldap::account::birthPlace(const BIRTHPLACE & value) {
  _birthPlace(value);
  return *this;
}

y::ldap::account & y::ldap::account::gender(const GENDER & value) {
  _gender(value);
  return *this;
}

y::ldap::account & y::ldap::account::adminGroup(const ADMINGROUP & value) {
  _adminGroup(value);
  return *this;
}

y::ldap::account & y::ldap::account::registerID(const REGISTER_ID & value) {
  _registerID(value);
  return *this;
}

y::ldap::account & y::ldap::account::nationality(const NATION & value) {
  _nationality(value);
  return *this;
}

y::ldap::account & y::ldap::account::stemID(const STEM_ID & value) {
  _stemID(value);
  return *this;
}

y::ldap::account & y::ldap::account::schoolID(const SCHOOL_ID & value) {
  _schoolID(value);
  return *this;
}

y::ldap::account & y::ldap::account::houseNumber(const HOUSENUMBER & value) {
  _houseNumber(value);
  return *this;
}

y::ldap::account & y::ldap::account::houseNumberAdd(const HOUSENUMBER_ADD & value) {
  _houseNumberAdd(value);
  return *this;
}

y::ldap::account & y::ldap::account::city(const CITY & value) {
  _city(value);
  return *this;
}

y::ldap::account & y::ldap::account::postalCode(const POSTAL_CODE & value) {
  _postalCode(value);
  return *this;
}

y::ldap::account & y::ldap::account::street(const STREET & value) {
  _street(value);
  return *this;
}

y::ldap::account & y::ldap::account::country(const COUNTRY & value) {
  _country(value);
  return *this;
}

string y::ldap::account::getPasswordText() const {
  return _passwordClearText;
}


WISA_IMPORT y::ldap::account::getImportStatus() {
  return _importStatus;
}

const string & y::ldap::account::ssPassword() const {
  return _ssPassword;
}

y::ldap::account & y::ldap::account::ssPassword(const string & value) {
  _ssPassword = value;
  return *this;
}

y::ldap::account & y::ldap::account::setImportStatus(WISA_IMPORT status) {
  _importStatus = status;
  return *this;
}

bool y::ldap::account::isStaff() const {
  if(_role().get() == ROLE::TEACHER ) return true;
  if(_role().get() == ROLE::ADMIN   ) return true;
  if(_role().get() == ROLE::DIRECTOR) return true;
  if(_role().get() == ROLE::SUPPORT ) return true;
  return false;
}

bool y::ldap::account::isStudent() const {
  if(_role().get() == ROLE::STUDENT) return true;
  return false;
}
