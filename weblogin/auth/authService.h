/* 
 * File:   authService.h
 * Author: yvan
 *
 * Created on June 15, 2015, 3:29 PM
 */

#ifndef AUTHSERVICE_H
#define	AUTHSERVICE_H

#include <Wt/Auth/AuthService>
#include <Wt/Auth/AbstractUserDatabase>

class authService : public Wt::Auth::AuthService {
public:
  virtual void lostPassword(const std::string & emailaddress,
          Wt::Auth::AbstractUserDatabase & users) const;
private:

};

#endif	/* AUTHSERVICE_H */

