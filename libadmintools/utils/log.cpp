/* 
 * File:   log.cpp
 * Author: yvan
 * 
 * Created on January 16, 2014, 2:11 PM
 */

#include "log.h"
#include <iostream>

log::log() : _useConsole(true), _useFile(true), _file("/var/log/admintools") {
  _stream.open(_file, std::ios_base::out | std::ios_base::app);
}

log & log::add(const std::string& message) {
  if(_useConsole) {
    std::cout << message << std::endl;
  }
  if(_useFile) {
    _stream << message << std::endl;
  }
}

log & log::useConsole(bool enable) {
  _useConsole = enable;
}

log & log::useFile(bool enable, const std::string& file) {
  if(_useFile) {
    _stream.close();
  }
  _useFile = enable;
  if(_useFile) {
    _stream.open(_file, std::ios_base::out | std::ios_base::app);
  }
}