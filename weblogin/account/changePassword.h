/* 
 * File:   changePassword.h
 * Author: yvan
 *
 * Created on June 15, 2015, 11:29 AM
 */

#ifndef CHANGEPASSWORD_H
#define	CHANGEPASSWORD_H

#include <Wt/WWidget>
#include <Wt/WLineEdit>
#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include "ldap/account.h"
#include "ldap/server.h"

class application;

class changePassword : public Wt::WContainerWidget {
public:
  changePassword(y::ldap::server * server) : server(server) {}
  
  void create(y::ldap::account * account, application * app);
  void passwordChanged();
  void mailChanged();
  
private:
  y::ldap::account * account;
  y::ldap::server  * server ;
  application      * app    ;
  
  Wt::WLineEdit   * curPW    ;
  Wt::WLineEdit   * newPW1   ;
  Wt::WLineEdit   * newPW2   ;
  Wt::WText       * feedback1;
  Wt::WText       * feedback2;
  Wt::WText       * feedback3;
  Wt::WText       * feedback4;
  Wt::WPushButton * savePW   ;
  
  Wt::WLineEdit   * email       ;
  Wt::WPushButton * saveMail    ;
  Wt::WText       * feedbackMail;
  
};

#endif	/* CHANGEPASSWORD_H */

