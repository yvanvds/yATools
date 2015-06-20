/* 
 * File:   yearbook.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 11:36 AM
 */

#include "yearbook.h"
#include "yearbookDB.h"
#include <Wt/WDate>


yearbook::yearbook(yearbookDB * ptr) : db(ptr), account(nullptr) {
  
  ybVerifyAccount = new yearbookVerifyAccount(db);
  addPage(ybVerifyAccount);
  ybVerifyAccount->showButtons(false, true);
  
  
  ybQuestion1 = new yearbookQuestion(1, db);
  addPage(ybQuestion1);
  ybQuestion1->showButtons(true, true);
  
  ybQuestion2 = new yearbookQuestion(2, db);
  addPage(ybQuestion2);
  ybQuestion2->showButtons(true, true);
  
  ybQuestion3 = new yearbookQuestion(3, db);
  addPage(ybQuestion3);
  ybQuestion3->showButtons(true, true);
  
  ybQuestion4 = new yearbookQuestion(4, db);
  addPage(ybQuestion4);
  ybQuestion4->showButtons(true, true);
  
  ybPhoto = new yearbookPhoto(db);
  addPage(ybPhoto);
  ybPhoto->showButtons(true, true);
  
  ybDone = new yearbookDone(db);
  addPage(ybDone);
  ybDone->showButtons(true, false);
  
}

void yearbook::setAccount(y::ldap::account * account) {
  this->account = account;
  if(!db->loadUser(account->uid().get())) {
    db->ID(account->uid().get());    
    db->name(account->cn().get());
    db->surname(account->sn().get());
    db->servername(account->fullName().get());
    db->group(account->schoolClass().get());
    Wt::WDate date;
    date.setDate(account->birthDay().getYear(),
                 account->birthDay().getMonth(),
                 account->birthDay().getDay()
            );
    db->birthday(date);
  }
  ybVerifyAccount->onShow();
}