/* 
 * File:   newStaff.h
 * Author: yvan
 *
 * Created on June 19, 2015, 12:19 PM
 */

#ifndef NEWSTAFF_H
#define	NEWSTAFF_H

#include "admintools.h"
#include <Wt/WContainerWidget>

class newStaff : public Wt::WContainerWidget {
public:
  newStaff(y::ldap::server * server) : server(server) {}
  void create();
  
private:
  void addAccount();
  
  y::ldap::server * server;
  
  Wt::WLineEdit * firstName;
  Wt::WLineEdit * surName;
  
  Wt::WDateEdit * dateOfBirth;
  Wt::WComboBox * gender;
  
  Wt::WLineEdit * wisaName;
  Wt::WComboBox * role;
  
  Wt::WPushButton * saveButton;
  
  Wt::WContainerWidget * result;
  Wt::WText * resultName;
  Wt::WText * resultUid;
  Wt::WText * resultMail;
  Wt::WText * resultMailAlias;
  Wt::WText * resultPassword;
  Wt::WText * resultSSPassword;
};

#endif	/* NEWSTAFF_H */

