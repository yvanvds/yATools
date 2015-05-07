/* 
 * File:   log.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 2:11 PM
 */

#include "log.h"
#include <iostream>

y::utils::log & y::utils::Log() {
  static log l;
  return l;
}

y::utils::log::log() : _useConsole(true), _useFile(true), _file("/var/log/admintools") {
  _stream.open(_file, std::ios_base::out | std::ios_base::app);
}

y::utils::log & y::utils::log::add(const std::wstring& message) {
  if(_useConsole) {
    std::wcout << message << std::endl;
  }
  if(_useFile) {
    _stream << message << std::endl;
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

y::utils::log & y::utils::log::useFile(bool enable, const std::string& file) {
  if(_useFile) {
    _stream.close();
  }
  _useFile = enable;
  if(_useFile) {
    _stream.open(_file, std::ios_base::out | std::ios_base::app);
  }
  return *this;
}

y::utils::log & y::utils::log::useFunction(void(*logFunction)(const std::wstring&)) {
  _logFunction = logFunction;
  return *this;
}