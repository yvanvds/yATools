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

y::utils::log::log() : _useConsole(true), _useFile(true), _useBind(false), _file("/var/log/admintools") {
  _stream.open(_file.utf8(), std::ios_base::out | std::ios_base::app);
}

y::utils::log & y::utils::log::add(const string& message) {
  std::lock_guard<std::mutex> lock(m);
  if(_useConsole) {
    std::cout << message.utf8() << std::endl;
  }
  if(_useFile) {
    _stream << message.wide() << std::endl;
  }
  if(_logFunction != nullptr) {
    (*_logFunction)(message);
  }
  if(_useBind) {
    _bindFunction(message);
  }
  return *this;
}

y::utils::log & y::utils::log::useConsole(bool enable) {
  std::lock_guard<std::mutex> lock(m);
  _useConsole = enable;
  return *this;
}

y::utils::log & y::utils::log::useFile(bool enable, const string& file) {
  std::lock_guard<std::mutex> lock(m);
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
  std::lock_guard<std::mutex> lock(m);
  _logFunction = logFunction;
  return *this;
}

y::utils::log & y::utils::log::bind(const std::function<void(const string &)> & function) {
  std::lock_guard<std::mutex> lock(m);
  _bindFunction = function;
  _useBind = true;
  return *this;
}

y::utils::log & y::utils::log::unbind() {
  std::lock_guard<std::mutex> lock(m);
  _useBind = false;
  return *this;
}