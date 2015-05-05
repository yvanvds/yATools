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
      const CN & cn() const;

      container<std::wstring> & owners ();
      container<std::wstring> & members();
     

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
      bool load(const CN & id);
      bool load(const data& d);
      
      bool saveNew   ();
      bool saveUpdate();
      void retrieveData(const data& d);
      
      watch<DN> _dn;
      watch<CN> _cn;

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

