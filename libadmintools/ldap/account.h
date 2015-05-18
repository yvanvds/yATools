/* 
 * File:   account.h
 * Author: yvan
 *
 * Created on January 14, 2014, 6:48 PM
 */

#ifndef LDAPACCOUNT_H
#define	LDAPACCOUNT_H

#include "attributes.h"
#include "defines.h"
#include "data.h"
#include "utils/watch.h"

namespace y {
  namespace ldap {
    // because of issues in the past, our ldap fields for some
    // values are a bit confusing. This is why we keep a const list
    // with the intended name mapped to the current ldap field.
    const string TYPE_UID_NUMBER("uidNumber"       );
    const string TYPE_UID       ("uid"             );
    const string TYPE_DN        ("DN"              );
    const string TYPE_CN        ("cn"              );
    const string TYPE_SN        ("sn"              );
    const string TYPE_FULL_NAME ("displayName"     );
    const string TYPE_HOMEDIR   ("homeDirectory"   );
    const string TYPE_WISA_ID   ("employeeNumber"  );
    const string TYPE_MAIL      ("mail"            );
    const string TYPE_PASSWORD  ("title"           );
    const string TYPE_BIRTHDAY  ("roomNumber"      );
    const string TYPE_GID       ("departmentNumber");
    const string TYPE_GID_NUMBER("gidNumber"       );   
    
    class account {
    public:
      account();

      bool isNew(); // true if account does not exist in ldap
      void clear();
      bool save ();
      
      // set - get
      const UID_NUMBER & uidNumber() const; account & uidNumber(const UID_NUMBER & value);
      const UID        & uid      () const; account & uid      (const UID        & value);
      const DN         & dn       () const; 
      const string & cn       () const; account & cn       (const string & value);
      const string & sn       () const; account & sn       (const string & value);
      const FULL_NAME  & fullName () const; account & fullName (const FULL_NAME  & value);
      const HOMEDIR    & homeDir  () const; account & homeDir  (const HOMEDIR    & value);
      const WISA_ID    & wisaID   () const; account & wisaID   (const WISA_ID    & value);
      const MAIL       & mail     () const; account & mail     (const MAIL       & value);
      const DATE       & birthDay () const; account & birthDay (const DATE       & value);
      const PASSWORD   & password () const; account & password (const PASSWORD   & value);
      const GID        & group    () const; account & group    (const GID        & value);
      const GID_NUMBER & groupID  () const; account & groupID  (const GID_NUMBER & value);
      
      // will flag this account for removal during server commit
      void flagForRemoval   () { _flaggedForRemoval = true; }
      bool flaggedForRemoval() { return _flaggedForRemoval; }   
      
      // returns password if changed during this request, otherwise empty string
      string getPasswordText();
      
      // used for wisa import
      WISA_IMPORT getImportStatus();
      account & setImportStatus(WISA_IMPORT status);
      
      TODO(remove after account conversion is complete)
      void convertToNewAccount();
      void removeOldAccountDetails();
      
    private:
      bool load(const UID  & id);
      bool load(UID_NUMBER   id);
      bool load(const DN   & id); 
      
      // shared code for load functions
      bool load(const data & d);
      
      watch<UID_NUMBER>  _uidNumber;
      watch<UID       >  _uid      ;
      watch<DN        >  _dn       ;
      watch<string>  _cn       ;
      watch<string>  _sn       ;
      watch<FULL_NAME >  _fullName ;
      watch<HOMEDIR   >  _homeDir  ;
      watch<WISA_ID   >  _wisaID   ;
      watch<MAIL      >  _mail     ;
      watch<DATE      >  _birthDay ;
      watch<PASSWORD  >  _password ;
      watch<GID       >  _group    ;
      watch<GID_NUMBER>  _groupID  ;

      bool _new; // false if the account is loaded from ldap
      string _passwordClearText; // used to update samba password
      
      // new accounts don't have these
      bool _hasKrbName; 
      bool _hasGroup;
      bool _hasWisaID;
      bool _hasMail;
      bool _hasBirthday;
      
      WISA_IMPORT _importStatus;
      bool _flaggedForRemoval;
      
      friend class server;
    };
  };
}

#endif	/* LDAPACCOUNT_H */