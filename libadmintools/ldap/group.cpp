/* 
 * File:   group.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 10:01 AM
 */

#include "group.h"

ldp::group::group(bool editable) 
  : _dn(DN("")), 
    _cn(CN("")), 
    _new(true), 
    _editable(editable) {
}

const ldp::DN & ldp::group::dn() {
  return _dn();
}

const ldp::CN & ldp::group::cn() {
  return _cn();
}

container<ldp::DN> & ldp::group::owners() {
  return _owners;
}

container<ldp::DN> & ldp::group::members() {
  return _members;
}


