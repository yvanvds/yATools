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
  
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  entries = new Wt::WTable();
  entries->setHeaderCount(0);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 200);
  
}

void wisaCompareFile::onShow() {
  // count accounts in wisa file
  container<wisaImport::wisaAccount> & wisaContent = parentObject->getWisaAccounts();
  string m1("Nieuw bestand bevat ");
  m1 += wisaContent.elms();
  m1 += " accounts.";
  message1->setText(m1.wt());
  
  // load all accounts
  ACCOUNTS & accounts = parentObject->ldap()->getAccounts();
  int validAccounts = accounts.elms();
  int accountedFor = 0;
  int accountsToRemove = 0;
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].getImportStatus() == WI_DISCARD) {
      validAccounts--;
      if(accounts[i].flaggedForRemoval()) {
        string s(accounts[i].fullName().get() + " wordt verwijderd.");
        entries->elementAt(accountsToRemove,0)->addWidget(new Wt::WText(s.wt()));
        accountsToRemove++;
      }
    } else {
      for(int j = 0; j < wisaContent.elms(); j++) {
        if(wisaContent[j].wisaID == accounts[i].wisaID()) {
          wisaContent[j].link = &accounts[i];
          accounts[i].setImportStatus(WI_ACCOUNTED);
          accountedFor++;
        }
      }
      if(accounts[i].getImportStatus() != WI_ACCOUNTED) {
        string s(accounts[i].fullName().get() + " wordt verwijderd.");
        entries->elementAt(accountsToRemove,0)->addWidget(new Wt::WText(s.wt()));
        accounts[i].flagForRemoval();
        accountsToRemove++;
      }
    }
  }
  
  string m2("De database bevat ");
  m2 += validAccounts;
  m2 += " accounts.";
  message2->setText(m2.wt());
  
  string m3("Er bestaat een geldige link voor ");
  m3 += accountedFor;
  m3 += " accounts.";
  message3->setText(m3.wt());
  
  string m4;
  m4 += accountsToRemove;
  m4 += " accounts worden verwijderd.";
  message4->setText(m4.wt());
}

bool wisaCompareFile::onNext() {
  parentObject->showNewPage(W_COMPARENAMES);
  return false;
}

bool wisaCompareFile::onPrevious() {
  parentObject->showNewPage(W_NOID);
  return false;
}