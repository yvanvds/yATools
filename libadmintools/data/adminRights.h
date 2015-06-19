/* 
 * File:   adminRights.h
 * Author: yvan
 *
 * Created on June 17, 2015, 6:07 PM
 */

#ifndef ADMINRIGHTS_H
#define	ADMINRIGHTS_H

#include "ldap/attributes.h"
#include "utils/string.h"

namespace y {
  namespace data {
    
    enum ADMINRIGHTS {
      ADMIN_STAFF,
      ADMIN_PASSWORD,
      ADMIN_YEARBOOK,
      ADMIN_WISA,
      ADMIN_NUM,
    };
    
    struct nameIDPair {
      string name;
      int ID;
    };
    
    class adminRights {
    public:
      adminRights();
      bool has   (const ::UID & name, ADMINRIGHTS category);
      void add   (const ::UID & name, ADMINRIGHTS category);
      void remove(const ::UID & name, ADMINRIGHTS category);
      
    private:
      void refreshData();
      
      container< container <nameIDPair> > data;
    };
  }
}


#endif	/* ADMINRIGHTS_H */

