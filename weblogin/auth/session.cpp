/* 
 * File:   session.cpp
 * Author: yvan
 * 
 * Created on June 13, 2015, 9:33 PM
 */

#include "session.h"
#include "authService.h"
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordService>
#include <Wt/Auth/PasswordStrengthValidator>
#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/GoogleService>
#include <Wt/Auth/FacebookService>
#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Auth/Dbo/UserDatabase>

namespace {

  class MyOAuth : public std::vector<const Wt::Auth::OAuthService *>
  {
  public:
    ~MyOAuth()
    {
      for (unsigned i = 0; i < size(); ++i)
	delete (*this)[i];
    }
  };

  authService myAuthService;
  Wt::Auth::PasswordService myPasswordService(myAuthService);
  MyOAuth myOAuthServices;
}

void userSession::configureAuth()
{
  myAuthService.setAuthTokensEnabled(true, "logincookie");
  myAuthService.setEmailVerificationEnabled(true);

  Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
  verifier->addHashFunction(new Wt::Auth::BCryptHashFunction(7));
  myPasswordService.setVerifier(verifier);
  myPasswordService.setStrengthValidator
    (new Wt::Auth::PasswordStrengthValidator());

  for (unsigned i = 0; i < myOAuthServices.size(); ++i)
    myOAuthServices[i]->generateRedirectEndpoint();
}

userSession::userSession(const string& db)
  : _connection(db.db(), "root", y::utils::Config().getMysqlPassword().db())
{
  _connection.setProperty("show-queries", "true");

  setConnection(_connection);

  mapClass<dbUser>("user");
  mapClass<AuthInfo>("auth_info");
  mapClass<AuthInfo::AuthIdentityType>("auth_identity");
  mapClass<AuthInfo::AuthTokenType>("auth_token");

  try {
    createTables();
    std::cerr << "Created database." << std::endl;
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Using existing database";
  }

  _users = new UserDatabase(*this);
}

userSession::~userSession()
{
  delete _users;
}

Wt::Auth::AbstractUserDatabase& userSession::users()
{
  return * _users;
}

dbo::ptr<dbUser> userSession::user() const
{
  if (_login.loggedIn()) {
    dbo::ptr<AuthInfo> authInfo = _users->find(_login.user());
    return authInfo->user();
  } else
    return dbo::ptr<dbUser>();
}

const Wt::Auth::AuthService& userSession::auth()
{
  return myAuthService;
}

const Wt::Auth::PasswordService& userSession::passwordAuth()
{
  return myPasswordService;
}

const std::vector<const Wt::Auth::OAuthService *>& userSession::oAuth()
{
  return myOAuthServices;
}