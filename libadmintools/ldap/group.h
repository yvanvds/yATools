/* 
 * File:   group.h
 * Author: yvan
 *
 * Created on January 16, 2014, 10:01 AM
 */

#pragma once
#include "utils/watch.h"
#include "utils/container.h"
#include "ldap/attributes.h"
#include "data.h"

namespace y {
  namespace ldap {
    class group {
    public:
      group();
      
      bool isNew();
      void clear();
      bool save ();
      
      const DN & dn() const;
      const string & cn() const;

      container<string> & owners ();
      container<string> & members();
      
      bool removeOwner(const string & owner);
      bool removeMember(const string & member);
      
      bool addOwner(const string & owner);
      bool addMember(const string & member);

      group & editable(bool value); // automatic group or not
      bool    editable();
      
      void    flagForCommit    ();
      void    flagForRemoval   ();
      bool    flaggedForRemoval();
      
      // used for wisa import
      WISA_IMPORT getImportStatus();
      group & setImportStatus(WISA_IMPORT status);
      
    private:
      bool load(const DN & id);
      bool load(const string & cn);
      bool load(const data& d);
      
      bool saveNew   ();
      bool saveUpdate();
      void retrieveData(const data& d);
      
      watch<DN> _dn;
      watch<string> _cn;

      container<string> _owners ;
      container<string> _members;
      
      // these are to compare with ldap data on save
      container<string> _ownersInLDAP;
      container<string> _membersInLDAP;

      bool _new     ; // false if loaded from ldap
      bool _editable;
      bool _flaggedForCommit;
      bool _flaggedForRemoval;
      WISA_IMPORT _importStatus;
      
      friend class server;
    };
  }
}

