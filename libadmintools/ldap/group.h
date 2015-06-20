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
#include "ldapObject.h"
#include "data.h"

namespace y {
  namespace ldap {
    class server;
    
    class group : public ldapObject {
    public:
      group(y::ldap::server * server);

      void clear();

      container<string> & owners ();
      container<string> & members();
      
      bool removeOwner(const string & owner);
      bool removeMember(const string & member);
      
      bool addOwner(const string & owner);
      bool addMember(const string & member);

      group & editable(bool value); // automatic group or not
      bool    editable();

      virtual void beforeRemove() {};
      
      
      
    private:
      using ldapObject::load;
      bool load(const CN & cn);
      bool loadData(const data& d);
      
      virtual bool addNew(dataset & values);
      virtual bool update(dataset & values);

      container<string> _owners ;
      container<string> _members;
      
      // these are to compare with ldap data on save
      container<string> _ownersInLDAP;
      container<string> _membersInLDAP;

      bool _editable;
      
      friend class server;
    };
  }
}

