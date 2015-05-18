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
  scroll->setMaximumSize(750, 500);
  
  download = new fileDownload(entries);
}

void WisaShowErrorOnScreen(const string & message) {
  WisaImport().showErrorOnScreen(message);
}


void commitThreadFunc(wisaCommitChanges * caller) {
  y::utils::Log().useFunction(&WisaShowErrorOnScreen);
  // create groups
  container<wisaImport::wisaGroup> & wisaGroups = WisaImport().getWisaGroups();
  for (int i = 0; i < wisaGroups.elms(); i++) {
    if(wisaGroups[i].link == nullptr) {
      y::ldap::group & g = y::ldap::Server().getGroup(wisaGroups[i].name, false);
      g.flagForCommit();
      string message("Klas ");
      message += wisaGroups[i].name;
      message += " werd toegevoegd";
      caller->addMessage(message);
    }
  }
  
  container<wisaImport::wisaAccount> & wisaAccounts = WisaImport().getWisaAccounts();
  for (int i = 0; i < wisaAccounts.elms(); i++) {
    wisaImport::wisaAccount & account = wisaAccounts[i];
    if(account.link == nullptr) {
      // create new account
      string cn(account.cn);
      string sn(account.sn);
      y::ldap::GID gid(account.group);
      y::ldap::DATE date(account.date, true);
      y::ldap::WISA_ID id(account.ID);
      string password(y::utils::Security().makePassword(8));
      
      
      y::ldap::account & acc = y::admin::User().add(cn, sn, gid, date, id, y::ldap::PASSWORD(password));
      string message("Account voor ");
      message += acc.fullName()();
      message += " werd toegevoegd";
      caller->addMessage(message);
      
      message = account.group;
      message += " ";
      message += acc.fullName()();
      caller->addNewAccountMessage(message);
      message = "Login: ";
      message += acc.uid()();
      caller->addNewAccountMessage(message);
      message = "Wachtwoord: ";
      message += password;
      caller->addNewAccountMessage(message);
      message = "Mail Adres: ";
      message += acc.mail()();
      caller->addNewAccountMessage(message);
      message = " ";
      caller->addNewAccountMessage(message);
      caller->addNewAccountMessage(message);
      
    } else {
      // account exists, but may not be up to date
      bool namechanged = false;
      if(account.link->sn() != account.sn) {
        account.link->sn(account.sn);
        string message("Naam voor ");
        message += account.link->fullName()();
        message += " werd gewijzigd";
        caller->addMessage(message);
        namechanged = true;
      }
      if(account.link->cn() != account.cn) {
        account.link->cn(account.cn);
        string message("Voornaam voor ");
        message += account.link->fullName()();
        message += " werd gewijzigd";
        caller->addMessage(message);
        namechanged = true;
      }
      
      if(namechanged) {
        string name(account.cn);
        name += " ";
        name += account.sn;
        account.link->fullName(y::ldap::FULL_NAME(name));
      }
      
      if(account.link->wisaID()() != account.ID) {
        account.link->wisaID(y::ldap::WISA_ID(account.ID));
        string message("Wisa ID voor ");
        message += account.link->fullName()();
        message += " werd gewijzigd";
        caller->addMessage(message);
      }
      
      if(account.link->group()() != account.group) {
        y::ldap::group & oldGroup = y::ldap::Server().getGroup(account.link->group()(), false);
        oldGroup.removeMember(account.link->dn()());
        y::ldap::group & newGroup = y::ldap::Server().getGroup(account.group, false);
        newGroup.addMember(account.link->dn()());
        account.link->group(y::ldap::GID(account.group));
        string message("Klas voor ");
        message += account.link->fullName()();
        message += " werd gewijzigd";
        caller->addMessage(message);
      }
      
      y::ldap::DATE date(account.date, true);
      string message("birthday: ");
      message += account.link->birthDay()();
      message += " ";
      message += date();
      caller->addMessage(message);
      if(account.link->birthDay() != date) {
        account.link->birthDay(date);
        string message("Verjaardag voor ");
        message += account.link->fullName()();
        message += " werd gewijzigd";
        caller->addMessage(message);
      }
    }
  }
  
  container<y::ldap::account> & ldapAcc = y::ldap::Server().getAccounts();
  for(int i = 0; i < ldapAcc.elms(); i++) {
    if(ldapAcc[i].flaggedForRemoval()) {
      y::admin::User().remove(ldapAcc[i]);
      string message("Gebruiker ");
      message += ldapAcc[i].fullName()();
      message += " werd verwijderd";
      caller->addMessage(message);
    }
  }
  y::ldap::Server().commitChanges();
  caller->addMessage("Alle wijzigingen zijn voltooid.", true);
  
  y::utils::Log().useFunction();
}

void wisaCommitChanges::onShow() {
  
  entries->clear();
  streamCounter = 0;
  rowCounter = 0;
  
  entries->elementAt(rowCounter,0)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(rowCounter,0)->setPadding(5);
  rowCounter++;
  
  WisaImport().getApplication()->enableUpdates();
  
  std::thread t(commitThreadFunc, this);
  t.detach();
  
}


void wisaCommitChanges::addMessage(const string& message, bool lastUpdate) {
  Wt::WApplication::UpdateLock lock(WisaImport().getApplication());
  if(lock) {
    entries->elementAt(rowCounter,0)->addWidget(new Wt::WText(message.wt()));
    entries->elementAt(rowCounter,0)->setPadding(5);
    rowCounter++;
    streamCounter++;
    if(streamCounter == 10) {
      WisaImport().getApplication()->triggerUpdate();
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
      WisaImport().getApplication()->triggerUpdate();
    }
  }  
}

void wisaCommitChanges::addNewAccountMessage(const string& message) {
  download->addMessage(message);
}

bool wisaCommitChanges::onNext() {
  
  return false;
}
