/* 
 * File:   console.cpp
 * Author: yvan
 * 
 * Created on February 10, 2015, 5:00 PM
 */

#include "console.h"
#include <iostream>

bool y::utils::ask(const std::string& question) {
  std::cout << question << " (y/N): ";
  std::string response;
  std::getline(std::cin, response);
  if(response[0] == 'y' || response[0] == 'Y') return true;
  return false;
}