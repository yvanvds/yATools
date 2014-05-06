/* 
 * File:   group.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 10:01 AM
 */

#include "group.h"

ldp::group::group(bool editable) : _dn(DN("")), _cn(CN("")), _new(true), _editable(editable) {
}


