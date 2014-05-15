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
#include <Wt/WBootstrapTheme>
#include <Wt/WTable>
#include <Wt/WLengthValidator>

#include "step1.h"
#include "step2.h"
#include "step3.h"
#include "step4.h"
#include "step5.h"
#include "stepPhoto.h"
#include "step6.h"

using namespace y;

yearBook::yearBook(const Wt::WEnvironment& env) : Wt::WApplication(env) {
  y::utils::Log().add("start of yearbook app");
  loggedIn = false;
  currentStep = 0;
  
  setTitle("Jaarboek");
  theme = new Wt::WBootstrapTheme();
  theme->setVersion(Wt::WBootstrapTheme::Version3);
  this->setTheme(theme); 
  
  root()->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  root()->setPadding("5%");
  
  loginDialog = new Wt::WDialog(root());
  loginDialog->setWindowTitle("Jaarboek App Login");
  //loginDialog->resize(300,300);
  
  loginContainer = new Wt::WContainerWidget(loginDialog->contents());
  Wt::WVBoxLayout * box = new Wt::WVBoxLayout();
  loginContainer->setLayout(box);
  
  nameBox = new Wt::WHBoxLayout();
  box->addLayout(nameBox);
  
  nameBox->addWidget(new Wt::WText("login: "),1, Wt::AlignMiddle);
  nameEdit = new Wt::WLineEdit();
  nameEdit->setHeight(35);
  nameEdit->setWidth(150);
  nameBox->addWidget(nameEdit);
  
  Wt::WLengthValidator * validator = new Wt::WLengthValidator();
  validator->setMinimumLength(1);
  validator->setInvalidTooShortText("Je hebt WEL een naam!");
  validator->setMandatory(true);
  nameEdit->setValidator(validator);
  
  Wt::WHBoxLayout * passBox = new Wt::WHBoxLayout();
  box->addLayout(passBox);
  
  passBox->addWidget(new Wt::WText("wachtwoord: "),1, Wt::AlignMiddle);
  passEdit = new Wt::WLineEdit();
  passEdit->setHeight(35);
  passEdit->setWidth(150);
  passEdit->setEchoMode(Wt::WLineEdit::Password);
  passEdit->enterPressed().connect(this, &yearBook::loginButtonClicked);
  passBox->addWidget(passEdit);
  
  Wt::WHBoxLayout * buttonBox = new Wt::WHBoxLayout();
  box->addLayout(buttonBox);
  
  sendButton = new Wt::WPushButton("log in");
  sendButton->setWidth(150);
  buttonBox->addWidget(sendButton, 0, Wt::AlignRight);
  sendButton->clicked().connect(this, &yearBook::loginButtonClicked);
  sendButton->setStyleClass("btn btn-primary");
  
  Wt::WHBoxLayout *feedbackBox = new Wt::WHBoxLayout();
  box->addLayout(feedbackBox);
  
  loginFeedback = new Wt::WText(" ");
  feedbackBox->addWidget(loginFeedback);
  
  loginDialog->show();
  
  // set up steps
  steps.emplace_back(new step1());
  steps.emplace_back(new step2());
  steps.emplace_back(new step3());
  steps.emplace_back(new step4());
  steps.emplace_back(new step5());
  steps.emplace_back(new stepPhoto());
  steps.emplace_back(new step6());
  
  steps[0]->showNextButton(true);
  steps[0]->create(this);
  steps[1]->showPreviousButton(true);
  steps[1]->showNextButton(true);
  steps[1]->create(this);
  steps[2]->showPreviousButton(true);
  steps[2]->showNextButton(true);
  steps[2]->create(this);
  steps[3]->showPreviousButton(true);
  steps[3]->showNextButton(true);
  steps[3]->create(this);
  steps[4]->showPreviousButton(true);
  steps[4]->showNextButton(true);
  steps[4]->create(this);
  steps[5]->showPreviousButton(true);
  steps[5]->showSaveButton(true);
  steps[5]->create(this);
  steps[6]->create(this);
}

void yearBook::loginButtonClicked() {
  Wt::WString id = nameEdit->text();
  Wt::WString passwd = passEdit->text();
  
  account = y::ldap::Server().getAccount(y::ldap::UID(id.toUTF8()));
  if(!account.isNew()) {
    loggedIn = y::ldap::Server().auth(account.dn(), y::ldap::PASSWORD(passwd.toUTF8()));
  
    if(loggedIn) {
      loginDialog->hide();
      loginFeedback->setStyleClass("");
      y::utils::Log().add("load id from database");
      if(!store.load(id)) {
        y::utils::Log().add("id not found");
        store.ID(id);
        store.name(account.cn()());
        store.surname(account.sn()());
        std::string fullname;
        fullname = account.cn()();
        fullname.append(" ");
        fullname.append(account.sn()());
        store.servername(fullname);
        store.group(account.group()());
        Wt::WDate date;
        date.setDate(account.birthDay().getYear(), account.birthDay().getMonth(), account.birthDay().getDay());    
        store.birthday(date);
      }
      y::utils::Log().add("found id");

      steps[currentStep]->show();
    } else {
      loginFeedback->setText("controleer je wachtwoord");
      loginFeedback->setStyleClass("alert alert-danger");
      passEdit->setStyleClass("form-control Wt-invalid");
      passEdit->setText("");
      passEdit->setFocus();
      nameEdit->setStyleClass("form-control");
    }
  } else {
    loginFeedback->setText("controleer je naam");
    loginFeedback->setStyleClass("alert alert-danger");
    nameEdit->setStyleClass("form-group has-error");
    nameEdit->setText(id);
    nameEdit->setFocus();
    passEdit->setStyleClass("form-control");
  }
}

void yearBook::setAction(action message) {
  switch(message) {
    case A_LOGOUT: {
      this->redirect("/");
      this->quit();
      
      break;
    }
    case A_PREVIOUS: {
      steps[currentStep]->hide();
      currentStep--;
      steps[currentStep]->show();
      break;
    }
    case A_NEXT: {
      steps[currentStep]->hide();
      currentStep++;
      steps[currentStep]->show();
      break;
    }
    case A_SAVE: {
      store.save();
      steps[currentStep]->hide();
      currentStep++;
      steps[currentStep]->show();
      break;
    }
  }
}