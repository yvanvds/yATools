/* 
 * File:   webLogin.h
 * Author: yvan
 *
 * Created on February 14, 2015, 1:07 PM
 */

#ifndef WEBLOGIN_H
#define	WEBLOGIN_H



#include <admintools.h>
#include <Wt/WBootstrapTheme>
#include <Wt/WTable>
#include <Wt/WDate>
#include <Wt/WStackedWidget>
#include "yearbook/yearbook.h"
#include "yearbook/yearbookConfig.h"
#include "yearbook/yearbookReview.h"
#include "yearbook/yearbookDownload.h"
#include "yearbook/yearbookDB.h"
#include "accountManager.h"
#include "proxyManager.h"
#include "ldap/server.h"
#include "wisaImport.h"

using namespace y;

/*
 * A utility container widget which defers creation of its single
 * child widget until the container is loaded (which is done on-demand
 * by a WMenu). The constructor takes the create function for the
 * widget as a parameter.
 *
 * We use this to defer widget creation until needed.
 */
template <typename Function>
class DeferredWidget : public Wt::WContainerWidget
{
public:
  DeferredWidget(Function f)
    : f_(f) { }

private:
  void load() {
    Wt::WContainerWidget::load();
    if (count() == 0)
      addWidget(f_());
  }

  Function f_;
};

template <typename Function>
DeferredWidget<Function> *deferCreate(Function f)
{
  return new DeferredWidget<Function>(f);
}

class webLogin : public Wt::WContainerWidget {
public:
  webLogin(Wt::WApplication * app);
 ~webLogin();
  
  void loginButtonClicked();
  
  void createContents();
  
  bool loggedIn;
  y::ldap::account * account;

private:
  
  // auth
  Wt::WDialog          * loginDialog   ;
  Wt::WContainerWidget * loginContainer;
  Wt::WHBoxLayout      * nameBox       ;
  
  Wt::WLineEdit   * nameEdit     ;
  Wt::WLineEdit   * passEdit     ;
  Wt::WPushButton * sendButton   ;
  Wt::WText       * loginFeedback;
  
  // main contents
  Wt::WMenu * mainMenu;
  Wt::WMenu * yearbookMenu;
  
  Wt::WStackedWidget * stack;
  
  Wt::WWidget * accountFunc();
  Wt::WWidget * webAccessFunc();
  Wt::WWidget * wisaImportFunc();
  //Wt::WWidget * groupFunc();
  Wt::WWidget * yearbookFunc();
  Wt::WWidget * yearbookReviewFunc();
  Wt::WWidget * yearbookDownloadFunc();
  Wt::WWidget * yearbookConfigFunc();
  
  // sub objects
  yearbook * yearbookPtr;
  yearbookConfig * yearbookConfigPtr;
  yearbookDownload * yearbookDownloadPtr;
  yearbookReview * yearbookReviewPtr;
  yearbookDB * yearbookDBPtr;
  accountManager * accountManagerPtr;
  proxyManager * proxyManagerPtr;
  wisaImport * wisaImportPtr;
  
  y::ldap::server ldapServer;
  
  void createYearbookDB();
  
  void logoutFunc();
  
  void updateTitle();
  //Wt::WWidget * wrapView(Wt::WWidget *(webLogin::*createFunction)());
  Wt::WApplication * app;
};

#endif	/* WEBLOGIN_H */

