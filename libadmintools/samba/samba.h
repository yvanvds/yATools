/* 
 * File:   samba.h
 * Author: yvan
 *
 * Created on August 19, 2014, 9:15 PM
 */

#ifndef SAMBA_H
#define	SAMBA_H

#include "../ldap/account.h"

namespace y {
  namespace samba {
    
    // these functions depend on the smbldap tools
    // being installed.
    // Also, the smbldap-passwd script must be modified
    // to allow changing a password from the command line.
    
    void changePassword(const std::string & user, const std::string & password);
    void addUser       (const ldap::account & account);
    void delUser       (const ldap::account & account);
  }
}


#endif	/* SAMBA_H */

