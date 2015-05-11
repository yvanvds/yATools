/* 
 * File:   group.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 10:01 AM
 */

#include "group.h"
#include "dataset.h"
#include "utils/config.h"
#include "server.h"
#include "smartschool/smartschool.h"
#include <assert.h>

y::ldap::group::group() 
  : _dn(DN(L"")), 
    _cn(CN(L"")), 
    _new(true), 
    _editable(true),
    _flaggedForCommit(false),
    _importStatus(WI_NOT_ACCOUNTED),
    _flaggedForRemoval(false){
}

bool y::ldap::group::load(const DN& id) {
  dataset d;
  if(d.createFromDN(id())) {
    load(d.get(0));
  } 
  return !_new;
}

bool y::ldap::group::load(const CN& id) {
  dataset d;
  std::wstring filter;
  filter = L"cn="; filter.append(id().c_str());
  
  if(!editable() && d.create(filter, L"ou=mailGroups")) {
    load(d.get(0));
  } else if(editable() && d.create(filter, L"ou=editableMailGroups")) {
    load(d.get(0));
  } else {
    _cn(id);
  }
  
  return !_new;
}

bool y::ldap::group::load(const data& d) {
  _dn(DN(d.getValue(L"DN")), true);
  _cn(CN(d.getValue(L"cn")), true);
  
  if(d.elms(L"owner")) {
    _editable = false;
    for(int i = 0; i < d.elms(L"owner"); i++) {
      std::wstring & owner = _owners.New();
      owner = d.getValue(L"owner", i);
      _ownersInLDAP.New() = owner;
    }
    for(int i = 0; i < d.elms(L"member"); i++) {
      std::wstring & member = _members.New();
      member = d.getValue(L"member", i);
      _membersInLDAP.New() = member;
    }
    
  } else {
    _editable = true;
    for(int i = 0; i < d.elms(L"mail"); i++) {
      std::wstring & owner = _owners.New();
      owner = d.getValue(L"mail", i);
      _ownersInLDAP.New() = owner;
    }
    for(int i = 0; i < d.elms(L"rfc822MailMember"); i++) {
      std::wstring & member = _members.New();
      member = d.getValue(L"rfc822MailMember", i);
      _membersInLDAP.New() = member;
    }
  }
  _new = false;
  return !_new;
}

void y::ldap::group::flagForCommit() {
  _flaggedForCommit = true;
}

const y::ldap::DN & y::ldap::group::dn() const {
  return _dn();
}

const y::ldap::CN & y::ldap::group::cn() const {
  return _cn();
}

container<std::wstring> & y::ldap::group::owners() {
  return _owners;
}

container<std::wstring> & y::ldap::group::members() {
  return _members;
}

y::ldap::group & y::ldap::group::editable(bool value) {
  // make sure this is only used with new groups
  assert(_new);
  _editable = value;
  return (*this);
}

bool y::ldap::group::editable() {
  return _editable;
}

bool y::ldap::group::isNew() {
  return _new;
}

void y::ldap::group::flagForRemoval() {
  _flaggedForCommit = true; // delete is also a commit
  _flaggedForRemoval = true;
}

bool y::ldap::group::removeOwner(const std::wstring& owner) {
  for(int i = 0; i < _owners.elms(); i++) {
    if(_owners[i].compare(owner) == 0) {
      _owners.remove(i);
      _flaggedForCommit = true;
      return true;
    }
  }
  return false;
}

bool y::ldap::group::removeMember(const std::wstring& member) {
  for (int i = 0; i < _members.elms(); i++) {
    if(_members[i].compare(member) == 0) {
      _members.remove(i);
      _flaggedForCommit = true;
      return true;
    }
  }
  return false;
}

bool y::ldap::group::addOwner(const std::wstring& owner) {
  for(int i = 0; i < _owners.elms(); i++) {
    if(_owners[i].compare(owner) == 0) {
      // already in group
      return false;
    }
  }
  _owners.New() = owner;
  _flaggedForCommit = true;
  return true;
}

bool y::ldap::group::addMember(const std::wstring& member) {
  for(int i = 0; i < _members.elms(); i++) {
    if(_members[i].compare(member) == 0) {
      // already in group
      return false;
    }
  }
  _members.New() = member;
  _flaggedForCommit = true;
  return true;
}

bool y::ldap::group::flaggedForRemoval() {
  return _flaggedForRemoval;
}

bool y::ldap::group::save() {
  if(!_flaggedForCommit) return false;
  
  if(_flaggedForRemoval) {
    // remove from smartschool if this is a class group
    if(!editable()) {
      y::Smartschool().deleteClass(*this);
    }
    
    Server().remove(_dn());
    // not really needed, but you never know
    _members.clear();
    _owners.clear();
    
    return true;
  }
  
  dataset values;
  
  // update or add smartschool class if needed
  if(!editable()) {
    y::Smartschool().addClass(*this);
  }
  
  if(_new) {    
    if(saveNew()) {
      _new = false;
      return true;
    } else return false;
  } else {
    return saveUpdate();
  }
  
  
}

bool y::ldap::group::saveNew() {
  dataset values;
  // don't create if there are no members
  if(_members.elms() == 0) {
    if(!_editable) {
      _members.New() = L"uid=gast,ou=People,dc=sanctamaria-aarschot,dc=be";
    } else {
      _members.New() = L"dummy@sanctamaria-aarschot.be";
    }
  }

  // add owner if not present
  if(!_owners.elms()) {
    // TODO generalize this
    if(!_editable) {
      _owners.New() = L"uid=inge,ou=personeel,ou=People,dc=sanctamaria-aarschot,dc=be";
    } else {
      _owners.New() = L"directie@sanctamaria-aarschot.be";
    }
  } 

  // create group first
  std::wstring dn;
  dn = L"cn="; dn += _cn()();
  if(_editable) {
    dn += L",ou=editableMailGroups,";
  } else {
    dn += L",ou=mailGroups,";
  }
  dn += utils::Config().getLdapBaseDN();
  _dn(DN(dn), true);

  data & d = values.New(NEW);
  d.add(L"type", L"objectClass");
  d.add(L"values", L"top");
  d.add(L"values", L"extensibleObject");
  if(_editable) {
    d.add(L"values", L"nisMailAlias");
  } else {
    d.add(L"values", L"groupOfNames");
  }
  
  data & cn = values.New(NEW);
  cn.add(L"type", L"cn");
  cn.add(L"values", _cn()());

  data & own = values.New(NEW);
  if(_editable) {
    own.add(L"type", L"mail");
  } else {
    own.add(L"type", L"owner");
  }
  for(int i = 0; i < _owners.elms(); i++) {
    own.add(L"values", _owners[i]);
  }
  
  // if editable, also add as member
  data & mbs = values.New(NEW);
  if(_editable) {
    mbs.add(L"type", L"rfc822MailMember");
    for(int i = 0; i < _owners.elms(); i++) {
      mbs.add(L"values", _owners[i]);
    }
  } else {
    mbs.add(L"type", L"member");
  }
  
  for(int i = 0; i < _members.elms(); i++) {
    mbs.add(L"values", _members[i]);
  }

  if(values.elms()) {
    Server().add(_dn(), values);
    return true;
  }
  return false;
}

bool y::ldap::group::saveUpdate() {
  // TODO in editable mailgroups owners should also be members
  
  dataset values;
  data * ownerDelete = nullptr;
  // remove owners if needed 
  for(int i = 0; i < _ownersInLDAP.elms(); i++){
    std::wstring owner = _ownersInLDAP[i];
    bool found = false;
    for(int j = 0; j < _owners.elms(); j++) {
      if(owner.compare(_owners[j]) == 0) found = true;
    }
    if(!found) {
      if(!ownerDelete) {
        ownerDelete = &values.New(DELETE);
        if(_editable) {
          ownerDelete->add(L"type", L"mail");
        } else {
          ownerDelete->add(L"type", L"owner");
        }
      }
      ownerDelete->add(L"values", owner);     
    }
  }
  
  // remove members if needed
  data * memberDelete = nullptr;
  for(int i = 0; i < _membersInLDAP.elms(); i++){
    std::wstring member = _membersInLDAP[i];
    bool found = false;
    for(int j = 0; j < _members.elms(); j++) {
      if(member.compare(L"uid=gast,ou=People,dc=sanctamaria-aarschot,dc=be") == 0 && _members.elms() > 1) {
        found = false;
      } else if(member.compare(L"dummy@sanctamaria-aarschot.be") == 0 && _members.elms() > 1) {
        found = false;
      } else if(member.compare(_members[j]) == 0) found = true;
    }
    if(!found) {
      if(!memberDelete) {
        memberDelete = &values.New(DELETE);
        if(_editable) {
          memberDelete->add(L"type", L"rfc822MailMember");
        } else {
          memberDelete->add(L"type", L"member");
        }
      }
      memberDelete->add(L"values", member);     
    }
  }
  
  // add owners if needed
  data * ownerAdd = nullptr;
  for(int i = 0; i < _owners.elms(); i++){
    std::wstring owner = _owners[i];
    bool found = false;
    for(int j = 0; j < _ownersInLDAP.elms(); j++) {
      if(owner.compare(_ownersInLDAP[j]) == 0) found = true;
    }
    if(!found) {
      if(!ownerAdd) {
        ownerAdd = &values.New(ADD);
        if(_editable) {
          ownerAdd->add(L"type", L"mail");
        } else {
          ownerAdd->add(L"type", L"owner");
        }
      }
      ownerAdd->add(L"values", owner);     
    }
  }  
  
  // add members if needed
  data * memberAdd = nullptr;
  for(int i = 0; i < _members.elms(); i++){
    std::wstring member = _members[i];
    bool found = false;
    for(int j = 0; j < _membersInLDAP.elms(); j++) {
      if(member.compare(_membersInLDAP[j]) == 0) found = true;
    }
    if(!found) {
      if(!memberAdd) {
        memberAdd = &values.New(ADD);
        if(_editable) {
          memberAdd->add(L"type", L"rfc822MailMember");
        } else {
          memberAdd->add(L"type", L"member");
        }
      }
      memberAdd->add(L"values", member);     
    }
  }
  
  if(values.elms()) {
    Server().modify(_dn(), values);
    return true;
  }
  return false;
  
}

y::ldap::WISA_IMPORT y::ldap::group::getImportStatus() {
  return _importStatus;
} 

y::ldap::group & y::ldap::group::setImportStatus(WISA_IMPORT status) {
  _importStatus = status;
  return *this;
}