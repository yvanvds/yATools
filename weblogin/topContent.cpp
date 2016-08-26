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
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WMenuItem>
#include <Wt/WWidget>


#include "topContent.h"
#include "proxyManager.h"
#include "wisaImport.h"
#include "yearbook/yearbook.h"
#include "yearbook/yearbookConfig.h"
#include "yearbook/yearbookReview.h"
#include "yearbook/yearbookDownload.h"
#include "staffManager/newStaff.h"
#include "application.h"

#include "version.h"
#include "build_date.h"

topContent::topContent(application * app, const string & uid) : WContainerWidget()
, yearbookDBPtr(nullptr)
, app(app)
, mainMenu(nullptr)
, rightMenu(nullptr)
{
  setOverflow(OverflowHidden);
  account = &ldapServer.getAccount(UID(uid));
  if(!account->isNew()) {
    create();
  } else {
    this->addWidget(new Wt::WText("Something smells rotten!"));
  }
}

topContent::~topContent() {
  if(yearbookDBPtr != nullptr) {
    delete yearbookDBPtr;
  }
}

void topContent::create() {
  
  Wt::WNavigationBar * navBar = new Wt::WNavigationBar(this);
  navBar->setResponsive(true);
  navBar->setTitle("Sancta Maria Apps", "/");
  
  Wt::WStackedWidget * contents = new Wt::WStackedWidget(this);
  contents->setMargin("1%");
  Wt::WAnimation fade(Wt::WAnimation::Fade, Wt::WAnimation::Linear, 250);
  contents->setTransitionAnimation(fade);
  contents->setId("contents");
  
  mainMenu = new Wt::WMenu(contents, this);
  navBar->addMenu(mainMenu);
  
  contents->addWidget(new Wt::WText(Wt::WString::tr("yAtools.frontpage")));
  
  if(account->isStaff()) {
    mainMenu->addItem("Web Toegang", 
            deferCreate(boost::bind(&topContent::webAccessFunc, this)), 
            Wt::WMenuItem::LazyLoading);
  }
  
  if(account->role().get() == ROLE::ADMIN || account->role().get() == ROLE::DIRECTOR || rights.has(account->uid(), y::data::ADMIN_STAFF)) {
    staffMenu = new Wt::WPopupMenu(contents);
    Wt::WMenuItem * item = new Wt::WMenuItem("Personeel");
    item->setMenu(staffMenu);
    mainMenu->addItem(item);
    
    staffMenu->addItem("Lijst",
            deferCreate(boost::bind(&topContent::staffListFunc, this)), 
            Wt::WMenuItem::LazyLoading);
    staffMenu->addItem("Toevoegen",
            deferCreate(boost::bind(&topContent::newStaffFunc, this)), 
            Wt::WMenuItem::LazyLoading);
  }
  
  if(account->role().get() == ROLE::ADMIN || rights.has(account->uid(), y::data::ADMIN_PASSWORD)) {
    studentMenu = new Wt::WPopupMenu(contents);
    Wt::WMenuItem * item = new Wt::WMenuItem("Leerlingen");
    item->setMenu(studentMenu);
    mainMenu->addItem(item);
    
    studentMenu->addItem("Wachtwoord wijzigen",
            deferCreate(boost::bind(&topContent::studentPasswordFunc, this)),
            Wt::WMenuItem::LazyLoading);
    
    studentMenu->addItem("Wisa Import",
            deferCreate(boost::bind(&topContent::wisaImportFunc, this)),
            Wt::WMenuItem::LazyLoading);
  }
  
  // show this for last year students (or me for testing)
  string group = account->schoolClass().get();
  TODO(only show when yearbook is open)
  if(group[0] == '6' || account->role().get() == ROLE::ADMIN || rights.has(account->uid(), y::data::ADMIN_YEARBOOK)) {
    mainMenu->addItem("Jaarboek", 
            deferCreate(boost::bind(&topContent::yearbookFunc, this)), 
            Wt::WMenuItem::LazyLoading);
  }
  
  
  if(account->role().get() == ROLE::ADMIN || rights.has(account->uid(), y::data::ADMIN_YEARBOOK)) {
    yearbookMenu = new Wt::WPopupMenu(contents);
    
    yearbookMenu->addItem("Review", 
            deferCreate(boost::bind(&topContent::yearbookReviewFunc, this)), 
            Wt::WMenuItem::LazyLoading);
    
    yearbookMenu->addItem("Download", 
            deferCreate(boost::bind(&topContent::yearbookDownloadFunc, this)), 
            Wt::WMenuItem::LazyLoading);
    
    yearbookMenu->addItem("Mailing List",
            deferCreate(boost::bind(&topContent::yearbookMailinglistFunc, this)),
            Wt::WMenuItem::LazyLoading);
    
    yearbookMenu->addItem("Config", 
            deferCreate(boost::bind(&topContent::yearbookConfigFunc, this)), 
            Wt::WMenuItem::LazyLoading);
    yearbookMenu->setInternalPathEnabled("/jaarboek-admin/");
    
    Wt::WMenuItem * item = new Wt::WMenuItem("Jaarboek Admin");
    item->setMenu(yearbookMenu);
    mainMenu->addItem(item);
  }
  
  mainMenu->setInternalPathEnabled("/");

  Wt::WPushButton * loginButton = new Wt::WPushButton("Afmelden");
  loginButton->clicked().connect(std::bind([=] () {
    logoutFunc();
  }));
  navBar->addWidget(loginButton, Wt::AlignmentFlag::AlignRight);
  
  rightMenu = new Wt::WMenu();
  navBar->addMenu(rightMenu, Wt::AlignRight);
  
  Wt::WPopupMenu * popup = new Wt::WPopupMenu(contents);
  
  if(account->isStaff() || account->role().get() == ROLE::EXTERN_WITH_MAIL) {
    popup->addItem("Naam Wijzigen",
            deferCreate(boost::bind(&topContent::changeNameFunc, this)),
            Wt::WMenuItem::LazyLoading);
  }

  popup->addItem("Wachtwoord Wijzigen",
          deferCreate(boost::bind(&topContent::changePasswordFunc, this)),
          Wt::WMenuItem::LazyLoading);
  

  popup->addItem("Bekijk Account",
        deferCreate(boost::bind(&topContent::viewAccountFunc, this)),
        Wt::WMenuItem::LazyLoading);          
  
  
  Wt::WMenuItem * item = new Wt::WMenuItem("Account");
  item->setMenu(popup);
  rightMenu->addItem(item);
  
  string versionText("yAtools version ");
  versionText += VERSION;
  versionText += ", by yvan vander sanden. Build number ";
  versionText += BUILD_NUMBER;
  versionText += " at ";
  versionText += BUILD_DATE;
  Wt::WText * version = new Wt::WText(versionText.wt());
  version->setStyleClass("small");
  version->setPadding("1%");
  this->addWidget(version);
}


void topContent::updateTitle() {
  if(mainMenu->currentItem()) {
    app->setTitle(mainMenu->currentItem()->text());
  }
}

Wt::WWidget * topContent::webAccessFunc() {
  proxyManagerPtr = new proxyManager();
  proxyManagerPtr->create();
  return proxyManagerPtr;
}

Wt::WWidget * topContent::studentPasswordFunc() {
  studentPasswordsPtr = new studentPasswords(&ldapServer);
  studentPasswordsPtr->create();
  return studentPasswordsPtr;
}

Wt::WWidget * topContent::wisaImportFunc() {
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Wisa Import</h3>");
  panel->setStyleClass("panel panel-primary");
  wisaImportPtr = new wisaImport(&ldapServer);
  wisaImportPtr->setApplication(app);
  panel->setCentralWidget(wisaImportPtr);
  panel->setMaximumSize(800, 700);
  panel->setMargin("0 auto");
  return panel;
}

Wt::WWidget * topContent::yearbookFunc() {
  createYearbookDB();
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek</h3>");
  panel->setStyleClass("panel panel-primary");
  
  yearbookPtr = new yearbook(yearbookDBPtr);
  yearbookPtr->setAccount(account);
  panel->setCentralWidget(yearbookPtr);
  panel->setMaximumSize(800, 700);
  panel->setMargin("0 auto");
  return panel;
}

Wt::WWidget * topContent::yearbookReviewFunc() {
  createYearbookDB();
  
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek Review</h3>");
  panel->setStyleClass("panel panel-primary");
  yearbookReviewPtr = new yearbookReview(yearbookDBPtr);
  panel->setCentralWidget(yearbookReviewPtr);
  panel->setMaximumSize(800, 700);
  panel->setMargin("0 auto");
  return panel;
}

Wt::WWidget * topContent::yearbookDownloadFunc() {
  createYearbookDB();
  
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek Download</h3>");
  panel->setStyleClass("panel panel-primary");
  yearbookDownloadPtr = new yearbookDownload(yearbookDBPtr);
  panel->setCentralWidget(yearbookDownloadPtr);
  panel->setMaximumSize(800, 700);
  panel->setMargin("0 auto");
  return panel;
}

Wt::WWidget * topContent::yearbookMailinglistFunc() {
  createYearbookDB();
  
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek Mailing list</h3>");
  panel->setStyleClass("panel panel-primary");
  yearbookMailinglistPtr = new yearbookMailinglist(yearbookDBPtr);
  panel->setCentralWidget(yearbookMailinglistPtr);
  panel->setMaximumSize(800, 700);
  panel->setMargin("0 auto");
  return panel;
}

Wt::WWidget * topContent::yearbookConfigFunc() {
  createYearbookDB();
  
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Jaarboek Configuratie</h3>");
  panel->setStyleClass("panel panel-primary");
  yearbookConfigPtr = new yearbookConfig(yearbookDBPtr);
  panel->setCentralWidget(yearbookConfigPtr);
  panel->setMaximumSize(800, 700);
  panel->setMargin("0 auto");
  return panel;
}

Wt::WWidget * topContent::changePasswordFunc() {
  changePasswordPtr = new changePassword(&ldapServer);
  changePasswordPtr->create(account, app);
  return changePasswordPtr;
}

Wt::WWidget * topContent::changeNameFunc() {
  changeNamePtr = new changeName(&ldapServer);
  changeNamePtr->create(account);
  return changeNamePtr;
}

Wt::WWidget * topContent::viewAccountFunc() {
  viewAccountPtr = new viewAccount(&ldapServer);
  viewAccountPtr->create(account);
  return viewAccountPtr;
}

Wt::WWidget * topContent::staffListFunc() {
  Wt::WPanel * panel = new Wt::WPanel();
  panel->setTitle("<h3>Personeelslijst</h3>");
  panel->setStyleClass("panel panel-primary");
  staffListPtr = new staffList(&ldapServer, &rights);
  panel->setCentralWidget(staffListPtr);
  panel->setMaximumSize(800, 700);
  panel->setMargin("0 auto");
  return panel;
}

Wt::WWidget * topContent::newStaffFunc() {
  newStaff * ns = new newStaff(&ldapServer);
  ns->create();
  return ns;
}

void topContent::logoutFunc() {
  app->setInternalPath("/");
  app->showLogout();
}

void topContent::createYearbookDB() {
  if(yearbookDBPtr == nullptr) {
    yearbookDBPtr = new yearbookDB();
    yearbookDBPtr->loadConfig();
  }
}


