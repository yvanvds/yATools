/* 
 * File:   server.h
 * Author: yvan
 *
 * Created on January 16, 2014, 12:39 PM
 * 
 * Server() can load ldap entries in memory and gives references
 * to work with. Use commitChanges when you're done.
 * 
 */

#pragma once
#include "ldap/attributes.h"
#include "ldap/account.h"
#include "ldap/group.h"
#include "utils/container.h"
#include "dataset.h"
#include <ldap.h>

namespace y {
  namespace ldap {
    class server {
    public:
      server(); // create object and connect to ldap server
     ~server(); // disconnect from ldap server, does not commit changes 

      bool commitChanges(); // propagate all changes to ldap server

      account & getAccount(const UID        & id);
      account & getAccount(const UID_NUMBER   id);
      account & getAccount(const DN         & id);

      group & getGroup(const DN & id);
      group & getGroup(const CN & id);

      container<account> & getAccounts(); // do not mix with getAccount!
      container<group  > & getGroups  (); // do not mix with getGroup!    

    private:
      void getData(dataset & rs);

      container<account> _accounts;
      container<group  > _groups  ;

      bool _connected;
      std::string _base;
      LDAP * _server;
      struct timeval timeOut;

      friend class dataset;
    };

    server & Server(); // global object
  }
}
