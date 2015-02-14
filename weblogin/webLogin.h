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

class webLogin : public Wt::WApplication {
public:
  webLogin(const Wt::WEnvironment & env);
  void loginButtonClicked();
  
  void createContents();
  
  bool loggedIn;
  y::ldap::account * account;

private:
  Wt::WContainerWidget * homePage;
  Wt::WBootstrapTheme * theme;
  
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
  Wt::WStackedWidget * stack;
  
  Wt::WWidget * accountFunc();
  Wt::WWidget * webAccessFunc();
  Wt::WWidget * groupFunc();
  Wt::WWidget * yearbookFunc();
  Wt::WWidget * yearbookAdminFunc();
  
  void updateTitle();
  Wt::WWidget * wrapView(Wt::WWidget *(webLogin::*createFunction)());
};

#endif	/* WEBLOGIN_H */

