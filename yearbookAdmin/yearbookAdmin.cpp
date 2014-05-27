/* 
 * File:   yearbookAdmin.cpp
 * Author: yvan
 * 
 * Created on May 18, 2014, 8:25 PM
 */

#include <Wt/WEnvironment>
#include <Wt/WApplication>

#include "yearbookAdmin.h"

yearbookAdmin::yearbookAdmin(const Wt::WEnvironment & env) : session(env) {
  // set login dialog
  setTitle("Jaarboek Administratie");
  root()->setAttributeValue("lang", "nl");
  
  this->login().setTitle("login vereist");
	y::utils::Log().add("start of yearbookadmin app");
  db.load();
	y::utils::Log().add("yearbookadmin data loaded");
  confPage = new configuration(this);
  reviewPage = new review(this);
  
  
  menu->addItem("Review", reviewPage);
  menu->addItem("Download", new Wt::WText("download page"));
  menu->addItem("Configuratie", confPage);
  menu->addSeparator();
  menu->addItem("Exit", new Wt::WText("exit"));
  menu->select(-1);
  menu->contentsStack()->setCurrentIndex(-1);
  menu->itemSelected().connect(this, &yearbookAdmin::onSelected);
}

bool yearbookAdmin::validate() {
  if(login().getName().toUTF8().compare("yvanym") == 0) {
    return true;
  }
  
  for(int i = 0; i < db.validUsers.elms(); i++) {
    if(db.validUsers[i]["accountName"].asString8().compare(login().getName().toUTF8()) == 0) {
      return true;
    }
  }
  
  // else 
  login().setErrorMessage("Je hebt geen toegang tot deze applicatie");
  return false;
}

void yearbookAdmin::onLogin() {

}

void yearbookAdmin::onSelected() {
  if(menu->currentIndex() == 4) {
    this->redirect(this->bookmarkUrl());
    this->quit();
  }
}