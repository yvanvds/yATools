/* 
 * File:   webLogin.cpp
 * Author: yvan
 * 
 * Created on February 14, 2015, 1:07 PM
 */

#include <Wt/WBootstrapTheme>
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
#include <Wt/WAnimation>
#include <Wt/WTemplate>
#include <admintools.h>

#include "webLogin.h"
#include "accountManager.h"

webLogin::webLogin(const Wt::WEnvironment & env) : Wt::WApplication(env), loggedIn(false) {
  y::utils::Log().add("start of webLogin app");
  
  setTitle("Login Application");
  theme = new Wt::WBootstrapTheme();
  theme->setVersion(Wt::WBootstrapTheme::Version3);
  this->setTheme(theme);
  
  root()->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  root()->setPadding("5%");
  
  loginDialog = new Wt::WDialog(root());
  loginDialog->setWindowTitle("Web Login");
  
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
  passEdit->enterPressed().connect(this, &webLogin::loginButtonClicked);
  passBox->addWidget(passEdit);
  
  Wt::WHBoxLayout * buttonBox = new Wt::WHBoxLayout();
  box->addLayout(buttonBox);
  
  sendButton = new Wt::WPushButton("log in");
  sendButton->setWidth(150);
  buttonBox->addWidget(sendButton, 0, Wt::AlignRight);
  sendButton->clicked().connect(this, &webLogin::loginButtonClicked);
  sendButton->setStyleClass("btn btn-primary");
  
  Wt::WHBoxLayout *feedbackBox = new Wt::WHBoxLayout();
  box->addLayout(feedbackBox);
  
  loginFeedback = new Wt::WText(" ");
  feedbackBox->addWidget(loginFeedback);
  
#ifdef DEBUG
  account = &y::ldap::Server().getAccount(y::ldap::UID(y::utils::Config().getLdapTestUID()));
  loggedIn = true;
  createContents();
  root()->addWidget(homePage);
#else 
  loginDialog->show();
#endif
}

void webLogin::loginButtonClicked() {
  Wt::WString id = nameEdit->text();
  Wt::WString passwd = passEdit->text();
  
  account = &y::ldap::Server().getAccount(y::ldap::UID(id.toUTF8()));
  if(!account->isNew()) {
    
    loggedIn =  y::ldap::Server().auth(account->dn(), y::ldap::PASSWORD(passwd.toUTF8()));

    if(loggedIn) {
      loginDialog->hide();
      loginFeedback->setStyleClass("");
      std::string message(account->uid()());
      message += " has just logged on to the web interface.";
      y::utils::Log().add(message);

    } else {
      loginFeedback->setText("controleer je wachtwoord");
      loginFeedback->setStyleClass("alert alert-danger");
      passEdit->setStyleClass("form-control invalid");
      passEdit->setText("");
      passEdit->setFocus();
      nameEdit->setStyleClass("form-control");
    }

  } else {
    loginFeedback->setText("controleer je naam");
    loginFeedback->setStyleClass("alert alert-danger");
    nameEdit->setStyleClass("form-control invalid");
    nameEdit->setText(id);
    nameEdit->setFocus();
    passEdit->setStyleClass("form-control");
  }
  
  if(loggedIn) {
    createContents();
    root()->addWidget(homePage);
  }
}

void webLogin::createContents() {
  
  homePage = new Wt::WContainerWidget(root());
  Wt::WHBoxLayout * hbox = new Wt::WHBoxLayout();
  homePage->setLayout(hbox);
  
  Wt::WStackedWidget * contents = new Wt::WStackedWidget(root());
  Wt::WAnimation fade(Wt::WAnimation::Fade, Wt::WAnimation::Linear, 250);
  contents->setTransitionAnimation(fade);
  contents->setId("contents");
  
  mainMenu = new Wt::WMenu(contents, Wt::Vertical);
  mainMenu->addItem("Mijn Account", 
          deferCreate(boost::bind(&webLogin::accountFunc, this)), 
          Wt::WMenuItem::PreLoading);
  
  mainMenu->addItem("Web Toegang", 
          deferCreate(boost::bind(&webLogin::webAccessFunc, this)), 
          Wt::WMenuItem::PreLoading);
  
  mainMenu->addItem("Groepen Admin", 
          deferCreate(boost::bind(&webLogin::groupFunc, this)), 
          Wt::WMenuItem::PreLoading);
  
  mainMenu->addItem("Jaarboek", 
          deferCreate(boost::bind(&webLogin::yearbookFunc, this)), 
          Wt::WMenuItem::PreLoading);
  
  mainMenu->addItem("Jaarboek Admin", 
          deferCreate(boost::bind(&webLogin::yearbookAdminFunc, this)), 
          Wt::WMenuItem::PreLoading);
  
  mainMenu->setInternalPathEnabled("/");
  mainMenu->itemSelected().connect(this, &webLogin::updateTitle);
  mainMenu->setStyleClass("nav nav-pills nav-stacked");
  
  hbox->addWidget(mainMenu);
  hbox->addWidget(contents, 1);
  
}

void webLogin::updateTitle() {
  if(mainMenu->currentItem()) {
    setTitle(mainMenu->currentItem()->text());
  }
}

Wt::WWidget * webLogin::accountFunc() {
  return AccountManager().get(account);
}

Wt::WWidget * webLogin::webAccessFunc() {
  return new Wt::WText("webtoegang");
}

Wt::WWidget * webLogin::groupFunc() {
  return new Wt::WText("groepen");
}

Wt::WWidget * webLogin::yearbookFunc() {
  return new Wt::WText("yearbook");
}

Wt::WWidget * webLogin::yearbookAdminFunc() {
  return new Wt::WText("yb admin");
}
