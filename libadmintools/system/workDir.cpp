/* 
 * File:   workDir.cpp
 * Author: yvan
 * 
 * Created on December 8, 2013, 2:09 PM
 */

#include "workDir.h"

y::sys::workDir y::sys::WorkDir;

const std::string & y::sys::workDir::get() {
  return dir.string();
}

void y::sys::workDir::set(const std::string & path) {
  dir = path;
}




