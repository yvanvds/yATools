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

      // these functions always create a new account if none is found
      account & getAccount(const UID        & id);
      account & getAccount(      UID_NUMBER   id);
      account & getAccount(const DN         & id);

      group & getGroup(const DN & id);
      group & getGroup(const CN & id, bool editable);

      container<account> & getAccounts(); 
      container<group  > & getGroups  ();     

      // uid numbers of accounts found by this query are stored in results.
      // the function returns the number of accounts found
      int findAccounts(const std::wstring & query, std::vector<UID_NUMBER> & results);
      UID  createUID (const std::wstring & cn, const std::wstring & sn);
      MAIL createMail(const std::wstring & cn, const std::wstring & sn);
      
      // this
      int countResults(const std::wstring &q);
      
      // clears up all loaded accounts and groups
      // this does not affect the database
      void clear();
      
    private:
      bool getData(dataset & rs, bool isDN = false);
      void modify(const DN & dn, dataset & values);
      void add   (const DN & dn, dataset & values);
      void remove(const DN & dn                  );
      
      LDAPMod ** createMods  (dataset &  values); //always combine with releaseMods!!!
      void       releaseMods (LDAPMod ** mods  );
      void       printMods   (LDAPMod ** mods  ); // for debugging only
      void       toLdapModify(const DN & dn, LDAPMod ** mods); // for debugging only
      
      container<account> _accounts;
      container<group  > _groups  ;

      bool _connected;
      std::string _base;
      LDAP * _server;
      LDAP * _authServer;
      struct timeval timeOut;
      
      friend class dataset;
      friend class account;
      friend class group  ;
      
      bool _allAccountsLoaded;
      bool _allGroupsLoaded;
    };

    server & Server(); // global object
  }
}
