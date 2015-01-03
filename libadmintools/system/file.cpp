/* 
 * File:   file.cpp
 * Author: yvan
 * 
 * Created on January 3, 2015, 8:24 PM
 */

#include "file.h"
#include <fstream>
#include <ios>

void y::sys::file::append(const std::string& file, const std::string& line) {
  std::ofstream ofs(file, std::ios_base::app);
  ofs << line;
  ofs.close();
}

bool y::sys::file::has(const std::string& file, const std::string& token) {
  std::ifstream ifs(file);
  std::string line;
  while(std::getline(ifs, line)) {
    if(line.find(token, 0) != std::string::npos) {
      ifs.close();
      return true;
    }
  }
  ifs.close();
  return false;
}