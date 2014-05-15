/* 
 * File:   yearBook.h
 * Author: yvan
 *
 * Created on May 12, 2014, 7:47 PM
 */

#ifndef YEARBOOK_H
#define	YEARBOOK_H

#include <admintools.h>
#include <Wt/WBootstrapTheme>
#include <Wt/WTable>
#include <Wt/WDate>
#include <vector>
#include "step.h"
#include "data.h"

using namespace y;

enum action {
  A_PREVIOUS,
  A_NEXT,
  A_LOGOUT,
  A_SAVE,
};

class yearBook : public Wt::WApplication {
public:
  yearBook(const Wt::WEnvironment & env);
  void loginButtonClicked();
  void setAction(action message);
  
  
  bool loggedIn;
  y::ldap::account account;
  
  //data
  dataconnect store;
  Wt::WString name;
  Wt::WString surname;
  Wt::WString group;
  Wt::WDate date;
  Wt::WString mail;
  
  Wt::WString answer1;
  Wt::WString answer2;
  Wt::WString answer3;
  Wt::WString answer4;
  
private:
  Wt::WBootstrapTheme * theme;
  
  // auth
  Wt::WDialog * loginDialog;
  Wt::WContainerWidget * loginContainer;
  Wt::WHBoxLayout * nameBox;
  
  Wt::WLineEdit * nameEdit;
  Wt::WLineEdit * passEdit;
  Wt::WPushButton * sendButton;
  Wt::WText * loginFeedback;
  
  // content
  std::vector<std::unique_ptr<step>> steps;
  int currentStep;
  
  
  
};

#endif	/* YEARBOOK_H */

