/* 
 * File:   wisaCommitClasses.cpp
 * Author: yvan
 * 
 * Created on June 22, 2015, 6:27 PM
 */

#include <Wt/WVBoxLayout>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include <thread>
#include <functional>
#include "../wisaImport.h"
#include "wisaCommitClasses.h"


void wisaCommitClasses::setContent(Wt::WVBoxLayout* box) {
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
}

void CommitThreadFunc(wisaCommitClasses * caller) {
  using std::placeholders::_1;
  y::utils::Log().bind(std::bind(&wisaCommitClasses::addMessage, caller, _1));
  caller->getParentObject()->ldap()->commitChanges();
  caller->threadDone();
  y::utils::Log().unbind();
}

void wisaCommitClasses::threadDone() {
  addMessage("Alle wijzigingen zijn uitgevoerd.");
  //progress->setText("<h4>Klaar.</4>");
  //parentObject->getApplication()->enableUpdates(false);
}

void wisaCommitClasses::onShow() {
  entries->clear();
  int rowCounter = 0;
  
  parentObject->getApplication()->enableUpdates();
  std::thread t(CommitThreadFunc, this);
  t.detach();
}



void wisaCommitClasses::addMessage(const string& message) {
  Wt::WApplication::UpdateLock lock(parentObject->getApplication());
  if(lock) {
     entries->elementAt(rowCounter,0)->addWidget(new Wt::WText(message.wt()));
     entries->elementAt(rowCounter,0)->setPadding(5);
     rowCounter++;

     parentObject->getApplication()->triggerUpdate();
  }
}

bool wisaCommitClasses::onNext() {
  parentObject->reset();
  parentObject->showNewPage(W_UPLOAD);
}