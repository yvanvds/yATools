/* 
 * File:   mailGroup.h
 * Author: yvan
 *
 * Created on January 16, 2014, 12:28 PM
 * 
 * The difference between mailgroups and editable groups is
 * that editable groups are not automatically generated and can
 * contain email addresses from outside the domain. This means
 * they have to be saved differently into ldap.
 * 
 */

#pragma once
#include "group.h"

namespace ldp {
  class mailGroup : group {
  public:
    mailGroup() : group(false) {}
    
    bool load(const DN & id);
    bool load(const CN & id);
    bool save(             );
    
  private:

  };
}



