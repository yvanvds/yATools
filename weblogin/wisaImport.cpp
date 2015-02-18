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
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include "wisaImport.h"
#include "utils/convert.h"

wisaImport & WisaImport() {
  static wisaImport w;
  return w;
}

wisaUpload::wisaUpload() : box(nullptr), fileUpload(nullptr) {}

void wisaUpload::setContent(Wt::WVBoxLayout* box) {
  this->box = box;
  
  cleanUpload();

  message = new Wt::WText("Kies een wisa export bestand.");
  message->setStyleClass("alert alert-info");
  box->addWidget(message);
}

void wisaUpload::cleanUpload() {
  if(fileUpload && box) {
    box->removeWidget(fileUpload);
  }
  
  fileUpload = new Wt::WFileUpload();
  fileUpload->setFileTextSize(1000);
  fileUpload->setProgressBar(new Wt::WProgressBar());
  fileUpload->changed().connect(this, &wisaUpload::uploadFunc);
  fileUpload->fileTooLarge().connect(this, &wisaUpload::fileTooLargeFunc);
  fileUpload->uploaded().connect(this, &wisaUpload::uploadedFunc);
  if(box) box->insertWidget(0, fileUpload);
}

void wisaUpload::uploadFunc() {
  fileUpload->upload();
}

void wisaUpload::fileTooLargeFunc() {
  message->setText("This file is too large");
  message->setStyleClass("alert alert-danger");
}

void wisaUpload::uploadedFunc() {
  WisaImport().setWisaFile(fileUpload->spoolFileName());
  parent->showPage(pageIndex + 1);
}

void wisaUpload::onShow() {
  cleanUpload();
}

void wisaParseFile::setContent(Wt::WVBoxLayout* box) {
  filename = new Wt::WText();
  box->addWidget(filename);
}

void wisaParseFile::onShow() {
  std::wstring content;
  container<wisaImport::wisaEntry> wisaContent = WisaImport().getWisaContents();
  
  for(int i = 0; i < wisaContent.elms(); i++) {
    content += L"<p>";
    content += wisaContent[i].cn;
    content += L" ";
    content += wisaContent[i].sn;
    content += L" | ";
    content += wisaContent[i].group;
    content += L" | ";
    content += wisaContent[i].date;
    content += L" | ";
    content += wisaContent[i].ID;
    content += L"</p>";
  }
  filename->setText(content);
}

y::gui::stackPageManager * wisaImport::get() {
  manager = new y::gui::stackPageManager();  
  wUpload = new wisaUpload();
  manager->addPage(wUpload);
  wUpload->showButtons(false, false);
  
  WParseFile = new wisaParseFile(); 
  manager->addPage(WParseFile);
  WParseFile->showButtons(true, true);
  return manager;
}

void wisaImport::setWisaFile(const std::string& file) {
  wisaFile = file;
  wisaContents.clear();
  
  // get lines from file
  std::wifstream ifile(file);
  ifile.imbue(std::locale("en_US.UTF-8"));
  
  std::wstring line;
  while(std::getline(ifile, line)) {
    // tokenize each line
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
      wisaContents.New().set(elms);
    }
  }
}

std::string wisaImport::getWisaFile() {
  return wisaFile;
}

container<wisaImport::wisaEntry> & wisaImport::getWisaContents() {
  return wisaContents;
}

void wisaImport::wisaEntry::set(std::vector<std::wstring>& line) {
  if(line.size() != 5) assert(false);
  cn = line[0];
  sn = line[1];
  group = line[2];
  date = line[3];
  ID = line[4];
}