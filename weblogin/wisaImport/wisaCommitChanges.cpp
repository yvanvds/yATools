/* 
 * File:   wisaCommitChanges.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:50 PM
 */

#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include <thread>
#include <Wt/WPushButton>
#include <Wt/WLink>
#include "wisaCommitChanges.h"
#include "utils/container.h"
#include "../wisaImport.h"
#include "ldap/group.h"
#include "ldap/server.h"
#include "utils/security.h"
#include "utils/convert.h"
#include "utils/log.h"
#include "utils/string.h"
#include "admin/userAdmin.h"
#include <boost/algorithm/string.hpp>

fileDownload::fileDownload(Wt::WObject* parent)
: Wt::WResource(parent) {
  suggestFileName("newUsers.txt");
}

fileDownload::~fileDownload() {
  beingDeleted();
}

void fileDownload::handleRequest(const Wt::Http::Request& request, Wt::Http::Response& response) {
  Wt::Http::ResponseContinuation * continuation = request.continuation();

  int iteration = continuation ? boost::any_cast<int>(continuation->data()) : 0;
  if(iteration == 0) {
    response.setMimeType("plain/text");        
  }

  int last = std::min(iteration + 50, messages.elms());
  for (int i = iteration; i < last; ++i) {
    response.out() << messages[i] << std::endl;
  }

  if(last < messages.elms()) {
    continuation = response.createContinuation();
    continuation->setData(last);
  }
}

void fileDownload::addMessage(const string& message) {
  messages.New() = message;
}

bool fileDownload::empty() {
  return messages.empty();
}

wisaCommitChanges::~wisaCommitChanges() {
  if(download != nullptr) {
    delete download;
  }
}

void wisaCommitChanges::setContent(Wt::WVBoxLayout* box) {
  this->box = box;
  progress = new Wt::WText("<h4>Wijzigingen worden uitgevoerd...</h4>");
  box->addWidget(progress);
    
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 450);
  
  download = new fileDownload(entries);
}

void commitThreadFunc(wisaCommitChanges * caller) {
  // create groups
  /*container<wisaImport::wisaClass> & wisaGroups = caller->getParentObject()->getWisaGroups();
  for (int i = 0; i < wisaGroups.elms(); i++) {
    if(wisaGroups[i].link == nullptr) {
      y::ldap::group & g = caller->getParentObject()->ldap()->getGroup(CN(wisaGroups[i].name), false);
      g.flagForCommit();
      string message("Klas ");
      message += wisaGroups[i].name;
      message += " werd toegevoegd";
      caller->addMessage(message);
    }
  }
  
  y::admin::userAdmin admin(caller->getParentObject()->ldap());
  
  container<wisaImport::wisaAccount> & wisaAccounts = caller->getParentObject()->getWisaAccounts();
  for (int i = 0; i < wisaAccounts.elms(); i++) {
    wisaImport::wisaAccount & account = wisaAccounts[i];
    if(account.link == nullptr) {
      // create new account
      CN cn(account.cn);
      SN sn(account.sn);
      SCHOOLCLASS schoolClass(account.schoolClass);
      ROLE gid(ROLE::STUDENT);
      DATE date(account.date, true);
      WISA_ID id(account.ID);
      string password(y::utils::Security().makePassword(8));
      
      
      y::ldap::account & acc = admin.add(cn, sn, gid, schoolClass, date, id, PASSWORD(password));
      string message("Account voor ");
      message += acc.fullName().get();
      message += " werd toegevoegd";
      caller->addMessage(message);
      
      message = account.schoolClass;
      message += " ";
      message += acc.fullName().get();
      caller->addNewAccountMessage(message);
      message = "Login: ";
      message += acc.uid().get();
      caller->addNewAccountMessage(message);
      message = "Wachtwoord: ";
      message += password;
      caller->addNewAccountMessage(message);
      message = "Mail Adres: ";
      message += acc.mail().get();
      caller->addNewAccountMessage(message);
      message = " ";
      caller->addNewAccountMessage(message);
      caller->addNewAccountMessage(message);
      
    } else {
      // account exists, but may not be up to date
      bool namechanged = false;
      if(account.link->sn() != SN(account.sn)) {
        account.link->sn(SN(account.sn));
        string message("Naam voor ");
        message += account.link->fullName().get();
        message += " werd gewijzigd";
        caller->addMessage(message);
        namechanged = true;
      }
      if(account.link->cn() != CN(account.cn)) {
        account.link->cn(CN(account.cn));
        string message("Voornaam voor ");
        message += account.link->fullName().get();
        message += " werd gewijzigd";
        caller->addMessage(message);
        namechanged = true;
      }
      
      if(namechanged) {
        string name(account.cn);
        name += " ";
        name += account.sn;
        account.link->fullName(FULL_NAME(name));
      }
      
      if(account.link->wisaID().get() != account.ID) {
        account.link->wisaID(WISA_ID(account.ID));
        string message("Wisa ID voor ");
        message += account.link->fullName().get();
        message += " werd gewijzigd";
        caller->addMessage(message);
      }
      
      if(account.link->schoolClass() != SCHOOLCLASS(account.schoolClass)) {
        y::ldap::schoolClass & oldClass = caller->getParentObject()->ldap()->getClass(account.link->schoolClass()(), false);
        oldClass.removeMember(account.link->dn()());
        y::ldap::group & newGroup = caller->getParentObject()->ldap()->getGroup(account.group, false);
        newGroup.addMember(account.link->dn()());
        account.link->group(y::ldap::GID(account.group));
        string message("Klas voor ");
        message += account.link->fullName()();
        message += " werd gewijzigd";
        caller->addMessage(message);
      }
      
      DATE date(account.date, true);
      if(account.link->birthDay() != date) {
        account.link->birthDay(date);
        string message("Verjaardag voor ");
        message += account.link->fullName().get();
        message += " werd gewijzigd";
        caller->addMessage(message);
      }
    }
  }
  
  ACCOUNTS & ldapAcc = caller->getParentObject()->ldap()->getAccounts();
  for(int i = 0; i < ldapAcc.elms(); i++) {
    if(ldapAcc[i].flaggedForRemoval()) {
      admin.remove(ldapAcc[i]);
      string message("Gebruiker ");
      message += ldapAcc[i].fullName().get();
      message += " werd verwijderd";
      caller->addMessage(message);
    }
  }
  caller->getParentObject()->ldap()->commitChanges();
  caller->addMessage("Alle wijzigingen zijn voltooid.", true);
  
  y::utils::Log().useFunction();*/
}

void wisaCommitChanges::onShow() {
  
  entries->clear();
  streamCounter = 0;
  rowCounter = 0;
  
  entries->elementAt(rowCounter,0)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(rowCounter,0)->setPadding(5);
  rowCounter++;
  
  parentObject->getApplication()->enableUpdates();
  
  std::thread t(commitThreadFunc, this);
  t.detach();
  
}


void wisaCommitChanges::addMessage(const string& message, bool lastUpdate) {
  Wt::WApplication::UpdateLock lock(parentObject->getApplication());
  if(lock) {
    entries->elementAt(rowCounter,0)->addWidget(new Wt::WText(message.wt()));
    entries->elementAt(rowCounter,0)->setPadding(5);
    rowCounter++;
    streamCounter++;
    if(streamCounter == 10) {
      parentObject->getApplication()->triggerUpdate();
      streamCounter = 0;
    }
    
    if(lastUpdate) {
      if(!download->empty()) {
        Wt::WPushButton * button = new Wt::WPushButton();
        box->addWidget(button);
      
        button->setStyleClass("btn btn-success");
        button->setText("Download Nieuwe Logins");
        button->setLink(Wt::WLink(download));  
      }
      
      progress->setText("<h4>Klaar</h4>");
      parentObject->getApplication()->triggerUpdate();
    }
  }  
}

void wisaCommitChanges::addNewAccountMessage(const string& message) {
  download->addMessage(message);
}

bool wisaCommitChanges::onNext() {
  
  return false;
}
