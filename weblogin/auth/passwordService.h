/* 
 * File:   passwordService.h
 * Author: yvan
 *
 * Created on August 27, 2015, 5:37 PM
 */

#ifndef PASSWORDSERVICE_H
#define	PASSWORDSERVICE_H

#include <Wt/Auth/PasswordService>

class passwordService : public Wt::Auth::PasswordService {
public:
  passwordService(const Wt::Auth::AuthService& baseAuth)
    : Wt::Auth::PasswordService(baseAuth) {}
    
  virtual void updatePassword(const Wt::Auth::User &user, const Wt::WString & password) const;
};

#endif	/* PASSWORDSERVICE_H */

