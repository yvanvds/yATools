/* 
 * File:   userAdmin.h
 * Author: yvan
 *
 * Created on May 6, 2015, 12:10 PM
 */

#ifndef USERADMIN_H
#define	USERADMIN_H
#include "ldap/account.h"

namespace y {
  namespace admin {
    
    class userAdmin {
    public:
      ldap::account & add(const string & cn, const string & sn,
               const ldap::GID & gid, const ldap::DATE & dateOfBirth, 
               const ldap::WISA_ID & id, const ldap::PASSWORD & pw);
      
      void remove(const ldap::account & acc);
      
    private:
      
    };
    
    userAdmin & User();
  }
}

#endif	/* USERADMIN_H */

