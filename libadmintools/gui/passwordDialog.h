/* 
 * File:   passwordDialog.h
 * Author: yvan
 *
 * Created on May 18, 2014, 8:55 PM
 */

#ifndef PASSWORDDIALOG_H
#define	PASSWORDDIALOG_H

#include <Wt/WObject>
#include <Wt/WDialog>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WPushButton>
#include "ldap/account.h"
#include "utils/string.h"

namespace y {
  namespace gui {
    class session;
    
    class passwordDialog : public Wt::WObject {
    public:
      void create(session * parent);
      void setTitle(const string & value);
      void show();
      void hide();
      
      string getName();
      string getPassword();
      void setErrorMessage(const string & message);
      
      y::ldap::account & getAccount();
    private:
      void validate();
      
      Wt::WDialog * dialog;
      Wt::WContainerWidget * container;
      Wt::WLineEdit * nameEdit;
      Wt::WLineEdit * passEdit;
      Wt::WPushButton * loginButton;
      Wt::WText * loginFeedback;
      
      session * parent;
      y::ldap::account account;
      bool loginOK;
      
      string errorMessage;
      Wt::WString loginName;
      Wt::WString loginPass;
    };   
  }
}



#endif	/* PASSWORDDIALOG_H */

