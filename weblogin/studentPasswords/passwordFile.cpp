/* 
 * File:   pdfPasswords.cpp
 * Author: yvan
 * 
 * Created on July 15, 2015, 8:17 PM
 */

#include "passwordFile.h"

passwordFile::passwordFile(Wt::WObject* parent) : Wt::WResource(parent) {
  suggestFileName("wachtwoorden.txt");
}

void passwordFile::handleRequest(const Wt::Http::Request& request, Wt::Http::Response& response) {
  response.setMimeType("plain/text");
  for(int i = 0; i < lines.elms(); i++) {
    response.out() << lines[i].c_str() << std::endl;
  }
}

passwordFile & passwordFile::addLine(const string& line) {
  lines.New() = line;
  return *this;
}

passwordFile & passwordFile::addCsv(const string& line) {
  lines.last() += ";";
  lines.last() += line;
}
