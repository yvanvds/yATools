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
    _flaggedForCommit(false) {
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
  
  if(d.create(filter, "ou=mailGroups")) {
    load(d.get(0));
  } else if(d.create(filter, "ou=editableMailGroups")) {
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
  return _dn();
}

const y::ldap::CN & y::ldap::group::cn() {
  return _cn();
}

container<std::string> & y::ldap::group::owners() {
  return _owners;
}

container<std::string> & y::ldap::group::members() {
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

bool y::ldap::group::save() {
  if(!_flaggedForCommit) return false;
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

  data & d = values.New(ADD);
  d.add("type", "objectClass");
  d.add("values", "top");
  d.add("values", "extensibleObject");
  if(_editable) {
    d.add("values", "nisMailAlias");
  } else {
    d.add("values", "groupOfNames");
  }
  
  data & d1 = values.New(ADD);
  d1.add("type", "cn");
  d1.add("values", _cn()());

  data & d2 = values.New(ADD);
  if(_editable) {
    d2.add("type", "mail");
  } else {
    d2.add("type", "owner");
  }
  for(int i = 0; i < _owners.elms(); i++) {
    d2.add("values", _owners[i]);
  }
  
  // if editable, also add as member
  if(_editable) {
    data & d = values.New(ADD);
    d.add("type", "rfc822mailmember");
    for(int i = 0; i < _owners.elms(); i++) {
      d.add("values", _owners[i]);
    }
  }

  data & d3 = values.New(ADD);
  if(_editable) {
    d3.add("type", "rfc822mailmember");
  } else {
    d3.add("type", "member");
  }
  for(int i = 0; i < _members.elms(); i++) {
    d3.add("values", _members[i]);
  }

  if(values.elms()) {
    Server().setData(_dn(), values);
    return true;
  }
  return false;
}

bool y::ldap::group::saveUpdate() {
  dataset values;
  // remove owners if needed 
  for(int i = 0; i < _ownersInLDAP.elms(); i++){
    std::string owner = _ownersInLDAP[i];
    bool found = false;
    for(int j = 0; j < _owners.elms(); j++) {
      if(owner.compare(_owners[j]) == 0) found = true;
    }
    if(!found) {
      data & d = values.New(DELETE);
      if(_editable) {
        d.add("type", "mail");
      } else {
        d.add("type", "owner");
      }
      d.add("values", owner);     
    }
  }
  
  // remove members if needed
  for(int i = 0; i < _membersInLDAP.elms(); i++){
    std::string member = _membersInLDAP[i];
    bool found = false;
    for(int j = 0; j < _members.elms(); j++) {
      if(member.compare(_members[j]) == 0) found = true;
    }
    if(!found) {
      data & d = values.New(DELETE);
      if(_editable) {
        d.add("type", "rfc822mailmember");
      } else {
        d.add("type", "member");
      }
      d.add("values", member);     
    }
  }
  
  // add owners if needed
  for(int i = 0; i < _owners.elms(); i++){
    std::string owner = _owners[i];
    bool found = false;
    for(int j = 0; j < _ownersInLDAP.elms(); j++) {
      if(owner.compare(_ownersInLDAP[j]) == 0) found = true;
    }
    if(!found) {
      data & d = values.New(ADD);
      if(_editable) {
        d.add("type", "mail");
      } else {
        d.add("type", "owner");
      }
      d.add("values", owner);     
    }
  }  
  
  // add members if needed
  for(int i = 0; i < _members.elms(); i++){
    std::string member = _members[i];
    bool found = false;
    for(int j = 0; j < _membersInLDAP.elms(); j++) {
      if(member.compare(_membersInLDAP[j]) == 0) found = true;
    }
    if(!found) {
      data & d = values.New(ADD);
      if(_editable) {
        d.add("type", "rfc822mailmember");
      } else {
        d.add("type", "member");
      }
      d.add("values", member);     
    }
  }
  
  if(values.elms()) {
    Server().setData(_dn(), values);
    return true;
  }
  return false;
  
}