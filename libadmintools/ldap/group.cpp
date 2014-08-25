/* 
 * File:   group.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 10:01 AM
 */

#include "group.h"
#include "dataset.h"
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
  std::string filter;
  filter = "DN="; filter.append(id());
  
  if(d.create(filter, "ou=mailGroups")) {
    load(d.get(0));
  } else if(d.create(filter, "ou=editableMailGroups")) {
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
    }
    for(int i = 0; i < d.elms("member"); i++) {
      std::string & member = _members.New();
      member = d.getValue("member", i);
    }
    
  } else {
    _editable = true;
    for(int i = 0; i < d.elms("mail"); i++) {
      std::string & owner = _owners.New();
      owner = d.getValue("mail", i);
    }
    for(int i = 0; i < d.elms("rfc822MailMember"); i++) {
      std::string & member = _members.New();
      member = d.getValue("rfc822MailMember", i);
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

