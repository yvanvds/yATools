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

      bool load(const DN & id);
      bool load(const CN & id);
      bool load(const data& d);
      
      void flagForCommit();
      void flagForDelete();
      bool save();

      const DN & dn();
      const CN & cn();

      container<std::wstring> & owners ();
      container<std::wstring> & members();

      group & editable(bool value); // automatic group or not
      bool    editable();
      bool    isNew   ();
      bool    wilBeDeleted();
      
      
    private:
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
      bool _flaggedForDelete;
    };
  }
}

