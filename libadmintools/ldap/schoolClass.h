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
      
      const string & description() const; schoolClass & description(const string & desc);
            DN       titular    () const; schoolClass & titular    (const DN     & dn  );
            DN       adjunct    () const; schoolClass & adjunct    (const DN     & dn  );
      int            adminCode  () const; schoolClass & adminCode  (      int      id  );
      int            schoolID   () const; schoolClass & schoolID   (      int      id  );
      
      container<string> & students();
     
      bool addStudent   (const DN & dn);
      bool removeStudent(const DN & dn);
     
    private:
      using ldapObject::load;
      bool load    (const string & cn);
      bool loadData(const data   & d );
      
      virtual bool addNew(dataset & values);
      virtual bool update(dataset & values);
      virtual void beforeRemove();
      
      watch<string> _description;
      watch<string> _titular, _adjunct;
      watch<int> _adminCode, _schoolID;
      
      container<string> _students;
      container<string> _studentsInLDAP;
      
      friend class server;
      
    };
  }
}

#endif	/* SCHOOLCLASS_H */

