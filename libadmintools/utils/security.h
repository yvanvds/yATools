/* 
 * File:   security.h
 * Author: yvan
 *
 * Created on May 8, 2014, 4:37 PM
 */

#ifndef SECURITY_H
#define	SECURITY_H

#include "../ldap/account.h"
#include "string.h"

namespace y {
  namespace utils {
    class security {
    public:
      
      bool test(const ldap::account & account, const string & password);
      string makePassword(int length);
      
      /* Password requires an uppercase letter, a lowercase letter, a number 
       * and one of the following symbols: !@#$%&_
       * It must be between 8-20 characters long.
       */
      bool isGoodPassword(const string & password);
    }; 
    
    security & Security();
  }
  
}


#endif	/* SECURITY_H */

