/* 
 * File:   passwordDialog.cpp
 * Author: yvan
 * 
 * Created on May 18, 2014, 8:55 PM
 */

#include "passwordDialog.h"
#include "session.h"
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WLengthValidator>
#include "../ldap/server.h"
#include "utils/string.h"

void y::gui::passwordDialog::create(session * parent) {
  this->parent = parent;
  loginOK = false;
  
  dialog = new Wt::WDialog(parent->root());

  container = new Wt::WContainerWidget(dialog->contents());
  Wt::WVBoxLayout * box = new Wt::WVBoxLayout();
  container->setLayout(box);
  
  Wt::WHBoxLayout * nameBox = new Wt::WHBoxLayout();
  box->addLayout(nameBox);
  
  nameBox->addWidget(new Wt::WText("login: "),1, Wt::AlignMiddle);
  nameEdit = new Wt::WLineEdit();
  nameEdit->setHeight(35);
  nameEdit->setWidth(150);
  nameBox->addWidget(nameEdit);
  
  Wt::WLengthValidator * validator = new Wt::WLengthValidator();
  validator->setMinimumLength(1);
  validator->setMandatory(true);
  nameEdit->setValidator(validator);
  
  Wt::WHBoxLayout * passBox = new Wt::WHBoxLayout();
  box->addLayout(passBox);
  
  passBox->addWidget(new Wt::WText("wachtwoord: "),1, Wt::AlignMiddle);
  passEdit = new Wt::WLineEdit();
  passEdit->setHeight(35);
  passEdit->setWidth(150);
  passEdit->setEchoMode(Wt::WLineEdit::Password);
  passEdit->enterPressed().connect(this, &passwordDialog::validate);
  passBox->addWidget(passEdit);
  
  Wt::WHBoxLayout * buttonBox = new Wt::WHBoxLayout();
  box->addLayout(buttonBox);
  
  loginButton = new Wt::WPushButton("log in");
  loginButton->setWidth(150);
  buttonBox->addWidget(loginButton, 0, Wt::AlignRight);
  loginButton->clicked().connect(this, &passwordDialog::validate);
  loginButton->setStyleClass("btn btn-primary");
  
  Wt::WHBoxLayout *feedbackBox = new Wt::WHBoxLayout();
  box->addLayout(feedbackBox);
  
  loginFeedback = new Wt::WText(" ");
  feedbackBox->addWidget(loginFeedback);
}

void y::gui::passwordDialog::setTitle(const string& value) {
  dialog->setWindowTitle(value.wt());
}

void y::gui::passwordDialog::show() {
  dialog->show();
}

void y::gui::passwordDialog::hide() {
  dialog->hide();
}

void y::gui::passwordDialog::validate() {
  loginName = nameEdit->text();
  loginPass = passEdit->text();
  
  account = y::ldap::Server().getAccount(y::ldap::UID(loginName));
  if(account.isNew()) {
    loginFeedback->setText("controleer je naam");
    loginFeedback->setStyleClass("alert alert-danger");
    nameEdit->setStyleClass("form-control invalid");
    nameEdit->setFocus();
    passEdit->setStyleClass("form-control");
    return;
    
  } else {
    loginOK = y::ldap::Server().auth(account.dn(), y::ldap::PASSWORD(loginPass));
    if(!loginOK) {
      loginFeedback->setText("controleer je wachtwoord");
      loginFeedback->setStyleClass("alert alert-danger");
      passEdit->setStyleClass("form-control invalid");
      passEdit->setText("");
      passEdit->setFocus();
      nameEdit->setStyleClass("form-control");
      return;
      
    } else {  
      if(!parent->validate()) {
        loginFeedback->setText(errorMessage.wt());
        loginFeedback->setStyleClass("alert alert-danger");
        passEdit->setStyleClass("form-control");
        nameEdit->setStyleClass("form-control");
        loginOK = false;
      } else {
        hide();
        parent->onLogin();
      }
    } 
  } 
}
string y::gui::passwordDialog::getName() {
  return loginName;
}

string y::gui::passwordDialog::getPassword() {
  return loginPass;
}

void y::gui::passwordDialog::setErrorMessage(const string & message) {
  errorMessage = message;
  if(errorMessage.empty()) {
    loginFeedback->setStyleClass("");
  } else {
    loginFeedback->setStyleClass("alert alert-danger");
  }
  loginFeedback->setText(errorMessage.wt());
}