/* 
 * File:   wisaImport.cpp
 * Author: yvan
 * 
 * Created on February 17, 2015, 10:46 AM
 */

#include <Wt/WWidget>
#include <Wt/WStackedWidget>
#include <Wt/WCompositeWidget>
#include <Wt/WPanel>
#include <Wt/WLayout>
#include <Wt/WText>
#include <Wt/WVBoxLayout>
#include <Wt/WFileUpload>
#include <Wt/WProgressBar>
#include <Wt/WPushButton>
#include <Wt/WScrollArea>
#include <Wt/WMessageBox>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <Wt/WTable>
#include "wisaImport.h"
#include "utils/convert.h"
#include "ldap/server.h"
#include <boost/locale.hpp>
#include <boost/lexical_cast.hpp>
#include <Wt/WLineEdit>
#include <Wt/WCheckBox>
#include <Wt/WIntValidator>
#include <Wt/WApplication>
#include <thread>
#include <Wt/WTabWidget>
#include <Wt/WGlobal>
#include "base/stackPage.h"


wisaImport::wisaImport(y::ldap::server* server) : ldapServer(server) { 
  wUpload = new wisaUpload(this);
  addPage(wUpload);
  wUpload->showButtons(false, false);
  
  WParseStudentFile = new wisaParseStudentFile(this); 
  addPage(WParseStudentFile);
  WParseStudentFile->showButtons(true, true);
  
  WParseClassFile = new wisaParseClassFile(this); 
  addPage(WParseClassFile);
  WParseClassFile->showButtons(true, true);
  
  WNoID = new wisaNoID(this); 
  addPage(WNoID);
  WNoID->showButtons(false, true);
  
  WCompareFile = new wisaCompareFile(this);
  addPage(WCompareFile);
  WCompareFile->showButtons(false, true);
  
  WCompareClasses = new wisaCompareClasses(this);
  addPage(WCompareClasses);
  WCompareClasses->showButtons(true, true);
  
  WCompareNames = new wisaCompareNames(this);
  addPage(WCompareNames);
  WCompareNames->showButtons(false, true);
    
  WNewGroups = new wisaNewGroups(this);
  addPage(WNewGroups);
  WNewGroups->showButtons(false, true);
  
  WConfirmSubmit = new wisaConfirmSubmit(this);
  addPage(WConfirmSubmit);
  WConfirmSubmit->showButtons(true, true);
  
  WCommitChanges = new wisaCommitChanges(this);
  addPage(WCommitChanges);
  WCommitChanges->showButtons(false, false);
  
  WCommitClasses = new wisaCommitClasses(this);
  addPage(WCommitClasses);
  WCommitClasses->showButtons(false, false);
}

void wisaImport::setWisaStudentFile(const string& file) {
  wisaStudentFile = file;
  wisaAccounts.clear();
  
  // get lines from file
  boost::locale::generator gen;
  std::locale utf8  = gen("en_US.UTF-8");
  std::wifstream stream(file.utf8());
  stream.imbue(utf8);
  
  if(!readLinesUTF8(&stream)) {
    // probably the file has another encoding
    // Try again with latin1
    std::locale latin = gen("en_US.iso88591");
    std::ifstream stream2(file.utf8());
    stream2.imbue(latin);
    readLinesLatin(&stream2);
  }
}

void wisaImport::setWisaClassFile(const string& file) {
  wisaClassFile = file;
  wisaClasses.clear();
  
  // get lines from file
  boost::locale::generator gen;
  std::locale utf8  = gen("en_US.UTF-8");
  std::wifstream stream(file.utf8());
  stream.imbue(utf8);
  
  if(!readLinesUTF8(&stream), false) {
    // probably the file has another encoding
    // Try again with latin1
    std::locale latin = gen("en_US.iso88591");
    std::ifstream stream2(file.utf8());
    stream2.imbue(latin);
    readLinesLatin(&stream2, false);
  }
}

bool wisaImport::readLinesUTF8(std::wifstream * stream, bool students) {
  std::wstring line;
  while(std::getline(*stream, line)) {
    if(!tokenize(line, students)) {
      Wt::WMessageBox * message = new Wt::WMessageBox (
            "Error",
            "<p>Het aantal kolommen in dit bestand klopt niet.</p>",
            Wt::Critical, Wt::Ok);
      message->buttonClicked().connect(std::bind([=] () {
        reset();
        showNewPage(W_UPLOAD);
      }));
    }    
  }
  return !wisaAccounts.empty();
}

bool wisaImport::readLinesLatin(std::ifstream* stream, bool students) {
  std::string line;
  while(std::getline(*stream, line)) {
    std::wstring converted = boost::locale::conv::to_utf<wchar_t>(line, "Latin1");
    if(!tokenize(converted, students)) {
      Wt::WMessageBox * message = new Wt::WMessageBox (
            "Error",
            "<p>Het aantal kolommen in dit bestand klopt niet.</p>",
            Wt::Critical, Wt::Ok);
      message->buttonClicked().connect(std::bind([=] () {
        reset();
        showNewPage(W_UPLOAD);
      }));
    }
  }
  return !wisaAccounts.empty();
}


bool wisaImport::tokenize(const std::wstring& line, bool students) {
  std::wstring item;
  std::vector<std::wstring> elms;

  for(int i = 0; i < line.size(); i++) {
    if(line[i] != ';') {
      item += line[i];
    } else {
      elms.push_back(std::move(item.c_str())); 
      item.clear();
    }
  }
  elms.push_back(std::move(item.c_str())); 

  // add to wisa contents
  if(elms.size()) {
    if(students) return wisaAccounts.New().set(elms);
    else return wisaClasses.New().set(elms);
  }
  return false;
}

string wisaImport::getWisaStudentFile() {
  return wisaStudentFile;
}

string wisaImport::getWisaClassFile() {
  return wisaClassFile;
}

void wisaImport::reset() {
  wUpload->clear();
  ldapServer->clear();
  //showPage(0);
}

container<wisaImport::wisaAccount> & wisaImport::getWisaAccounts() {
  return wisaAccounts;
}

bool wisaImport::wisaAccount::set(std::vector<std::wstring>& line) {
  if(line.size() != 5) {
    return false;
  }
  sn = string(line[0]);
  cn = string(line[1]);
  schoolClass = string(line[2]);
  date = string(line[3]);
  ID = std::stoi(line[4]);
  return true;
}

bool wisaImport::wisaClass::set(std::vector<std::wstring> & line) {
  if(line.size() != 7) {
    return false;
  }
  name = string(line[0]);
  description = string(line[1]);
  adminGroup = string(line[2]).asInt();
  // we don't need line[3]
  schoolID = string(line[4]).asInt();
  titular = string(line[5]);
  titular.keeponlyChars().removeNewLine();
  adjunct = string(line[6]);
  adjunct.keeponlyChars().removeNewLine();
}

container<wisaImport::wisaClass> & wisaImport::getWisaClasses() {
  return wisaClasses;
}

void wisaImport::showErrorOnScreen(const string& message) {
  WCommitChanges->addMessage(message);
}

void wisaImport::showNewPage(WISA_PAGE value) {
  switch (value) {
    case W_UPLOAD: showPage(wUpload->getPageIndex()); break;
    case W_PARSE_STUDENT: showPage(WParseStudentFile->getPageIndex()); break;
    case W_PARSE_CLASS: showPage(WParseClassFile->getPageIndex()); break;
    case W_COMPAREGROUPS: showPage(WCompareClasses->getPageIndex()); break;
    case W_COMMITCLASSES: showPage(WCommitClasses->getPageIndex()); break;
  }
}