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
    response.out() << str8(messages[i]) << std::endl;
  }

  if(last < messages.elms()) {
    continuation = response.createContinuation();
    continuation->setData(last);
  }
}

void fileDownload::addMessage(const std::wstring& message) {
  messages.New() = message;
}

void wisaCommitChanges::setContent(Wt::WVBoxLayout* box) {
  this->box = box;
  box->addWidget(new Wt::WText("<h4>Wijzigingen worden uitgevoerd...</h4>"));
    
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

void WisaShowErrorOnScreen(const std::wstring & message) {
  WisaImport().showErrorOnScreen(message);
}


void commitThreadFunc(wisaCommitChanges * caller) {
  y::utils::Log().useFunction(&WisaShowErrorOnScreen);
  // create groups
  container<wisaImport::wisaGroup> & wisaGroups = WisaImport().getWisaGroups();
  for (int i = 0; i < wisaGroups.elms(); i++) {
    if(wisaGroups[i].link == nullptr) {
      y::ldap::group & g = y::ldap::Server().getGroup(y::ldap::CN(wisaGroups[i].name), false);
      g.flagForCommit();
      std::wstring message(L"Klas ");
      message += wisaGroups[i].name;
      message += L" werd toegevoegd";
      caller->addMessage(message);
    }
  }
  
  container<wisaImport::wisaAccount> & wisaAccounts = WisaImport().getWisaAccounts();
  for (int i = 0; i < wisaAccounts.elms(); i++) {
    wisaImport::wisaAccount & account = wisaAccounts[i];
    if(account.link == nullptr) {
      // create new account
      y::ldap::CN cn(account.cn);
      y::ldap::SN sn(account.sn);
      y::ldap::GID gid(account.group);
      y::ldap::DATE date(account.date, true);
      y::ldap::WISA_ID id(account.ID);
      std::wstring password(strW(y::utils::Security().makePassword(8)));
      
      
      y::ldap::account & acc = y::admin::User().add(cn, sn, gid, date, id, y::ldap::PASSWORD(password));
      std::wstring message(L"Account voor ");
      message += acc.fullName()();
      message += L" werd toegevoegd";
      caller->addMessage(message);
      
      message = account.group;
      message += L" ";
      message += acc.fullName()();
      caller->addNewAccountMessage(message);
      message = L"Login: ";
      message += acc.uid()();
      caller->addNewAccountMessage(message);
      message = L"Wachtwoord: ";
      message += password;
      caller->addNewAccountMessage(message);
      message = L"Mail Adres: ";
      message += acc.mail()();
      caller->addNewAccountMessage(message);
      message = L" ";
      caller->addNewAccountMessage(message);
      caller->addNewAccountMessage(message);
      
    } else {
      // account exists, but may not be up to date
      bool namechanged = false;
      if(account.link->sn()().compare(account.sn) != 0) {
        account.link->sn(y::ldap::SN(account.sn));
        std::wstring message(L"Naam voor ");
        message += account.link->fullName()();
        message += L" werd gewijzigd";
        caller->addMessage(message);
        namechanged = true;
      }
      if(account.link->cn()().compare(account.cn) != 0) {
        account.link->cn(y::ldap::CN(account.cn));
        std::wstring message(L"Voornaam voor ");
        message += account.link->fullName()();
        message += L" werd gewijzigd";
        caller->addMessage(message);
        namechanged = true;
      }
      
      if(namechanged) {
        std::wstring name(account.cn);
        name += L" ";
        name += account.sn;
        account.link->fullName(y::ldap::FULL_NAME(name));
      }
      
      if(account.link->wisaID()() != account.ID) {
        account.link->wisaID(y::ldap::WISA_ID(account.ID));
        std::wstring message(L"Wisa ID voor ");
        message += account.link->fullName()();
        message += L" werd gewijzigd";
        caller->addMessage(message);
      }
      if(account.link->group()().compare(account.group)) {
        y::ldap::group & oldGroup = y::ldap::Server().getGroup(y::ldap::CN(account.link->group()()), false);
        oldGroup.removeMember(account.link->dn()());
        y::ldap::group & newGroup = y::ldap::Server().getGroup(y::ldap::CN(account.group), false);
        newGroup.addMember(account.link->dn()());
        account.link->group(y::ldap::GID(account.group));
        std::wstring message(L"Klas voor ");
        message += account.link->fullName()();
        message += L" werd gewijzigd";
        caller->addMessage(message);
      }        
    }
  }
  
  container<y::ldap::account> & ldapAcc = y::ldap::Server().getAccounts();
  for(int i = 0; i < ldapAcc.elms(); i++) {
    if(ldapAcc[i].flaggedForRemoval()) {
      y::admin::User().remove(ldapAcc[i]);
      std::wstring message(L"Gebruiker ");
      message += ldapAcc[i].fullName()();
      message += L" werd verwijderd";
      caller->addMessage(message);
    }
  }
  y::ldap::Server().commitChanges();
  caller->addMessage(L"Alle wijzigingen zijn voltooid.", true);
  
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


void wisaCommitChanges::addMessage(const std::wstring& message, bool lastUpdate) {
  Wt::WApplication::UpdateLock lock(WisaImport().getApplication());
  if(lock) {
    entries->elementAt(rowCounter,0)->addWidget(new Wt::WText(message));
    entries->elementAt(rowCounter,0)->setPadding(5);
    rowCounter++;
    streamCounter++;
    if(streamCounter == 10) {
      WisaImport().getApplication()->triggerUpdate();
      streamCounter = 0;
    }
    if(lastUpdate) {
      Wt::WPushButton * button = new Wt::WPushButton();
      box->addWidget(button);
      
      button->setStyleClass("btn btn-success");
      button->setText("Download lijst");
      button->setLink(Wt::WLink(download));    
      WisaImport().getApplication()->triggerUpdate();
    }
  }  
}

void wisaCommitChanges::addNewAccountMessage(const std::wstring& message) {
  download->addMessage(message);
}

bool wisaCommitChanges::onNext() {
  
  return false;
}
