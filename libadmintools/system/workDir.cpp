/* 
 * File:   workDir.cpp
 * Author: yvan
 * 
 * Created on December 8, 2013, 2:09 PM
 */

#include "workDir.h"

at::workDir at::WorkDir;

const std::string & at::workDir::get() {
  return dir.string();
}

void at::workDir::set(const std::string & path) {
  dir = path;
}




