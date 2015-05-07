/* 
 * File:   wisaCompareFile.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:22 PM
 */

#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include "wisaCompareFile.h"
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"


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