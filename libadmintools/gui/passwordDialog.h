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
#include "../ldap/account.h"

namespace y {
  namespace gui {
    class session;
    
    class passwordDialog : public Wt::WObject {
    public:
      void create(session * parent);
      void setTitle(const std::string & value);
      void show();
      void hide();
      
      const Wt::WString & getName();
      const Wt::WString & getPassword();
      void setErrorMessage(const std::string & message);
      
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
      
      Wt::WString errorMessage;
      Wt::WString loginName;
      Wt::WString loginPass;
    };   
  }
}



#endif	/* PASSWORDDIALOG_H */

