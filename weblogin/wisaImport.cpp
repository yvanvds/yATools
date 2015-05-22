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
#include <Wt/WTabWidget>
#include "base/stackPage.h"


void wisaImport::create() {
  setTitle("<h3>Wisa Import</h3>");
  setStyleClass("panel panel-primary");
  setMaximumSize(800, 800);
  
  tabs = new Wt::WTabWidget();
  this->setCentralWidget(tabs);
  
  wUpload = new wisaUpload(this);
  tabs->addTab(wUpload, "Upload");
  
  WParseFile = new wisaParseFile(this); 
  tabs->addTab(WParseFile, "Accounts");
  /*
  WNoID = new wisaNoID(this); 
  manager->addPage(WNoID);
  WNoID->showButtons(false, true);
  
  WCompareFile = new wisaCompareFile(this);
  manager->addPage(WCompareFile);
  WCompareFile->showButtons(false, true);
  
  WCompareGroups = new wisaCompareGroups(this);
  manager->addPage(WCompareGroups);
  WCompareGroups->showButtons(false, true);
  
  WCompareNames = new wisaCompareNames(this);
  manager->addPage(WCompareNames);
  WCompareNames->showButtons(false, true);
  
  WNewGroups = new wisaNewGroups(this);
  manager->addPage(WNewGroups);
  WNewGroups->showButtons(false, true);
  
  WConfirmSubmit = new wisaConfirmSubmit(this);
  manager->addPage(WConfirmSubmit);
  WConfirmSubmit->showButtons(true, true);
  
  WCommitChanges = new wisaCommitChanges(this);
  manager->addPage(WCommitChanges);
  WCommitChanges->showButtons(false, false);*/
}

void wisaImport::setWisaFile(const string& file) {
  wisaFile = file;
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
  
  // read groups
  wisaGroups.clear();
  
  for(int i = 0; i < wisaAccounts.elms(); i++) {
    string group = wisaAccounts[i].group;
    bool found = false;
    for(int j = 0; j < wisaGroups.elms(); j++) {
      if(group == wisaGroups[j].name) {
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

string wisaImport::getWisaFile() {
  return wisaFile;
}

void wisaImport::reset() {
  wUpload->clear();
  ldapServer->clear();
  //showPage(0);
}

container<wisaImport::wisaAccount> & wisaImport::getWisaAccounts() {
  return wisaAccounts;
}

void wisaImport::wisaAccount::set(std::vector<std::wstring>& line) {
  if(line.size() != 5) assert(false);
  sn = string(line[0]);
  cn = string(line[1]);
  group = string(line[2]);
  date = string(line[3]);
  ID = std::stoi(line[4]);
}

container<wisaImport::wisaGroup> & wisaImport::getWisaGroups() {
  return wisaGroups;
}

void wisaImport::showErrorOnScreen(const string& message) {
  WCommitChanges->addMessage(message);
}

void wisaImport::gotoTab(WISA_TAB id) {
  switch(id) {
    case WISA_TAB_UPLOAD: tabs->setCurrentIndex(tabs->indexOf(wUpload)); break;
    case WISA_TAB_PARSE : tabs->setCurrentIndex(tabs->indexOf(WParseFile)); break;
    
  }
}