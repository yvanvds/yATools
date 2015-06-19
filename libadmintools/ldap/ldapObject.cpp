/* 
 * File:   ldapObject.cpp
 * Author: yvan
 * 
 * Created on June 12, 2015, 5:14 PM
 */

#include "ldapObject.h"
#include "dataset.h"
#include "server.h"


y::ldap::ldapObject::ldapObject(y::ldap::server* server) 
        : server(server),
          _dn(DN("")),
          _cn(""),
          _new(true),
          _flaggedForCommit(false),
          _flaggedForRemoval(false),
          _importStatus(WI_NOT_ACCOUNTED) {}

bool y::ldap::ldapObject::isNew() {
  return _new;
}

bool y::ldap::ldapObject::load(const DN & id) {
  dataset d(server);
  if(d.createFromDN(id.get())) {
    load(d.get(0));
  }
  return !_new;
}

bool y::ldap::ldapObject::load(const data& d) {
  _dn(DN(d.getValue("DN")), true);
  _cn(d.getValue("cn"), true);
  
  _new = !loadData(d);
  return !_new;
}

WISA_IMPORT y::ldap::ldapObject::getImportStatus() {
  return _importStatus;
}

void y::ldap::ldapObject::setImportStatus(WISA_IMPORT status) {
  _importStatus = status;
}

const DN & y::ldap::ldapObject::dn() const {
  return _dn();
}

const string & y::ldap::ldapObject::cn() const {
  return _cn();
}

void y::ldap::ldapObject::cn(const string& value) {
  _cn(value);
}



bool y::ldap::ldapObject::save() {
  if(!_flaggedForCommit) return false;
  
  if(_flaggedForRemoval) {
    beforeRemove();
    server->remove(_dn());
    clear();
    _new = true; 
    _dn(DN(""));
    _cn("");
    return true;
  }
  
  if(_new) {
    dataset values(server);
    if(addNew(values)) {
      if(values.elms()) {
        server->add(_dn(), values);
        _new = false;
        return true;
      } 
    } 
  } else {
    dataset values(server);
    if(update(values)) {
      if(values.elms()) {
        server->modify(_dn(), values);
        return true;
      }
    } 
  }
  return false;
}

void y::ldap::ldapObject::flagForRemoval() {
  _flaggedForCommit  = true;
  _flaggedForRemoval = true;
}