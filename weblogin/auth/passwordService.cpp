/* 
 * File:   updateWidget.cpp
 * Author: yvan
 * 
 * Created on August 27, 2015, 5:37 PM
 */

#include <Wt/Auth/Identity>

#include "passwordService.h"
#include "admintools.h"
#include "ldap/account.h"

void passwordService::updatePassword(const Wt::Auth::User& user, const Wt::WString& password) const {
  string login(user.identity(Wt::Auth::Identity::LoginName));
  y::ldap::server server;
  y::ldap::account & account = server.getAccount(UID(login));
  if(account.isNew()) {
    string error("Password update failed for user ");
    error += login;
    y::utils::Log().add(error);
    return;
  } else {
    account.password(PASSWORD(password));
    server.commitChanges();
  }    
}