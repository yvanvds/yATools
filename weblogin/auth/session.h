/* 
 * File:   session.h
 * Author: yvan
 *
 * Created on June 13, 2015, 9:33 PM
 */

#ifndef SESSION_H
#define	SESSION_H

#include <Wt/Auth/Login>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/MySQL>
#include <Wt/Auth/PasswordService>
#include <Wt/Auth/AbstractUserDatabase>
#include "admintools.h"
#include "user.h"

namespace dbo = Wt::Dbo;

typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

class userSession : public dbo::Session {
public:
  userSession(const string & db);
 ~userSession();

  Wt::Dbo::ptr<dbUser> user() const;
  Wt::Auth::AbstractUserDatabase & users();
  Wt::Auth::Login& login() { return _login; }

  static void configureAuth();
  static const Wt::Auth::AuthService& auth();
  static const Wt::Auth::PasswordService & passwordAuth();
  static const std::vector<const Wt::Auth::OAuthService *> & oAuth();

private:
  dbo::backend::MySQL _connection;
  UserDatabase * _users;
  Wt::Auth::Login _login;
};

#endif	/* SESSION_H */

