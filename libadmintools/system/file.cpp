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