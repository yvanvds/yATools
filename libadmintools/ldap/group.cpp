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
#include <assert.h>

y::ldap::group::group() 
  : _dn(DN("")), 
    _cn(CN("")), 
    _new(true), 
    _editable(true),
    _flaggedForCommit(false),
    _flaggedForDelete(false){
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
  std::string filter;
  filter = "cn="; filter.append(id());
  
  if(!editable() && d.create(filter, "ou=mailGroups")) {
    load(d.get(0));
  } else if(editable() && d.create(filter, "ou=editableMailGroups")) {
    load(d.get(0));
  } else {
    _cn(id);
  }
  
  return !_new;
}

bool y::ldap::group::load(const data& d) {
  _dn(DN(d.getValue("DN")), true);
  _cn(CN(d.getValue("cn")), true);
  
  if(d.elms("owner")) {
    _editable = false;
    for(int i = 0; i < d.elms("owner"); i++) {
      std::string & owner = _owners.New();
      owner = d.getValue("owner", i);
      _ownersInLDAP.New() = owner;
    }
    for(int i = 0; i < d.elms("member"); i++) {
      std::string & member = _members.New();
      member = d.getValue("member", i);
      _membersInLDAP.New() = member;
    }
    
  } else {
    _editable = true;
    for(int i = 0; i < d.elms("mail"); i++) {
      std::string & owner = _owners.New();
      owner = d.getValue("mail", i);
      _ownersInLDAP.New() = owner;
    }
    for(int i = 0; i < d.elms("rfc822MailMember"); i++) {
      std::string & member = _members.New();
      member = d.getValue("rfc822MailMember", i);
      _membersInLDAP.New() = member;
    }
  }
  _new = false;
  return !_new;
}

void y::ldap::group::flagForCommit() {
  _flaggedForCommit = true;
}

const y::ldap::DN & y::ldap::group::dn() {
  assert(!_flaggedForDelete);
  return _dn();
}

const y::ldap::CN & y::ldap::group::cn() {
  assert(!_flaggedForDelete);
  return _cn();
}

container<std::string> & y::ldap::group::owners() {
  assert(!_flaggedForDelete);
  return _owners;
}

container<std::string> & y::ldap::group::members() {
  assert(!_flaggedForDelete);
  return _members;
}

y::ldap::group & y::ldap::group::editable(bool value) {
  // make sure this is only used with new groups
  assert(_new);
  assert(!_flaggedForDelete);
  _editable = value;
  return (*this);
}

bool y::ldap::group::editable() {
  return _editable;
}

bool y::ldap::group::isNew() {
  return _new;
}

void y::ldap::group::flagForDelete() {
  _flaggedForCommit = true; // delete is also a commit
  _flaggedForDelete = true;
}

bool y::ldap::group::wilBeDeleted() {
  return _flaggedForDelete;
}

bool y::ldap::group::save() {
  if(!_flaggedForCommit) return false;
  
  if(_flaggedForDelete) {
    Server().remove(_dn());
    // not really needed, but you never know
    _members.clear();
    _owners.clear();
    
    return true;
  }
  
  dataset values;
  
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
  if(_members.elms() == 0) return false;

  // add owner if not present
  if(!_editable && !_owners.elms()) {
    // TODO generalize this
    _owners.New() = "uid=inge,ou=personeel,ou=People,dc=sanctamaria-aarschot,dc=be";
  }

  // create group first
  std::string dn;
  dn = "cn="; dn += _cn()();
  if(_editable) {
    dn += ",ou=editableMailGroups,";
  } else {
    dn += ",ou=mailGroups,";
  }
  dn += utils::Config().getLdapBaseDN();
  _dn(DN(dn), true);

  data & d = values.New(NEW);
  d.add("type", "objectClass");
  d.add("values", "top");
  d.add("values", "extensibleObject");
  if(_editable) {
    d.add("values", "nisMailAlias");
  } else {
    d.add("values", "groupOfNames");
  }
  
  data & cn = values.New(NEW);
  cn.add("type", "cn");
  cn.add("values", _cn()());

  data & own = values.New(NEW);
  if(_editable) {
    own.add("type", "mail");
  } else {
    own.add("type", "owner");
  }
  for(int i = 0; i < _owners.elms(); i++) {
    own.add("values", _owners[i]);
  }
  
  // if editable, also add as member
  data & mbs = values.New(NEW);
  if(_editable) {
    mbs.add("type", "rfc822MailMember");
    for(int i = 0; i < _owners.elms(); i++) {
      mbs.add("values", _owners[i]);
    }
  } else {
    mbs.add("type", "member");
  }
  
  for(int i = 0; i < _members.elms(); i++) {
    mbs.add("values", _members[i]);
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
    std::string owner = _ownersInLDAP[i];
    bool found = false;
    for(int j = 0; j < _owners.elms(); j++) {
      if(owner.compare(_owners[j]) == 0) found = true;
    }
    if(!found) {
      if(!ownerDelete) {
        ownerDelete = &values.New(DELETE);
        if(_editable) {
          ownerDelete->add("type", "mail");
        } else {
          ownerDelete->add("type", "owner");
        }
      }
      ownerDelete->add("values", owner);     
    }
  }
  
  // remove members if needed
  data * memberDelete = nullptr;
  for(int i = 0; i < _membersInLDAP.elms(); i++){
    std::string member = _membersInLDAP[i];
    bool found = false;
    for(int j = 0; j < _members.elms(); j++) {
      if(member.compare(_members[j]) == 0) found = true;
    }
    if(!found) {
      if(!memberDelete) {
        memberDelete = &values.New(DELETE);
        if(_editable) {
          memberDelete->add("type", "rfc822MailMember");
        } else {
          memberDelete->add("type", "member");
        }
      }
      memberDelete->add("values", member);     
    }
  }
  
  // add owners if needed
  data * ownerAdd = nullptr;
  for(int i = 0; i < _owners.elms(); i++){
    std::string owner = _owners[i];
    bool found = false;
    for(int j = 0; j < _ownersInLDAP.elms(); j++) {
      if(owner.compare(_ownersInLDAP[j]) == 0) found = true;
    }
    if(!found) {
      if(!ownerAdd) {
        ownerAdd = &values.New(ADD);
        if(_editable) {
          ownerAdd->add("type", "mail");
        } else {
          ownerAdd->add("type", "owner");
        }
      }
      ownerAdd->add("values", owner);     
    }
  }  
  
  // add members if needed
  data * memberAdd = nullptr;
  for(int i = 0; i < _members.elms(); i++){
    std::string member = _members[i];
    bool found = false;
    for(int j = 0; j < _membersInLDAP.elms(); j++) {
      if(member.compare(_membersInLDAP[j]) == 0) found = true;
    }
    if(!found) {
      if(!memberAdd) {
        memberAdd = &values.New(ADD);
        if(_editable) {
          memberAdd->add("type", "rfc822MailMember");
        } else {
          memberAdd->add("type", "member");
        }
      }
      memberAdd->add("values", member);     
    }
  }
  
  if(values.elms()) {
    Server().modify(_dn(), values);
    return true;
  }
  return false;
  
}