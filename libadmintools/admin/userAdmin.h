/* 
 * File:   userAdmin.h
 * Author: yvan
 *
 * Created on May 6, 2015, 12:10 PM
 */

#ifndef USERADMIN_H
#define	USERADMIN_H
#include "ldap/account.h"
#include "ldap/server.h"

namespace y {
  namespace admin {
    
    class userAdmin {
    public:
      userAdmin(y::ldap::server * server) : server(server) {}
      
      y::ldap::account & add(const string & cn, const string & sn,
               const y::ldap::GID & gid, const y::ldap::DATE & dateOfBirth, 
               const y::ldap::WISA_ID & id, const y::ldap::PASSWORD & pw);
      
      void remove(const y::ldap::account & acc);
      
    private:
      y::ldap::server * server;
    };
    
  }
}

#endif	/* USERADMIN_H */

