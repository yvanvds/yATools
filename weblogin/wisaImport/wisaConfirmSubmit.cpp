/* 
 * File:   wisaConfirmSubmit.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:49 PM
 */

#include "wisaConfirmSubmit.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include <Wt/WPushButton>
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"

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
