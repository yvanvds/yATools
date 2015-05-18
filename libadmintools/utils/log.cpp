/* 
 * File:   log.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 2:11 PM
 */

#include "log.h"
#include <iostream>
#include "convert.h"

y::utils::log & y::utils::Log() {
  static log l;
  return l;
}

y::utils::log::log() : _useConsole(true), _useFile(true), _file("/var/log/admintools") {
  _stream.open(_file.utf8(), std::ios_base::out | std::ios_base::app);
}

y::utils::log & y::utils::log::add(const string& message) {
  if(_useConsole) {
    std::cout << message.utf8() << std::endl;
  }
  if(_useFile) {
    _stream << message.wide() << std::endl;
  }
  if(_logFunction != nullptr) {
    (*_logFunction)(message);
  }
  return *this;
}

y::utils::log & y::utils::log::useConsole(bool enable) {
  _useConsole = enable;
  return *this;
}

y::utils::log & y::utils::log::useFile(bool enable, const string& file) {
  if(_useFile) {
    _stream.close();
  }
  _useFile = enable;
  if(_useFile) {
    _stream.open(_file.utf8(), std::ios_base::out | std::ios_base::app);
  }
  return *this;
}

y::utils::log & y::utils::log::useFunction(void(*logFunction)(const string&)) {
  _logFunction = logFunction;
  return *this;
}