/* 
 * File:   hostValidate.cpp
 * Author: yvan
 * 
 * Created on January 3, 2015, 1:54 PM
 */

#include <iostream>
#include "validators.h"
#include "admintools.h"
#include "config.h"

void ValidateAll() {
  hostValidate();
}

void hostValidate() {
  std::vector<std::string> result;
  // check hostname
  y::sys::GetProcessResult("cat /etc/hostname", result);
  if(result.size()) {
    if (result[0].compare(Config().getServerName()) == 0) {
      std::cout << "/etc/hostname is valid" << std::endl;
      return;
    }
  }
  y::sys::stdOut("hostname wrong");
}