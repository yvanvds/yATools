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

wisaImport & WisaImport() {
  static wisaImport w;
  return w;
}

/*****************************************************
 * WisaUpload
 * **************************************************/

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

void wisaUpload::clear() {
  cleanUpload();
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

/*****************************************************
 * Wisa Parse File
 * **************************************************/

void wisaParseFile::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>Controleer of dit er ok uit ziet. (Let op de accenten!)</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaParseFile::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText("GeboorteDatum"));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Wisa ID"));
  entries->elementAt(0,0)->setPadding(5);
  entries->elementAt(0,1)->setPadding(5);
  entries->elementAt(0,2)->setPadding(5);
  entries->elementAt(0,3)->setPadding(5);
  entries->elementAt(0,4)->setPadding(5);
  
  container<wisaImport::wisaAccount> & wisaContent = WisaImport().getWisaAccounts();
  
  for(int i = 0; i < wisaContent.elms(); i++) {
    entries->elementAt(i+1, 0)->addWidget(new Wt::WText(wisaContent[i].sn));
    entries->elementAt(i+1, 1)->addWidget(new Wt::WText(wisaContent[i].cn));
    entries->elementAt(i+1, 2)->addWidget(new Wt::WText(wisaContent[i].group));
    entries->elementAt(i+1, 3)->addWidget(new Wt::WText(wisaContent[i].date));
    entries->elementAt(i+1, 4)->addWidget(new Wt::WText(std::to_wstring(wisaContent[i].ID)));
  }
}

/*****************************************************
 * Wisa No ID
 * **************************************************/

void wisaNoID::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>Deze accounts hebben geen Wisa ID.</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaNoID::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText("Wisa ID"));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Verwijder"));
  
  container<y::ldap::account> & accounts = y::ldap::Server().getAccounts();
  int row = 1;
  Wt::WIntValidator * validator = new Wt::WIntValidator(0, 100000);
  
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].group()().compare(L"personeel") == 0) {
      accounts[i].setImportStatus(y::ldap::WI_DISCARD);
    } else if(accounts[i].group()().compare(L"extern") == 0) {
      accounts[i].setImportStatus(y::ldap::WI_DISCARD);
    } else if(accounts[i].group()().compare(L"externmail") == 0) {
      accounts[i].setImportStatus(y::ldap::WI_DISCARD);
    } else if(accounts[i].group()().size() == 0) {
      accounts[i].setImportStatus(y::ldap::WI_DISCARD);
    } else if(accounts[i].wisaID()() == 0 ) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(accounts[i].sn()()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText(accounts[i].cn()()));
      entries->elementAt(row, 2)->addWidget(new Wt::WText(accounts[i].group()()));
      Wt::WLineEdit * wisaEdit = new Wt::WLineEdit();
      wisaEdit->setId(str8(accounts[i].uid()()));
      wisaEdit->setValidator(validator);
      wisaEdit->setStyleClass("alert alert-warning");
      wisaEdit->setHeight(5);
      entries->elementAt(row, 3)->addWidget(wisaEdit);
      Wt::WCheckBox * remove = new Wt::WCheckBox();
      entries->elementAt(row, 4)->addWidget(remove);
      row++;
    }
  }
}

bool wisaNoID::onNext() {
  for(int i = 1; i < entries->rowCount(); i++) {
    Wt::WLineEdit * le = (Wt::WLineEdit*)entries->rowAt(i)->elementAt(3)->widget(0);
    Wt::WCheckBox * cb = (Wt::WCheckBox*)entries->rowAt(i)->elementAt(4)->widget(0);
    if(cb->isChecked()) {
      y::ldap::account & acc = y::ldap::Server().getAccount(y::ldap::UID(strW(le->id())));
      acc.flagForRemoval();
      acc.setImportStatus(y::ldap::WI_DISCARD);
    } else if(le->validate() != Wt::WValidator::Valid) {
      le->setStyleClass("alert alert-danger");
      le->setHeight(5);
      return false;
    } else {
      if(!le->text().empty()) {
        int newID = 0;
        try {
          newID = boost::lexical_cast<int>(le->text());
        } catch (boost::bad_lexical_cast) {
          return false;
        }
        y::ldap::account & acc = y::ldap::Server().getAccount(y::ldap::UID(strW(le->id())));
        acc.wisaID(y::ldap::WISA_ID(newID));
        le->setStyleClass("alert alert-success");
        le->setHeight(5);
      }
    }
  }
  return true;
}

/*****************************************************
 * Wisa Compare File
 * **************************************************/

void wisaCompareFile::setContent(Wt::WVBoxLayout* box) {
  message1 = new Wt::WText();
  box->addWidget(message1);
  message2 = new Wt::WText();
  box->addWidget(message2);
  message3 = new Wt::WText();
  box->addWidget(message3);
  message4 = new Wt::WText();
  box->addWidget(message4);
}

void wisaCompareFile::onShow() {
  // count accounts in wisa file
  container<wisaImport::wisaAccount> & wisaContent = WisaImport().getWisaAccounts();
  std::wstring m1(L"Nieuw bestand bevat ");
  m1 += std::to_wstring(wisaContent.elms());
  m1 += L" accounts.";
  message1->setText(m1);
  
  // load all accounts
  container<y::ldap::account> & accounts = y::ldap::Server().getAccounts();
  int validAccounts = accounts.elms();
  int accountedFor = 0;
  int accountsToRemove = 0;
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].getImportStatus() == y::ldap::WI_DISCARD) {
      validAccounts--;
      if(accounts[i].flaggedForRemoval()) accountsToRemove++;
    } else {
      int wisaID = accounts[i].wisaID()();
      for(int j = 0; j < wisaContent.elms(); j++) {
        if(wisaContent[j].ID == wisaID) {
          wisaContent[j].link = &accounts[i];
          accounts[i].setImportStatus(y::ldap::WI_ACCOUNTED);
          accountedFor++;
        }
      }
    }
  }
  
  std::wstring m2(L"De database bevat ");
  m2 += std::to_wstring(validAccounts);
  m2 += L" accounts.";
  message2->setText(m2);
  
  std::wstring m3(L"Er bestaat een geldige link voor ");
  m3 += std::to_wstring(accountedFor);
  m3 += L" accounts.";
  message3->setText(m3);
  
  std::wstring m4;
  m4 += std::to_wstring(accountsToRemove);
  m4 += L" accounts worden verwijderd.";
  message4->setText(m4);
}

/*****************************************************
 * Wisa Compare Groups
 * **************************************************/

void wisaCompareGroups::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>De volgende klassen worden aangepast.</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaCompareGroups::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText(" "));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Nieuwe Klas"));
  
  container<wisaImport::wisaAccount> & wisaContent = WisaImport().getWisaAccounts();
  int row = 1;
  for(int i = 0; i < wisaContent.elms(); i++) {
    if(!wisaContent[i].link) continue;
    if(wisaContent[i].link->group()().compare(wisaContent[i].group) != 0) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaContent[i].sn));
      entries->elementAt(row, 1)->addWidget(new Wt::WText(wisaContent[i].cn));
      entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].link->group()()));
      entries->elementAt(row, 3)->addWidget(new Wt::WText("=>"));
      entries->elementAt(row, 4)->addWidget(new Wt::WText(wisaContent[i].group));
      row++;
      
      // change name
      wisaContent[i].link->group(y::ldap::GID(wisaContent[i].group));
    }      
  }
}

/*****************************************************
 * Wisa Compare names
 * **************************************************/

void wisaCompareNames::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>De volgende namen worden aangepast.</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaCompareNames::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText("Nieuwe Naam"));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Nieuwe Voornaam"));
  entries->elementAt(0,0)->setPadding(5);
  entries->elementAt(0,1)->setPadding(5);
  entries->elementAt(0,2)->setPadding(5);
  entries->elementAt(0,3)->setPadding(5);
  entries->elementAt(0,4)->setPadding(5);
  
  container<wisaImport::wisaAccount> & wisaContent = WisaImport().getWisaAccounts();
  int row = 1;
  for(int i = 0; i < wisaContent.elms(); i++) {
    if(!wisaContent[i].link) continue;
    if(wisaContent[i].link->sn()().compare(wisaContent[i].sn) != 0 
            || wisaContent[i].link->cn()().compare(wisaContent[i].cn) != 0) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaContent[i].link->sn()()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText(wisaContent[i].link->cn()()));
      entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].group));
      entries->elementAt(row, 3)->addWidget(new Wt::WText(wisaContent[i].sn));
      entries->elementAt(row, 4)->addWidget(new Wt::WText(wisaContent[i].cn));
      row++;
      
      // change name
      wisaContent[i].link->cn(y::ldap::CN(wisaContent[i].cn));
      wisaContent[i].link->sn(y::ldap::SN(wisaContent[i].sn));
      std::wstring fullName(wisaContent[i].cn);
      fullName += L" ";
      fullName += wisaContent[i].sn;
      wisaContent[i].link->fullName(y::ldap::FULL_NAME(fullName));
    }      
  }
}

/*****************************************************
 * Wisa New Groups
 * **************************************************/

void wisaNewGroups::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>Wijzigingen aan klassen.</h4>"));
    
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaNewGroups::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,0)->setPadding(5);
  entries->elementAt(0,1)->addWidget(new Wt::WText("Status"));
  entries->elementAt(0,1)->setPadding(5);
  
  container<y::ldap::group> & groups = y::ldap::Server().getGroups();
  container<wisaImport::wisaGroup> & wisaGroups = WisaImport().getWisaGroups();
  
  int row = 1;
  for(int i = 0; i < groups.elms(); i++) {
    if(groups[i].editable()) {
      groups[i].setImportStatus(y::ldap::WI_DISCARD);
    } else {
      bool found = false;
      for(int j = 0; j < wisaGroups.elms(); j++) {
        if(wisaGroups[j].name.compare(groups[i].cn()()) == 0) {
          groups[i].setImportStatus(y::ldap::WI_ACCOUNTED);
          wisaGroups[j].link = &groups[i];
          found = true;
          break;
        }
      }
      if(!found) {
        groups[i].flagForRemoval();
        entries->elementAt(row, 0)->addWidget(new Wt::WText(groups[i].cn()()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("wordt verwijderd"));
        row++;
      }
    }
  }
  
  for(int i = 0; i < wisaGroups.elms(); i++) {
    if(wisaGroups[i].link == nullptr) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaGroups[i].name));
      entries->elementAt(row, 1)->addWidget(new Wt::WText("wordt toegevoegd"));
      row++;
    }
  }
}

/*****************************************************
 * Wisa Submit
 * **************************************************/

void wisaConfirmSubmit::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>Accounts</h4>"));
  message1 = new Wt::WText();
  box->addWidget(message1);
  message2 = new Wt::WText();
  box->addWidget(message2);
  message3 = new Wt::WText();
  box->addWidget(message3);
  message4 = new Wt::WText();
  box->addWidget(message4);
  message5 = new Wt::WText();
  box->addWidget(message5);
  
  box->addWidget(new Wt::WText("<h4>Klassen</h4>"));
  message6 = new Wt::WText();
  box->addWidget(message6);
  message7 = new Wt::WText();
  box->addWidget(message7);
  message8 = new Wt::WText();
  box->addWidget(message8);
  message9 = new Wt::WText();
  box->addWidget(message9);
  message10 = new Wt::WText();
  box->addWidget(message10);
}

bool wisaConfirmSubmit::onPrevious() {
  WisaImport().reset();
  return false;
}

bool wisaConfirmSubmit::onNext() {
  return true;
}

void wisaConfirmSubmit::onShow() {
  // overwrite buttons
  previousButton->setStyleClass("btn btn-success");
  previousButton->setText("Toch maar niet");
  
  nextButton->setStyleClass("btn btn-danger");
  nextButton->setText("Wijzig Database");
  
  // count accounts in wisa file
  container<wisaImport::wisaAccount> & wisaAccounts = WisaImport().getWisaAccounts();
  std::wstring m1(L"Nieuw bestand bevat ");
  m1 += std::to_wstring(wisaAccounts.elms());
  m1 += L" accounts.";
  message1->setText(m1);
  
  // load all accounts
  container<y::ldap::account> & accounts = y::ldap::Server().getAccounts();
  int validAccounts = accounts.elms();
  int linkedAccounts = 0;
  int accountsToRemove = 0;
  
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].getImportStatus() == y::ldap::WI_DISCARD) {
      validAccounts--;
      if(accounts[i].flaggedForRemoval()) accountsToRemove++;
    } 
  }
  
  for(int i = 0; i < wisaAccounts.elms(); i++) {
    if(wisaAccounts[i].link != nullptr) {
      linkedAccounts++;
    }
  }
  
  int newAccounts = wisaAccounts.elms() - linkedAccounts;
  
  std::wstring m2(L"De database bevat ");
  m2 += std::to_wstring(validAccounts);
  m2 += L" accounts.";
  message2->setText(m2);
  
  std::wstring m3(L"Er bestaat een geldige link voor ");
  m3 += std::to_wstring(linkedAccounts);
  m3 += L" accounts.";
  message3->setText(m3);
  
  std::wstring m4;
  m4 += std::to_wstring(accountsToRemove);
  m4 += L" accounts worden verwijderd.";
  message4->setText(m4);
  
  std::wstring m5;
  m5 += std::to_wstring(newAccounts);
  m5 += L" accounts worden toegevoegd.";
  message5->setText(m5);
  
  // count groups in wisa file
  container<wisaImport::wisaGroup> & wisaGroups = WisaImport().getWisaGroups();
  std::wstring m6(L"Nieuw bestand bevat ");
  m6 += std::to_wstring(wisaGroups.elms());
  m6 += L" klassen.";
  message6->setText(m6);
  
  // load all accounts
  container<y::ldap::group> & groups = y::ldap::Server().getGroups();
  int validGroups = groups.elms();
  int linkedGroups = 0;
  int groupsToRemove = 0;
  
  for(int i = 0; i < groups.elms(); i++) {
    if(groups[i].getImportStatus() == y::ldap::WI_DISCARD) {
      validGroups--;
    } else {
      if(groups[i].flaggedForRemoval()) groupsToRemove++;
    } 
  }
  
  for(int i = 0; i < wisaGroups.elms(); i++) {
    if(wisaGroups[i].link != nullptr) {
      linkedGroups++;
    }
  }
  
  int newGroups = wisaGroups.elms() - linkedGroups;
  
  std::wstring m7(L"De database bevat ");
  m7 += std::to_wstring(validGroups);
  m7 += L" klassen.";
  message7->setText(m7);
  
  std::wstring m8(L"Er bestaat een geldige link voor ");
  m8 += std::to_wstring(linkedGroups);
  m8 += L" klassen.";
  message8->setText(m8);
  
  std::wstring m9;
  m9 += std::to_wstring(groupsToRemove);
  m9 += L" klassen worden verwijderd.";
  message9->setText(m9);
  
  std::wstring m10;
  m10 += std::to_wstring(newGroups);
  m10 += L" klassen worden toegevoegd.";
  message10->setText(m10);
}

/*****************************************************
 * Wisa Import (Main class)
 * **************************************************/

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
  
  if(!readLines(&stream)) {
    // probably the file has another encoding
    // Try again with latin1
    std::locale latin = gen("en_US.iso88591");
    std::wifstream stream2(file);
    stream2.imbue(latin);
    readLines(&stream2);
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

bool wisaImport::readLines(std::wifstream * stream) {
  std::wstring line;
  while(std::getline(*stream, line)) {
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
      wisaAccounts.New().set(elms);
    }
  }
  return !wisaAccounts.empty();
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