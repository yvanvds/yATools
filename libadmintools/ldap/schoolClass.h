/* 
 * File:   schoolClass.h
 * Author: yvan
 *
 * Created on June 12, 2015, 4:07 PM
 */

#ifndef SCHOOLCLASS_H
#define	SCHOOLCLASS_H
#include "utils/watch.h"
#include "utils/container.h"
#include "ldap/attributes.h"
#include "data.h"
#include "ldapObject.h"

namespace y {
  namespace ldap {
    class server;
    
    class schoolClass : public ldapObject {
    public:
      schoolClass(y::ldap::server * server);
      
      void clear();
      
      const DESCRIPTION & description() const; schoolClass & description(const DESCRIPTION & desc);
      const TITULAR     & titular    () const; schoolClass & titular    (const TITULAR     & dn  );
      const ADJUNCT     & adjunct    () const; schoolClass & adjunct    (const ADJUNCT     & dn  );
      const ADMINGROUP  & adminGroup () const; schoolClass & adminGroup (const ADMINGROUP  & id  );
      const SCHOOL_ID   & schoolID   () const; schoolClass & schoolID   (const SCHOOL_ID   & id  );
      
      container<string> & students();
     
      bool addStudent   (const DN & dn);
      bool removeStudent(const DN & dn);
     
    private:
      using ldapObject::load;
      bool load    (const CN     & cn);
      bool loadData(const data   & d );
      
      virtual bool addNew(dataset & values);
      virtual bool update(dataset & values);
      virtual void beforeRemove();
      
      
      stringWatch<DESCRIPTION> _description;
      dnWatch    <TITULAR    > _titular    ;
      dnWatch    <ADJUNCT    > _adjunct    ;
      intWatch   <ADMINGROUP > _adminGroup ;
      intWatch   <SCHOOL_ID  > _schoolID   ;
      
      container<string> _students;
      container<string> _studentsInLDAP;
      
      friend class server;
      
    };
  }
}

#endif	/* SCHOOLCLASS_H */

