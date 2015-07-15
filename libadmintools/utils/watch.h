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

#include "ldap/data.h"
#include "ldap/dataset.h"
#include "utils/log.h"
#include "utils/string.h"
#include "ldap/attributes.h"

template <class T, typename V> 
class watchBase {
protected:
  string _identifier;
  T      _value     ;
  bool   _changed   ;  
  bool   _inLdap;
  
public:
  watchBase(const string & identifier) 
    : _identifier(identifier)
    , _changed(false)
    , _inLdap(false)
    {}
  
  watchBase(const string & identifier, const T & value) 
    : _identifier(identifier)
    , _value(value)
    , _changed(false) 
    , _inLdap(false)
    {}
  
  void reset(const T & value) {
    _value = value;
    _changed = false;
    _inLdap = false;;
  }
  
  bool update(const T & value) {
    if(_value != value) {
      _value = value;
      _changed = true;
      return true;
    }
    return false;
  }
  
  const T & operator()() const { return _value; }
  
  void operator()(const T & value, bool silent = false) {
    _value = value;
    if(!silent) _changed = true;
  }
  
  virtual void readFromLdap(const y::ldap::data & d) = 0;
  virtual void saveToLdap(y::ldap::dataset & values) = 0;
  
  bool changed () {
    return _changed;
  }
  
  void unFlag() {
    _changed = false;
  }
  
};


template<class T>
class intWatch : public watchBase<T, int> {
  public:
  intWatch(const string & identifier) : watchBase<T, int>(identifier) {}
  intWatch(const string & identifier, const T & value) 
  : watchBase<T, int>(identifier, value) {}
  
  void readFromLdap(const y::ldap::data & d) {
    if(d.getValue(watchBase<T, int>::_identifier).size()) {
      try {
        watchBase<T, int>::_value = T(d.getValue(watchBase<T, int>::_identifier).asInt());
        watchBase<T, int>::_inLdap = true;
      } catch (const std::invalid_argument &e) {
        string message("Invalid ldap int conversion: ");
        message += d.getValue(watchBase<T, int>::_identifier);
        y::utils::Log().add(message);
      }     
    }
  }
  
  void saveToLdap(y::ldap::dataset & values) {
    if(!watchBase<T, int>::_changed) return;
    
    string s = string(watchBase<T, int>::_value.get());
    
    if(!watchBase<T, int>::_inLdap) {
      y::ldap::data & d = values.New(y::ldap::ADD);
      d.add("type", watchBase<T, int>::_identifier);
      d.add("values", s);
    } else {
      y::ldap::data & d = values.New(y::ldap::MODIFY);
      d.add("type", watchBase<T, int>::_identifier);
      d.add("values", s);
    }
    
    watchBase<T, int>::unFlag();
  }
}; 

template<class T>
class stringWatch : public watchBase<T, string> {
  public:
  stringWatch(const string & identifier) : watchBase<T, string>(identifier) {}
  stringWatch(const string & identifier, const T & value) 
  : watchBase<T, string>(identifier, value) {}
  
  void readFromLdap(const y::ldap::data & d) {
    if(d.getValue(watchBase<T, string>::_identifier).size()) {
     watchBase<T, string>::_value = T(d.getValue(watchBase<T, string>::_identifier));
     watchBase<T, string>::_inLdap = true;
    }
  }
  
  void saveToLdap(y::ldap::dataset & values) {
    if(!watchBase<T, string>::_changed) return;
    
    string s = watchBase<T, string>::_value.get();
    if(!s.empty()) {
      if(!watchBase<T, string>::_inLdap) {
        y::ldap::data & d = values.New(y::ldap::ADD);
        d.add("type", watchBase<T, string>::_identifier);
        d.add("values", s);
      } else {
        y::ldap::data & d = values.New(y::ldap::MODIFY);
        d.add("type", watchBase<T, string>::_identifier);
        d.add("values", s);
      }
    }
    
    watchBase<T, string>::unFlag();
  }  
};

template<class T>
class dateWatch : public watchBase<T, DATE> {
  public:
  dateWatch(const string & identifier) : watchBase<T, DATE>(identifier) {}
  dateWatch(const string & identifier, const T & value) 
  : watchBase<T, DATE>(identifier, value) {}
  
  void readFromLdap(const y::ldap::data & d) {
    if(d.getValue(watchBase<T, DATE>::_identifier).size()) {
     watchBase<T, DATE>::_value = T(d.getValue(watchBase<T, DATE>::_identifier));
     watchBase<T, DATE>::_inLdap = true;
    }
  }
  
  void saveToLdap(y::ldap::dataset & values) {
    if(!watchBase<T, DATE>::_changed) return;
    
    string s = string(watchBase<T, DATE>::_value.asInt());
    if(!s.empty()) {
      if(!watchBase<T, DATE>::_inLdap) {
        y::ldap::data & d = values.New(y::ldap::ADD);
        d.add("type", watchBase<T, DATE>::_identifier);
        d.add("values", s);
      } else {
        y::ldap::data & d = values.New(y::ldap::MODIFY);
        d.add("type", watchBase<T, DATE>::_identifier);
        d.add("values", s);
      }
    }
    
    watchBase<T, DATE>::unFlag();
  }  
};


template<class T>
class roleWatch : public watchBase<T, ROLE> {
  public:
  roleWatch(const string & identifier) : watchBase<T, ROLE>(identifier) {}
  roleWatch(const string & identifier, const T & value) 
  : watchBase<T, ROLE>(identifier, value) {}
  
  void readFromLdap(const y::ldap::data & d) {
    if(d.getValue(watchBase<T, ROLE>::_identifier).size()) {
     watchBase<T, ROLE>::_value = T(ROLE::toRole(d.getValue(watchBase<T, ROLE>::_identifier)));
     watchBase<T, ROLE>::_inLdap = true;
    }
  }
  
  void saveToLdap(y::ldap::dataset & values) {
    if(!watchBase<T, ROLE>::_changed) return;
    
    string s = ROLE::toText(watchBase<T, ROLE>::_value.get());
    
    if(!watchBase<T, ROLE>::_inLdap) {
      y::ldap::data & d = values.New(y::ldap::ADD);
      d.add("type", watchBase<T, ROLE>::_identifier);
      d.add("values", s);
    } else {
      y::ldap::data & d = values.New(y::ldap::MODIFY);
      d.add("type", watchBase<T, ROLE>::_identifier);
      d.add("values", s);
    }
    
    watchBase<T, ROLE>::unFlag();
  }  
};

template<class T>
class genderWatch : public watchBase<T, GENDER> {
  public:
  genderWatch(const string & identifier) : watchBase<T, GENDER>(identifier) {}
  genderWatch(const string & identifier, const T & value) 
  : watchBase<T, GENDER>(identifier, value) {}
  
  void readFromLdap(const y::ldap::data & d) {
    if(d.getValue(watchBase<T, GENDER>::_identifier).size()) {
     watchBase<T, GENDER>::_value = T(GENDER::toGender(d.getValue(watchBase<T, GENDER>::_identifier)));
     watchBase<T, GENDER>::_inLdap = true;
    }
  }
  
  void saveToLdap(y::ldap::dataset & values) {
    if(!watchBase<T, GENDER>::_changed) return;
    
    string s = GENDER::toText(watchBase<T, GENDER>::_value.get());
    
    if(!watchBase<T, GENDER>::_inLdap) {
      y::ldap::data & d = values.New(y::ldap::ADD);
      d.add("type", watchBase<T, GENDER>::_identifier);
      d.add("values", s);
    } else {
      y::ldap::data & d = values.New(y::ldap::MODIFY);
      d.add("type", watchBase<T, GENDER>::_identifier);
      d.add("values", s);
    }
    
    watchBase<T, GENDER>::unFlag();
  }  
};


template<class T>
class dnWatch : public watchBase<T, DN> {
  public:
  dnWatch(const string & identifier) : watchBase<T, DN>(identifier) {}
  dnWatch(const string & identifier, const T & value) 
  : watchBase<T, DN>(identifier, value) {}
  
  void readFromLdap(const y::ldap::data & d) {
    if(d.getValue(watchBase<T, DN>::_identifier).size()) {
     watchBase<T, DN>::_value = T(DN(d.getValue(watchBase<T, DN>::_identifier)));
     watchBase<T, DN>::_inLdap = true;
    }
  }
  
  void saveToLdap(y::ldap::dataset & values) {
    if(!watchBase<T, DN>::_changed) return;
    
    string s = watchBase<T, DN>::_value.get().get();
    
    if(!watchBase<T, DN>::_inLdap) {
      y::ldap::data & d = values.New(y::ldap::ADD);
      d.add("type", watchBase<T, DN>::_identifier);
      d.add("values", s);
    } else {
      y::ldap::data & d = values.New(y::ldap::MODIFY);
      d.add("type", watchBase<T, DN>::_identifier);
      d.add("values", s);
    }
    
    watchBase<T, DN>::unFlag();
  }  
};