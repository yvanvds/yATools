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
      const std::wstring & cn() const;

      container<std::wstring> & owners ();
      container<std::wstring> & members();
      
      bool removeOwner(const std::wstring & owner);
      bool removeMember(const std::wstring & member);
      
      bool addOwner(const std::wstring & owner);
      bool addMember(const std::wstring & member);

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
      bool load(const std::wstring & cn);
      bool load(const data& d);
      
      bool saveNew   ();
      bool saveUpdate();
      void retrieveData(const data& d);
      
      watch<DN> _dn;
      watch<std::wstring> _cn;

      container<std::wstring> _owners ;
      container<std::wstring> _members;
      
      // these are to compare with ldap data on save
      container<std::wstring> _ownersInLDAP;
      container<std::wstring> _membersInLDAP;

      bool _new     ; // false if loaded from ldap
      bool _editable;
      bool _flaggedForCommit;
      bool _flaggedForRemoval;
      WISA_IMPORT _importStatus;
      
      friend class server;
    };
  }
}

