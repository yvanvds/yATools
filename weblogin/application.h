/* 
 * File:   application.h
 * Author: yvan
 *
 * Created on June 13, 2015, 8:55 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WNavigationBar>
#include <Wt/WMenu>
#include <Wt/WPushButton>
#include "auth/session.h"
#include "topContent.h"

class application : public Wt::WApplication {
public:
  application(const Wt::WEnvironment & env);
  void authEvent();
  void showLogout();
  
  // needed here because we need to store it in the userSession
  void setAccountMail(const string & mail);
  string getAccountMail();
  
private:
  userSession _session;
  
  Wt::WNavigationBar * navBar;
  Wt::WPushButton * loginButton;
  Wt::WText * siteMenu;
  
  Wt::WDialog * loginDialog;
  Wt::WHBoxLayout * frontPage;
  topContent * content;
};

#endif	/* APPLICATION_H */

