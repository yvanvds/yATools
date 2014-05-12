/* 
 * File:   yearBook.cpp
 * Author: yvan
 * 
 * Created on May 12, 2014, 7:47 PM
 */

#include "yearBook.h"
#include <gui/application.h>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WPanel>
#include <Wt/WDialog>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>

using namespace y;

yearBook::yearBook(const Wt::WEnvironment& env) : Wt::WApplication(env) {
  setTitle("Jaarboek");
  setCssTheme("polished");
  
  loginDialog = new Wt::WDialog(root());
  loginDialog->setWindowTitle("Login");
  //loginDialog->resize(300,300);
  
  loginContainer = new Wt::WContainerWidget(loginDialog->contents());
  Wt::WVBoxLayout * box = new Wt::WVBoxLayout();
  loginContainer->setLayout(box);
  
  Wt::WHBoxLayout * nameBox = new Wt::WHBoxLayout();
  box->addLayout(nameBox);
  
  nameBox->addWidget(new Wt::WText("login: "), 1);
  nameEdit = new Wt::WLineEdit();
  nameEdit->setWidth(150);
  nameBox->addWidget(nameEdit);
  
  Wt::WHBoxLayout * passBox = new Wt::WHBoxLayout();
  box->addLayout(passBox);
  
  passBox->addWidget(new Wt::WText("wachtwoord: "), 1);
  passEdit = new Wt::WLineEdit();
  passEdit->setWidth(150);
  passEdit->setEchoMode(Wt::WLineEdit::Password);
  passBox->addWidget(passEdit);
  
  Wt::WHBoxLayout * buttonBox = new Wt::WHBoxLayout();
  box->addLayout(buttonBox);
  
  buttonBox->addWidget(new Wt::WText(" "), 1);
  sendButton = new Wt::WPushButton("log in");
  sendButton->setWidth(150);
  buttonBox->addWidget(sendButton, 0, Wt::AlignRight);
  
  loginDialog->show();
}
