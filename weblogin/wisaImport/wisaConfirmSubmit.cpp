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
  parentObject->reset();
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
  container<wisaImport::wisaAccount> & wisaAccounts = parentObject->getWisaAccounts();
  string m1("Nieuw bestand bevat ");
  m1 += wisaAccounts.elms();
  m1 += " accounts.";
  message1->setText(m1.wt());
  
  // load all accounts
  ACCOUNTS & accounts = parentObject->ldap()->getAccounts();
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
  
  string m2("De database bevat ");
  m2 += validAccounts;
  m2 += " accounts.";
  message2->setText(m2.wt());
  
  string m3("Er bestaat een geldige link voor ");
  m3 += linkedAccounts;
  m3 += " accounts.";
  message3->setText(m3.wt());
  
  string m4;
  m4 += accountsToRemove;
  m4 += " accounts worden verwijderd.";
  message4->setText(m4.wt());
  
  string m5;
  m5 += newAccounts;
  m5 += " accounts worden toegevoegd.";
  message5->setText(m5.wt());
  
  // count groups in wisa file
  container<wisaImport::wisaGroup> & wisaGroups = parentObject->getWisaGroups();
  string m6("Nieuw bestand bevat ");
  m6 += wisaGroups.elms();
  m6 += " klassen.";
  message6->setText(m6.wt());
  
  // load all accounts
  GROUPS & groups = parentObject->ldap()->getGroups();
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
  
  string m7("De database bevat ");
  m7 += validGroups;
  m7 += " klassen.";
  message7->setText(m7.wt());
  
  string m8("Er bestaat een geldige link voor ");
  m8 += linkedGroups;
  m8 += " klassen.";
  message8->setText(m8.wt());
  
  string m9;
  m9 += groupsToRemove;
  m9 += " klassen worden verwijderd.";
  message9->setText(m9.wt());
  
  string m10;
  m10 += newGroups;
  m10 += " klassen worden toegevoegd.";
  message10->setText(m10.wt());
}
