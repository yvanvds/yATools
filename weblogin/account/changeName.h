/* 
 * File:   changeName.h
 * Author: yvan
 *
 * Created on June 16, 2015, 12:06 PM
 */

#ifndef CHANGENAME_H
#define	CHANGENAME_H

#include <Wt/WWidget>
#include <Wt/WLineEdit>
#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include "ldap/account.h"
#include "ldap/server.h"

class changeName : public Wt::WContainerWidget {
public:
  changeName(y::ldap::server * server) : server(server) {}
  
  void create(y::ldap::account * account);
  void nameChanged();
  
private:
  y::ldap::account * account;
  y::ldap::server  * server ;
  
  Wt::WLineEdit * firstName;
  Wt::WLineEdit * lastName  ;
  
  Wt::WPushButton * saveButton;
  Wt::WText * feedback;
  
};

#endif	/* CHANGENAME_H */

