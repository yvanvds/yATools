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
#include <Wt/WMenu>

#include "webLogin.h"
#include "accountManager.h"
#include "proxyManager.h"
#include "wisaImport.h"
#include "yearbook/yearbook.h"
#include "yearbook/yearbookConfig.h"
#include "yearbook/yearbookReview.h"
#include "yearbook/yearbookDownload.h"

webLogin::webLogin(Wt::WApplication * app) : WContainerWidget()
, loggedIn(false), yearbookDBPtr(nullptr)
, app(app) {
  setOverflow(OverflowHidden);
  
  
  loginDialog = new Wt::WDialog(this);
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
  
  Wt::WLengthValidator * validator = new Wt::WLengthValidator(this);
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
  account = &ldapServer.getAccount(y::ldap::UID(y::utils::Config().getLdapTestUID()));
  loggedIn = true;
  createContents();
  //loginDialog->show();
#else 
  loginDialog->show();
#endif
}

webLogin::~webLogin() {
  if(yearbookDBPtr != nullptr) {
    delete yearbookDBPtr;
  }
}

void webLogin::loginButtonClicked() {
  Wt::WString id = nameEdit->text();
  Wt::WString passwd = passEdit->text();
  
  account = &ldapServer.getAccount(y::ldap::UID(id)); 
  if(!account->isNew()) {
    
    loggedIn = ldapServer.auth(account->dn(), y::ldap::PASSWORD(passwd));

    if(loggedIn) {
      loginDialog->hide();
      loginFeedback->setStyleClass("");
      string message(account->uid()());
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
  }
}


void webLogin::createContents() {
  Wt::WVBoxLayout * everything = new Wt::WVBoxLayout();
  this->setLayout(everything);
  Wt::WContainerWidget * mainContentBlock = new Wt::WContainerWidget();
  everything->addWidget(mainContentBlock);
  string versionText("yAtools version ");
  versionText += VERSION;
  versionText += ", by yvan vander sanden.";

  everything->addWidget(new Wt::WText(versionText.wt()));
  
  Wt::WHBoxLayout * hbox = new Wt::WHBoxLayout();
  mainContentBlock->setLayout(hbox);
  
  Wt::WStackedWidget * contents = new Wt::WStackedWidget(this);
  Wt::WAnimation fade(Wt::WAnimation::Fade, Wt::WAnimation::Linear, 250);
  contents->setTransitionAnimation(fade);
  contents->setId("contents");
  
  mainMenu = new Wt::WMenu(contents, Wt::Vertical);
  
  mainMenu->addItem("Mijn Account", 
          deferCreate(boost::bind(&webLogin::accountFunc, this)), 
          Wt::WMenuItem::LazyLoading);
  
  if(account->group()() == "personeel") {
    mainMenu->addItem("Web Toegang", 
            deferCreate(boost::bind(&webLogin::webAccessFunc, this)), 
            Wt::WMenuItem::LazyLoading);
  }
  
  if(account->uid()() == "yvanym") {
    mainMenu->addItem("Wisa Import",
            deferCreate(boost::bind(&webLogin::wisaImportFunc, this)),
            Wt::WMenuItem::LazyLoading);
  }
  
  /*
  if(false) {
    mainMenu->addItem("Groepen Admin", 
            deferCreate(boost::bind(&webLogin::groupFunc, this)), 
            Wt::WMenuItem::PreLoading);
  }
  */
  // show this for last year students (or me for testing)
  string group = account->group()();
  TODO(only show when yearbook is open)
  if(group[0] == '6' || group[0] == '7' || y::utils::Config().isYearbookAdmin(account->uid()())) {
    mainMenu->addItem("Jaarboek", 
            deferCreate(boost::bind(&webLogin::yearbookFunc, this)), 
            Wt::WMenuItem::LazyLoading);
  }
  
  if(y::utils::Config().isYearbookAdmin(account->uid()())) {
    yearbookMenu = new Wt::WMenu(contents, Wt::Vertical);
    
    yearbookMenu->addItem("Review", 
            deferCreate(boost::bind(&webLogin::yearbookReviewFunc, this)), 
            Wt::WMenuItem::LazyLoading);
    
    yearbookMenu->addItem("Download", 
            deferCreate(boost::bind(&webLogin::yearbookDownloadFunc, this)), 
            Wt::WMenuItem::LazyLoading);
    
    yearbookMenu->addItem("Config", 
            deferCreate(boost::bind(&webLogin::yearbookConfigFunc, this)), 
            Wt::WMenuItem::LazyLoading);
    yearbookMenu->setInternalPathEnabled("/jaarboek-admin/");
    yearbookMenu->setStyleClass("nav nav-stacked");
    
    mainMenu->addMenu("Jaarboek Admin", yearbookMenu);
  }
  
  mainMenu->setInternalPathEnabled("/");
  //mainMenu->itemSelected().connect(this, &webLogin::updateTitle);
  mainMenu->setStyleClass("nav nav-pills nav-stacked");
  
  Wt::WPushButton * logoutButton = new Wt::WPushButton();
  logoutButton->setText("Afmelden");
  logoutButton->setStyleClass("btn btn-danger");
  logoutButton->clicked().connect(this, &webLogin::logoutFunc);
  
  Wt::WVBoxLayout * leftBox = new Wt::WVBoxLayout();
  leftBox->addWidget(mainMenu);
  leftBox->addWidget(logoutButton);
  leftBox->addWidget(new Wt::WText(), 1);
  
  Wt::WContainerWidget * leftContainer = new Wt::WContainerWidget();
  leftContainer->setLayout(leftBox);
  
  hbox->addWidget(leftContainer);
  hbox->addWidget(contents, 1);
}


void webLogin::updateTitle() {
  if(mainMenu->currentItem()) {
    app->setTitle(mainMenu->currentItem()->text());
  }
}

Wt::WWidget * webLogin::accountFunc() {
  accountManagerPtr = new accountManager(&ldapServer);
  accountManagerPtr->create(account);
  return accountManagerPtr;
}

Wt::WWidget * webLogin::webAccessFunc() {
  proxyManagerPtr = new proxyManager();
  proxyManagerPtr->create();
  return proxyManagerPtr;
}

Wt::WWidget * webLogin::wisaImportFunc() {
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Wisa Import</h3>");
  panel->setStyleClass("panel panel-primary");
  wisaImportPtr = new wisaImport(&ldapServer);
  wisaImportPtr->setApplication(app);
  panel->setCentralWidget(wisaImportPtr);
  panel->setMaximumSize(800, 700);
  return panel;
}
/*
Wt::WWidget * webLogin::groupFunc() {
  return new Wt::WText("groepen");
}
*/
Wt::WWidget * webLogin::yearbookFunc() {
  createYearbookDB();
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek</h3>");
  panel->setStyleClass("panel panel-primary");
  
  yearbookPtr = new yearbook(yearbookDBPtr);
  yearbookPtr->setAccount(account);
  panel->setCentralWidget(yearbookPtr);
  panel->setMaximumSize(800, 700);
  
  return panel;
}

Wt::WWidget * webLogin::yearbookReviewFunc() {
  createYearbookDB();
  
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek Review</h3>");
  panel->setStyleClass("panel panel-primary");
  yearbookReviewPtr = new yearbookReview(yearbookDBPtr);
  panel->setCentralWidget(yearbookReviewPtr);
  panel->setMaximumSize(800, 700);
  
  return panel;
}

Wt::WWidget * webLogin::yearbookDownloadFunc() {
  createYearbookDB();
  
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek Download</h3>");
  panel->setStyleClass("panel panel-primary");
  yearbookDownloadPtr = new yearbookDownload(yearbookDBPtr);
  panel->setCentralWidget(yearbookDownloadPtr);
  panel->setMaximumSize(800, 700);
  
  return panel;
}

Wt::WWidget * webLogin::yearbookConfigFunc() {
  createYearbookDB();
  
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek Configuratie</h3>");
  panel->setStyleClass("panel panel-primary");
  yearbookConfigPtr = new yearbookConfig(yearbookDBPtr);
  panel->setCentralWidget(yearbookConfigPtr);
  panel->setMaximumSize(800, 700);
  
  return panel;
}

void webLogin::logoutFunc() {
  app->redirect("/");
  app->quit();
}

void webLogin::createYearbookDB() {
  if(yearbookDBPtr == nullptr) {
    yearbookDBPtr = new yearbookDB();
    yearbookDBPtr->loadConfig();
  }
}
