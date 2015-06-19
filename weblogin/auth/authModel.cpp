/* 
 * File:   authModel.cpp
 * Author: yvan
 * 
 * Created on June 14, 2015, 2:48 PM
 */

#include <Wt/WTheme>

#include "authModel.h"


authModel::authModel(userSession & s, Wt::WObject * parent) 
  : Wt::Auth::AuthModel(userSession::auth(), s.users(), parent)
{}

bool authModel::validateField(Field field) {
  if(field == RememberMeField) return true;
  
  y::ldap::account & account = ldapServer.getAccount(UID(valueText(LoginNameField)));
  
  if(field == LoginNameField) {
    if(!account.isNew()) {
      setValid(LoginNameField);
      return true;
    } else {
      setValidation(LoginNameField,
         Wt::WValidator::Result(Wt::WValidator::Invalid,
            Wt::WString::tr("Wt.Auth.user-name-invalid")));
      return false;
    }
  }
  
  if(field == PasswordField) {
    if(account.isNew()) return false;
    if(ldapServer.auth(account.dn(), PASSWORD(valueText(PasswordField)))) {
      setValid(PasswordField);
      
      Wt::Auth::User user = users().findWithIdentity(Wt::Auth::Identity::LoginName, account.uid().get().db());
      if(!user.isValid()) {
        Wt::Auth::User user = users().registerNew();
        user.addIdentity(Wt::Auth::Identity::LoginName, account.uid().get().db());
      }
      return true;
    } else {
      setValidation(PasswordField,
        Wt::WValidator::Result(Wt::WValidator::Invalid,
          Wt::WString::tr("Wt.Auth.password-invalid")));
      return false;
    }
  }
  return true;
}


