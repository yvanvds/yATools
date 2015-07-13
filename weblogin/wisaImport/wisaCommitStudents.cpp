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
#include "admintools.h"
#include "ldap/account.h"
#include "wisaCommitStudents.h"
#include "../wisaImport.h"

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

wisaCommitStudents::~wisaCommitStudents() {
  if(download != nullptr) {
    delete download;
  }
}

void wisaCommitStudents::setContent(Wt::WVBoxLayout* box) {
  this->box = box;
  progress = new Wt::WText("<h4>Wijzigingen worden uitgevoerd...</h4>");
  box->addWidget(progress);
    
  waitImage = new Wt::WImage();
  waitImage->setImageLink(Wt::WLink("http://apps.sanctamaria-aarschot.be/weblogin/site_resources/wait.gif"));
  waitImage->resize(137,100);
  imageContainer = new Wt::WContainerWidget();
  imageContainer->addWidget(waitImage);
  box->addWidget(imageContainer);
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 350);
  
  download = new fileDownload(entries);
}

void commitThreadFunc(wisaCommitStudents * caller) {
  using std::placeholders::_1;
  y::utils::Log().bind(std::bind(&wisaCommitStudents::addMessage, caller, _1));
  
  y::admin::userAdmin admin(caller->getParentObject()->ldap());
  container<wisaImport::wisaAccount> & wisaAccounts = caller->getParentObject()->getWisaAccounts();
  
  for (int i = 0; i < wisaAccounts.elms(); i++) {
    wisaImport::wisaAccount & account = wisaAccounts[i];
    if(account.link == nullptr) {
      // create new account
      y::ldap::account values(nullptr);
      values.cn(account.cn);
      values.sn(account.sn);
      values.role(ROLE(ROLE::STUDENT));
      values.birthDay(account.birthday);
      values.wisaID(account.wisaID);
      string password(y::utils::Security().makePassword(8));
      
      y::ldap::account & newAccount = admin.add(values, PASSWORD(password));
      string message("Account voor ");
      message += newAccount.fullName().get();
      message += " werd toegevoegd";
      y::utils::Log().add(message);
      
      newAccount.gender(account.gender);
      newAccount.birthPlace(account.birthplace);
      newAccount.registerID(account.registerID);
      newAccount.nationality(account.nationality);
      newAccount.stemID(account.stemID);
      newAccount.schoolClass(account.schoolClass);
      //newAccount.changeClassDate(account.changeClassDate);
      newAccount.street(account.street);
      newAccount.houseNumber(account.houseNumber);
      newAccount.houseNumberAdd(account.houseNumberAdd);
      newAccount.postalCode(account.postalCode);
      newAccount.city(account.city);
      
      message = newAccount.schoolClass().get();
      message += " ";
      message += newAccount.fullName().get();
      caller->addNewAccountMessage(message);
      message = "Login: ";
      message += newAccount.uid().get();
      caller->addNewAccountMessage(message);
      message = "Wachtwoord: ";
      message += password;
      caller->addNewAccountMessage(message);
      message = "Mail Adres: ";
      message += newAccount.mail().get();
      caller->addNewAccountMessage(message);
      message = " ";
      caller->addNewAccountMessage(message);
      
    } else {
      // account exists, but may not be up to date
      bool namechanged = false;
      bool updated = false;
      if(account.link->sn() != account.sn) {
        account.link->sn(account.sn);
        namechanged = true;
        updated = true;
      }
      if(account.link->cn() != account.cn) {
        account.link->cn(account.cn);
        namechanged = true;
        updated = true;
      }
      
      if(namechanged) {
        string name(account.cn.get());
        name += " ";
        name += account.sn.get();
        account.link->fullName(FULL_NAME(name));
      }
      
      if(account.link->gender() != account.gender) {
        account.link->gender(account.gender);
        updated = true;
      }
      
      if(account.link->birthDay() != account.birthday){
        account.link->birthDay(account.birthday);
        updated = true;
      }
      
      if(account.link->birthPlace() != account.birthplace){
        account.link->birthPlace(account.birthplace);
        updated = true;
      }
      
      if(account.link->registerID() != account.registerID){
        account.link->registerID(account.registerID);
        updated = true;
      }
      
      if(account.link->nationality() != account.nationality){
        account.link->nationality(account.nationality);
        updated = true;
      }
      
      if(account.link->stemID() != account.stemID){
        account.link->stemID(account.stemID);
        updated = true;
      }
      
      if(account.link->wisaID() != account.wisaID){
        account.link->wisaID(account.wisaID);
        updated = true;
      }
      
      if(account.link->schoolClass() != account.schoolClass){
        account.link->schoolClass(account.schoolClass);
        updated = true;
      }
      
      //if(account.link->changeClassDate() != account.changeClassDate){
      //  account.link->changeClassDate(account.changeClassDate);
      //  updated = true;
      //}
      
      if(account.link->street() != account.street){
        account.link->street(account.street);
        updated = true;
      }
      
      if(account.link->houseNumber() != account.houseNumber){
        account.link->houseNumber(account.houseNumber);
        updated = true;
      }
      
      if(account.link->houseNumberAdd() != account.houseNumberAdd){
        account.link->houseNumberAdd(account.houseNumberAdd);
        updated = true;
      }
      
      if(account.link->postalCode() != account.postalCode){
        account.link->postalCode(account.postalCode);
        updated = true;
      }
      
      if(account.link->city() != account.city){
        account.link->city(account.city);
        updated = true;
      }
      
      if(updated) {
        string message("Gebruiker ");
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
  caller->threadDone();
  y::utils::Log().unbind();
}

void wisaCommitStudents::threadDone() {
  Wt::WApplication::UpdateLock lock(parentObject->getApplication());
  if(lock) {
    addMessage("Alle wijzigingen zijn uitgevoerd.");
    imageContainer->removeWidget(waitImage);
    delete waitImage;
    showButtons(false, true);
    
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


void wisaCommitStudents::onShow() {
  entries->clear();
  rowCounter = 0;
  
  parentObject->getApplication()->enableUpdates();
  std::thread t(commitThreadFunc, this);
  t.detach();
}


void wisaCommitStudents::addMessage(const string& message) {
  Wt::WApplication::UpdateLock lock(parentObject->getApplication());
  if(lock) {
    entries->elementAt(rowCounter,0)->addWidget(new Wt::WText(message.wt()));
    entries->elementAt(rowCounter,0)->setPadding(5);
    rowCounter++;
    parentObject->getApplication()->triggerUpdate();
  }  
}

void wisaCommitStudents::addNewAccountMessage(const string& message) {
  download->addMessage(message);
}

bool wisaCommitStudents::onNext() {
  parentObject->reset();
  parentObject->showNewPage(W_UPLOAD);
  return false;
}
