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
  this->login().setTitle("login vereist");
  
  confPage = new configuration(this);
  reviewPage = new review(this);
  
  menu->addItem("Configuratie", confPage);
  menu->addItem("Review", reviewPage);
  menu->addItem("Download", new Wt::WText("download page"));
  menu->addItem("Exit", new Wt::WText("exit page"));

  login().hide(); 
}

bool yearbookAdmin::validate() {
  if(login().getName().toUTF8().compare("yvanym") == 0) {
    return true;
  }
  
  if(login().getName().toUTF8().compare("segerja") == 0) {
    return true;
  }
  
  // else 
  login().setErrorMessage("Je hebt geen toegang tot deze applicatie");
  return false;
}

void yearbookAdmin::onLogin() {
  //Wt::WText * text = new Wt::WText("success");
  //root()->addWidget(text);
}