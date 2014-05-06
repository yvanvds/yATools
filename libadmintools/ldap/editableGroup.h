/* 
 * File:   editableGroup.h
 * Author: yvan
 *
 * Created on January 16, 2014, 12:35 PM
 * 
 * The difference between mailgroups and editable groups is
 * that editable groups are not automatically generated and can
 * contain email addresses from outside the domain. This means
 * they have to be saved differently into ldap.
 * 
 */

#pragma once
#include "ldap/group.h"

namespace y {
  namespace ldap {
    class editableGroup : group {
    public:
      editableGroup() : group(true) {}

      bool load(const DN & id);
      bool load(const CN & id);
      bool save(             );

    private:

    };
  }
}



