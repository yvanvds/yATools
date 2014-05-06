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

namespace y {
  namespace ldap {
    class group {
    public:
      group(bool editable);

      virtual bool load(const DN & id) = 0;
      virtual bool load(const CN & id) = 0;
      virtual bool save(             ) = 0;

      const DN & dn();
      const CN & cn();

      container<DN> & owners ();
      container<DN> & members();

    private:
      watch<DN> _dn;
      watch<CN> _cn;

      container<DN> _owners ;
      container<DN> _members;

      bool _new     ; // false if loaded from ldap
      bool _editable; // automatic group or not, set by subclasses
    };
  }
}

