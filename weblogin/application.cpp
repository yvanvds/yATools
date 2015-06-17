/* 
 * File:   application.cpp
 * Author: yvan
 * 
 * Created on June 13, 2015, 8:55 PM
 */

#include <Wt/WEnvironment>
#include <Wt/WContainerWidget>
#include <Wt/WBootstrapTheme>
#include <Wt/WHBoxLayout>
#include <Wt/WDialog>
#include "application.h"
#include "topContent.h"
#include "auth/session.h"
#include "auth/authWidget.h"
#include "auth/authModel.h"

application::application(const Wt::WEnvironment & env)
  : Wt::WApplication(env)
  , _session("admintools")
  , loginDialog(nullptr)
  , frontPage  (nullptr)
  , content    (nullptr)
{
  if(appRoot().empty()) {
    std::cerr << "!!!!!!!!!!" << std::endl
	      << "!! Warning: read the README.md file for hints on deployment,"
	      << " the approot looks suspect!" << std::endl
	      << "!!!!!!!!!!" << std::endl;
  }
  messageResourceBundle().use("site_resources/auth_strings");
  messageResourceBundle().use("site_resources/bootstrap_theme");
  messageResourceBundle().use("site_resources/bootstrap3_theme");
  
  _session.login().changed().connect(this, &application::authEvent);
  
  setTitle("Sancta Maria Apps");
  
  Wt::WBootstrapTheme *bootstrapTheme = new Wt::WBootstrapTheme(this);
  bootstrapTheme->setVersion(Wt::WBootstrapTheme::Version3);
  bootstrapTheme->setResponsive(true);
  setTheme(bootstrapTheme);

  // load the default bootstrap3 (sub-)theme
  useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
  useStyleSheet("style/everywidget.css");
  useStyleSheet("style/dragdrop.css");
  useStyleSheet("style/combostyle.css");
  useStyleSheet("style/pygments.css");
  useStyleSheet("style/layout.css");
  useStyleSheet("//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css");
  
  navBar = new Wt::WNavigationBar(this->root());
  navBar->setResponsive(true);
  navBar->setTitle("Sancta Maria Apps");
  
  authWidget * auth = new authWidget(_session);
  authModel * model = new authModel(_session, auth);
  auth->setModel(model);
  auth->model()->addPasswordAuth(&userSession::passwordAuth());
  auth->setRegistrationEnabled(false);

  auth->processEnvironment();
  
  loginDialog = new Wt::WDialog(root());
  loginDialog->contents()->addWidget(auth);
  loginDialog->setTitleBarEnabled(false);
  loginDialog->setWidth(700);
  loginDialog->rejectWhenEscapePressed(true);
  
  loginButton = new Wt::WPushButton("Aanmelden");
  loginButton->clicked().connect(std::bind([=] () {
    loginDialog->show();
  }));
  navBar->addWidget(loginButton, Wt::AlignmentFlag::AlignRight);
  navBar->show();
  
  siteMenu = new Wt::WText(Wt::WString::tr("yAtools.frontpage"));
  root()->addWidget(siteMenu);
  root()->setContentAlignment(Wt::AlignmentFlag::AlignCenter | Wt::AlignmentFlag::AlignMiddle);
}

void application::authEvent() {
  if(_session.login().loggedIn()) {
    const Wt::Auth::User & u = _session.login().user();
    
    if(content == nullptr) {
      content = new topContent(this, string(u.identity("loginname")));
    }
    root()->addWidget(content);
    navBar->hide();
    loginDialog->hide();
    siteMenu->hide();
  } else {
    root()->removeWidget(content);
    navBar->show();
    siteMenu->show();
    loginDialog->hide();
    delete content;
    content = nullptr;
  }
}

void application::showLogout() {
  loginDialog->show();
}

void application::setAccountMail(const string& mail) {
  _session.login().user().setEmail(mail.db());
}

string application::getAccountMail() {
  return string(_session.login().user().email());
}
