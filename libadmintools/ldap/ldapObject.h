/* 
 * File:   ldapObject.h
 * Author: yvan
 *
 * Created on June 12, 2015, 5:14 PM
 */

#ifndef LDAPOBJECT_H
#define	LDAPOBJECT_H

#include "attributes.h"
#include "defines.h"
#include "data.h"
#include "dataset.h"
#include "utils/watch.h"

namespace y {
  namespace ldap {
    class server;
    
    class ldapObject {
    public:
      ldapObject(y::ldap::server * server);
      virtual ~ldapObject() {}
      
      bool isNew();
      bool save ();
      virtual void clear() = 0;
      
      bool load(const DN & id);
      bool load(const data& d);
      
      const DN & dn() const;
      const CN & cn() const; void cn(const CN & value);
      
      void flagForCommit    () { _flaggedForCommit  = true; }
      // will flag this object for removal during server commit
      void flagForRemoval   ();
      bool flaggedForRemoval() { return _flaggedForRemoval; } 
      
      // used for wisa import
      WISA_IMPORT getImportStatus(                  );
      void        setImportStatus(WISA_IMPORT status);
      
    protected:
      
      virtual bool loadData(const data& d) = 0; // load data of derived class in this function      
      virtual void beforeRemove() = 0;
      virtual bool addNew(dataset & values) = 0;
      virtual bool update(dataset & values) = 0;
     
      y::ldap::server * server;
      stringWatch<DN> _dn;
      stringWatch<CN> _cn;
      
      bool _new     ; // false if loaded from ldap
      bool _editable;
      bool _flaggedForCommit;
      bool _flaggedForRemoval;
      WISA_IMPORT _importStatus;
      
      friend class server;
    };
  }
}

#endif	/* LDAPOBJECT_H */

