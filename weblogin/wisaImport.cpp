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

wisaImport & WisaImport() {
  static wisaImport w;
  return w;
}


y::gui::stackPageManager * wisaImport::get() {
  manager = new y::gui::stackPageManager();  
 
  wUpload = new wisaUpload();
  manager->addPage(wUpload);
  wUpload->showButtons(false, false);
  
  WParseFile = new wisaParseFile(); 
  manager->addPage(WParseFile);
  WParseFile->showButtons(true, true);
  
  WNoID = new wisaNoID(); 
  manager->addPage(WNoID);
  WNoID->showButtons(false, true);
  
  WCompareFile = new wisaCompareFile();
  manager->addPage(WCompareFile);
  WCompareFile->showButtons(false, true);
  
  WCompareGroups = new wisaCompareGroups();
  manager->addPage(WCompareGroups);
  WCompareGroups->showButtons(false, true);
  
  WCompareNames = new wisaCompareNames();
  manager->addPage(WCompareNames);
  WCompareNames->showButtons(false, true);
  
  WNewGroups = new wisaNewGroups();
  manager->addPage(WNewGroups);
  WNewGroups->showButtons(false, true);
  
  WConfirmSubmit = new wisaConfirmSubmit();
  manager->addPage(WConfirmSubmit);
  WConfirmSubmit->showButtons(true, true);
  
  WCommitChanges = new wisaCommitChanges();
  manager->addPage(WCommitChanges);
  WCommitChanges->showButtons(false, false);
  
  return manager;
}

void wisaImport::setWisaFile(const std::string& file) {
  wisaFile = file;
  wisaAccounts.clear();
  
  // get lines from file
  boost::locale::generator gen;
  std::locale utf8  = gen("en_US.UTF-8");
  std::wifstream stream(file);
  stream.imbue(utf8);
  
  if(!readLinesUTF8(&stream)) {
    // probably the file has another encoding
    // Try again with latin1
    std::locale latin = gen("en_US.iso88591");
    std::ifstream stream2(file);
    stream2.imbue(latin);
    readLinesLatin(&stream2);
  }
  
  // read groups
  wisaGroups.clear();
  
  for(int i = 0; i < wisaAccounts.elms(); i++) {
    std::wstring group = wisaAccounts[i].group;
    bool found = false;
    for(int j = 0; j < wisaGroups.elms(); j++) {
      if(group.compare(wisaGroups[j].name) == 0) {
        found = true;
        break;
      }
    }
    
    if(!found) {
      wisaGroups.New().name = group;
    }    
  }
}

bool wisaImport::readLinesUTF8(std::wifstream * stream) {
  std::wstring line;
  while(std::getline(*stream, line)) {
    tokenize(line);    
  }
  return !wisaAccounts.empty();
}

bool wisaImport::readLinesLatin(std::ifstream* stream) {
  std::string line;
  while(std::getline(*stream, line)) {
    std::wstring converted = boost::locale::conv::to_utf<wchar_t>(line, "Latin1");
    tokenize(converted);
  }
  return !wisaAccounts.empty();
}


bool wisaImport::tokenize(const std::wstring& line) {
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
    wisaAccounts.New().set(elms);
    return true;
  }
  return false;
}

std::string wisaImport::getWisaFile() {
  return wisaFile;
}

void wisaImport::reset() {
  wUpload->clear();
  y::ldap::Server().clear();
  manager->showPage(0);
}

container<wisaImport::wisaAccount> & wisaImport::getWisaAccounts() {
  return wisaAccounts;
}

void wisaImport::wisaAccount::set(std::vector<std::wstring>& line) {
  if(line.size() != 5) assert(false);
  sn = line[0];
  cn = line[1];
  group = line[2];
  date = line[3];
  ID = std::stoi(line[4]);
}

container<wisaImport::wisaGroup> & wisaImport::getWisaGroups() {
  return wisaGroups;
}

void wisaImport::showErrorOnScreen(const std::wstring& message) {
  WCommitChanges->addMessage(message);
}