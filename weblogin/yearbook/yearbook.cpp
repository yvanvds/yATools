/* 
 * File:   yearbook.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 11:36 AM
 */

#include "yearbook.h"
#include "yearbookDB.h"
#include <Wt/WDate>


yearbook::yearbook(yearbookDB * ptr) : db(ptr), manager(nullptr), account(nullptr) {}

y::gui::stackPageManager * yearbook::get() { 
  manager = new y::gui::stackPageManager();
  this->addChild(manager);
  /*
  ybVerifyAccount = new yearbookVerifyAccount(db);
  manager->addPage(ybVerifyAccount);
  ybVerifyAccount->showButtons(false, true);
  
  ybQuestion1 = new yearbookQuestion(1, db);
  manager->addPage(ybQuestion1);
  ybQuestion1->showButtons(true, true);
  
  ybQuestion2 = new yearbookQuestion(2, db);
  manager->addPage(ybQuestion2);
  ybQuestion2->showButtons(true, true);
  
  ybQuestion3 = new yearbookQuestion(3, db);
  manager->addPage(ybQuestion3);
  ybQuestion3->showButtons(true, true);
  
  ybQuestion4 = new yearbookQuestion(4, db);
  manager->addPage(ybQuestion4);
  ybQuestion4->showButtons(true, true);
  
  ybPhoto = new yearbookPhoto(db);
  manager->addPage(ybPhoto);
  ybPhoto->showButtons(true, true);
  
  ybDone = new yearbookDone(db);
  manager->addPage(ybDone);
  ybDone->showButtons(true, false);
  */
  return manager;
}

void yearbook::setAccount(y::ldap::account * account) {
  this->account = account;
  if(!db->loadUser(account->uid()())) {
    db->ID(account->uid()());    
    db->name(account->cn());
    db->surname(account->sn());
    db->servername(account->fullName()());
    db->group(account->group()());
    Wt::WDate date;
    date.setDate(account->birthDay().getYear(),
                 account->birthDay().getMonth(),
                 account->birthDay().getDay()
            );
    db->birthday(date);
  }
  ybVerifyAccount->onShow();
}