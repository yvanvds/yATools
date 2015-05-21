/* 
 * File:   accountManager.h
 * Author: yvan
 *
 * Created on February 14, 2015, 5:28 PM
 */

#ifndef ACCOUNTMANAGER_H
#define	ACCOUNTMANAGER_H

#include <Wt/WWidget>
#include <Wt/WLineEdit>
#include <Wt/WObject>
#include "ldap/account.h"
#include "ldap/server.h"


class accountManager : public Wt::WContainerWidget {
public:
  accountManager(y::ldap::server * server) : server(server) {}
  void create(y::ldap::account * account);
  void saveButtonClicked();
  
private:
  y::ldap::account * account;
  
  Wt::WLineEdit * firstName;
  Wt::WLineEdit * lastName;
  Wt::WLineEdit * mail;
  Wt::WLineEdit * group;
  Wt::WLineEdit * birthday;
  Wt::WLineEdit * currentPassword;
  Wt::WLineEdit * newPassword1;
  Wt::WLineEdit * newPassword2;
  
  Wt::WText * feedback; 
  Wt::WPushButton * saveButton;
  
  y::ldap::server * server;
};


#endif	/* ACCOUNTMANAGER_H */

