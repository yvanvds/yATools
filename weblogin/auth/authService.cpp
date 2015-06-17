/* 
 * File:   authService.cpp
 * Author: yvan
 * 
 * Created on June 15, 2015, 3:29 PM
 */

#include "authService.h"
#include <Wt/Auth/AbstractUserDatabase>
#include <Wt/Auth/AuthService>
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/Identity>
#include <Wt/Auth/User>
#include <Wt/Mail/Client>
#include <Wt/Mail/Message>
#include <Wt/WApplication>
#include <Wt/WRandom>


void authService::lostPassword(const std::string& username, Wt::Auth::AbstractUserDatabase& users) const {
  /*
   * This will check that a user exists in the database, and if so,
   * send an email.
   */
  Wt::Auth::User user = users.findWithIdentity(Wt::Auth::Identity::LoginName, username);
  if(user.isValid() && user.email().size() > 0) {
    std::string random = Wt::WRandom::generateId(randomTokenLength());
    std::string hash = tokenHashFunction()->compute(random, std::string());

    Wt::WDateTime expires = Wt::WDateTime::currentDateTime();
    expires = expires.addSecs(emailTokenValidity() * 60);

    Wt::Auth::Token t(hash, expires);
    user.setEmailToken(t, Wt::Auth::User::LostPassword);
    sendLostPasswordMail(user.email(), user, random);
  }
}