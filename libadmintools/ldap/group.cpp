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
#include "defines.h"

y::ldap::group::group(y::ldap::server * server) 
  : ldapObject(server),
    _editable(true) {}

void y::ldap::group::clear() {
  _owners.clear();
  _members.clear();
  _ownersInLDAP.clear();
  _membersInLDAP.clear();
}

bool y::ldap::group::load(const string & cn) {
  dataset d(server);
  string filter("cn=" + cn);
  
  if(!editable() && d.create(filter, "ou=mailGroups")) {
    loadData(d.get(0));
  } else if(editable() && d.create(filter, "ou=editableMailGroups")) {
    loadData(d.get(0));
  } else {
    _cn(cn);
  }
  
  return !_new;
}

bool y::ldap::group::loadData(const data& d) {
  _dn(DN(d.getValue("DN")), true);
  _cn(d.getValue("cn"), true);
  
  if(d.elms("owner")) {
    _editable = false;
    for(int i = 0; i < d.elms("owner"); i++) {
      string & owner = _owners.New();
      owner = d.getValue("owner", i);
      _ownersInLDAP.New() = owner;
    }
    for(int i = 0; i < d.elms("member"); i++) {
      string & member = _members.New();
      member = d.getValue("member", i);
      _membersInLDAP.New() = member;
    }
    
  } else {
    _editable = true;
    for(int i = 0; i < d.elms("mail"); i++) {
      string & owner = _owners.New();
      owner = d.getValue("mail", i);
      _ownersInLDAP.New() = owner;
    }
    for(int i = 0; i < d.elms("rfc822MailMember"); i++) {
      string & member = _members.New();
      member = d.getValue("rfc822MailMember", i);
      _membersInLDAP.New() = member;
    }
  }
  _new = false;
  return !_new;
}

container<string> & y::ldap::group::owners() {
  return _owners;
}

container<string> & y::ldap::group::members() {
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

bool y::ldap::group::removeOwner(const string& owner) {
  for(int i = 0; i < _owners.elms(); i++) {
    if(_owners[i] == owner) {
      _owners.remove(i);
      _flaggedForCommit = true;
      return true;
    }
  }
  return false;
}

bool y::ldap::group::removeMember(const string& member) {
  for (int i = 0; i < _members.elms(); i++) {
    if(_members[i] == member) {
      _members.remove(i);
      _flaggedForCommit = true;
      return true;
    }
  }
  return false;
}

bool y::ldap::group::addOwner(const string& owner) {
  for(int i = 0; i < _owners.elms(); i++) {
    if(_owners[i] == owner) {
      // already in group
      return false;
    }
  }
  _owners.New() = owner;
  _flaggedForCommit = true;
  return true;
}

bool y::ldap::group::addMember(const string& member) {
  for(int i = 0; i < _members.elms(); i++) {
    if(_members[i] == member) {
      // already in group
      return false;
    }
  }
  _members.New() = member;
  _flaggedForCommit = true;
  return true;
}

bool y::ldap::group::addNew(dataset & values) {
  // don't create if there are no members
  if(_members.elms() == 0) {
    if(!_editable) {
      _members.New() = "uid=gast,ou=People,dc=sanctamaria-aarschot,dc=be";
    } else {
      _members.New() = "dummy@sanctamaria-aarschot.be";
    }
  }

  // add owner if not present
  if(!_owners.elms()) {
    TODO(generalize this)
    if(!_editable) {
      _owners.New() = "uid=inge,ou=personeel,ou=People,dc=sanctamaria-aarschot,dc=be";
    } else {
      _owners.New() = "directie@sanctamaria-aarschot.be";
    }
  } 

  // create group first
  string dn("cn=" + _cn());
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
  cn.add("values", _cn());

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

  return true;
}

bool y::ldap::group::update(dataset & values) {
  TODO(in editable mailgroups owners should also be members)

  data * ownerDelete = nullptr;
  // remove owners if needed 
  for(int i = 0; i < _ownersInLDAP.elms(); i++){
    string owner = _ownersInLDAP[i];
    bool found = false;
    for(int j = 0; j < _owners.elms(); j++) {
      if(owner == _owners[j]) found = true;
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
    string member = _membersInLDAP[i];
    bool found = false;
    for(int j = 0; j < _members.elms(); j++) {
      if(member == "uid=gast,ou=People,dc=sanctamaria-aarschot,dc=be" && _members.elms() > 1) {
        found = false;
      } else if(member == "dummy@sanctamaria-aarschot.be" && _members.elms() > 1) {
        found = false;
      } else if(member == _members[j]) found = true;
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
    string owner = _owners[i];
    bool found = false;
    for(int j = 0; j < _ownersInLDAP.elms(); j++) {
      if(owner == _ownersInLDAP[j]) found = true;
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
    string member = _members[i];
    bool found = false;
    for(int j = 0; j < _membersInLDAP.elms(); j++) {
      if(member == _membersInLDAP[j]) found = true;
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
  
  return true; 
}
