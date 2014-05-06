/* 
 * File:   group.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 10:01 AM
 */

#include "group.h"

y::ldap::group::group(bool editable) 
  : _dn(DN("")), 
    _cn(CN("")), 
    _new(true), 
    _editable(editable) {
}

const y::ldap::DN & y::ldap::group::dn() {
  return _dn();
}

const y::ldap::CN & y::ldap::group::cn() {
  return _cn();
}

container<y::ldap::DN> & y::ldap::group::owners() {
  return _owners;
}

container<y::ldap::DN> & y::ldap::group::members() {
  return _members;
}


