/* 
 * File:   user.h
 * Author: yvan
 *
 * Created on June 13, 2015, 9:39 PM
 */

#ifndef USER_H
#define	USER_H

#include <Wt/Dbo/Types>
#include <Wt/WGlobal>

namespace dbo = Wt::Dbo;

class dbUser;
typedef Wt::Auth::Dbo::AuthInfo<dbUser> AuthInfo;

class dbUser {
public:
  /* You probably want to add other user information here */

  template<class Action>
  void persist(Action& a)
  {
  }
};


DBO_EXTERN_TEMPLATES(dbUser);

#endif	/* USER_H */

