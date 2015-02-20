/* 
 * File:   account.h
 * Author: yvan
 *
 * Created on January 14, 2014, 6:48 PM
 */

#ifndef LDAPACCOUNT_H
#define	LDAPACCOUNT_H

#include "utils/watch.h"
#include "ldap/attributes.h"
#include "ldap/data.h"

namespace y {
  namespace ldap {
    // because of issues in the past, our ldap fields for some
    // values are a bit confusing. This is why we keep a const list
    // with the intended name mapped to the current ldap field.
    const std::wstring TYPE_UID_NUMBER(L"uidNumber"       );
    const std::wstring TYPE_UID       (L"uid"             );
    const std::wstring TYPE_DN        (L"DN"              );
    const std::wstring TYPE_CN        (L"cn"              );
    const std::wstring TYPE_SN        (L"sn"              );
    const std::wstring TYPE_FULL_NAME (L"displayName"     );
    const std::wstring TYPE_HOMEDIR   (L"homeDirectory"   );
    const std::wstring TYPE_WISA_ID   (L"employeeNumber"  );
    const std::wstring TYPE_MAIL      (L"mail"            );
    const std::wstring TYPE_PASSWORD  (L"title"           );
    const std::wstring TYPE_BIRTHDAY  (L"roomNumber"      );
    const std::wstring TYPE_GID       (L"departmentNumber");
    const std::wstring TYPE_GID_NUMBER(L"gidNumber"       );
    
    enum WISA_IMPORT {
      WI_NOT_ACCOUNTED, // initial status
      WI_ACCOUNTED    , // a wisa account is found for this entry
      WI_DISCARD      , // don't process in this session  
    };
    
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
      const CN         & cn       () const; account & cn       (const CN         & value);
      const SN         & sn       () const; account & sn       (const SN         & value);
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
      std::wstring getPasswordText();
      
      // used for wisa import
      WISA_IMPORT getImportStatus();
      account & setImportStatus(WISA_IMPORT status);
      
    private:
      bool load(const UID  & id);
      bool load(UID_NUMBER   id);
      bool load(const DN   & id); 
      
      // shared code for load functions
      bool load(const data & d);
      
      watch<UID_NUMBER>  _uidNumber;
      watch<UID       >  _uid      ;
      watch<DN        >  _dn       ;
      watch<CN        >  _cn       ;
      watch<SN        >  _sn       ;
      watch<FULL_NAME >  _fullName ;
      watch<HOMEDIR   >  _homeDir  ;
      watch<WISA_ID   >  _wisaID   ;
      watch<MAIL      >  _mail     ;
      watch<DATE      >  _birthDay ;
      watch<PASSWORD  >  _password ;
      watch<GID       >  _group    ;
      watch<GID_NUMBER>  _groupID  ;

      bool _new; // false if the account is loaded from ldap
      std::wstring _passwordClearText; // used to update samba password
      
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