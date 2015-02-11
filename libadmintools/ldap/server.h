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

      // check a user's password
      bool auth(const DN & dn, const PASSWORD & password); 
      
      bool commitChanges(); // propagate all changes to ldap server

      // these functions always create an account if none is found
      account & getAccount(const UID        & id);
      account & getAccount(      UID_NUMBER   id);
      account & getAccount(const DN         & id);

      group & getGroup(const DN & id);
      group & getGroup(const CN & id);

      container<account> & getAccounts(); // do not mix with getAccount!
      container<group  > & getGroups  (); // do not mix with getGroup!    

      // uid numbers of accounts found by this query are stored in results.
      // the function returns the number of accounts found
      int findAccounts(const std::string & query, std::vector<UID_NUMBER> & results);
      UID  createUID (const std::string & cn, const std::string & sn);
      MAIL createMail(const std::string & cn, const std::string & sn);
      
      // this
      int countResults(const std::string &q);
    private:
      bool getData(dataset & rs);
      void setData(const DN & dn, dataset & values);

      container<account> _accounts;
      container<group  > _groups  ;

      bool _connected;
      std::string _base;
      LDAP * _server;
      LDAP * _authServer;
      struct timeval timeOut;

      enum LDAP_MODE {
        LDAP_MODE_NONE,
        LDAP_MODE_SINGLE,
        LDAP_MODE_FULL,
      } _ldapMode;
      
      friend class dataset;
      friend class account;
    };

    server & Server(); // global object
  }
}
