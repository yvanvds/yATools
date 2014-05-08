/* 
 * File:   watch.h
 * Author: yvan
 *
 * Created on January 14, 2014, 7:07 PM
 * 
 * Watches make sure we can detect if a variable has changed after
 * its initialisation. They are used to detect if changes should be
 * propagated to the ldap server.
 * 
 */

#pragma once


template <class T> class watch {
private:
  T    _value  ;
  bool _changed;
  
public:
  watch()                :                _changed(false) {}
  watch(const T & value) : _value(value), _changed(false) {}
  
  const T & operator()() const { return _value; }
  
  void operator()(const T & value, bool silent = false) {
    _value = value;
    if(!silent) _changed = true;
  }
  
  bool changed () {
    return _changed;
  }
  
};
