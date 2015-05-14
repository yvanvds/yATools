/* 
 * File:   yearbook.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 11:36 AM
 */

#include "yearbook.h"
#include "yearbookDB.h"
#include <Wt/WDate>

yearbook & Yearbook() {
  static yearbook s;
  return s;
}

yearbook::yearbook() : manager(nullptr), account(nullptr) {}

y::gui::stackPageManager * yearbook::get() {
  YearbookDB().loadConfig();
  
  manager = new y::gui::stackPageManager();
  
  ybVerifyAccount = new yearbookVerifyAccount();
  manager->addPage(ybVerifyAccount);
  ybVerifyAccount->showButtons(false, true);
  
  ybQuestion1 = new yearbookQuestion(1);
  manager->addPage(ybQuestion1);
  ybQuestion1->showButtons(true, true);
  
  ybQuestion2 = new yearbookQuestion(2);
  manager->addPage(ybQuestion2);
  ybQuestion2->showButtons(true, true);
  
  ybQuestion3 = new yearbookQuestion(3);
  manager->addPage(ybQuestion3);
  ybQuestion3->showButtons(true, true);
  
  ybQuestion4 = new yearbookQuestion(4);
  manager->addPage(ybQuestion4);
  ybQuestion4->showButtons(true, true);
  
  ybPhoto = new yearbookPhoto();
  manager->addPage(ybPhoto);
  ybPhoto->showButtons(true, true);
  
  ybDone = new yearbookDone();
  manager->addPage(ybDone);
  ybDone->showButtons(true, false);
  
  return manager;
}

void yearbook::setAccount(y::ldap::account * account) {
  this->account = account;
  if(!YearbookDB().loadUser(str8(account->uid()()))) {
    YearbookDB().ID(account->uid()());    
    YearbookDB().name(account->cn()());
    YearbookDB().surname(account->sn()());
    YearbookDB().servername(account->fullName()());
    YearbookDB().group(account->group()());
    Wt::WDate date;
    date.setDate(account->birthDay().getYear(),
                 account->birthDay().getMonth(),
                 account->birthDay().getDay()
            );
    YearbookDB().birthday(date);
  }
  ybVerifyAccount->onShow();
}