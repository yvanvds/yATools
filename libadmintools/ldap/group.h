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

      const DN & dn();
      const CN & cn();

      container<std::string> & owners ();
      container<std::string> & members();

      group & editable(bool value); // automatic group or not
      bool    editable();
      
    private:
      void retrieveData(const data& d);
      
      watch<DN> _dn;
      watch<CN> _cn;

      container<std::string> _owners ;
      container<std::string> _members;

      bool _new     ; // false if loaded from ldap
      bool _editable;
      bool _flaggedForCommit;
    };
  }
}

