/* 
 * File:   account.h
 * Author: yvan
 *
 * Created on January 14, 2014, 6:48 PM
 */

#pragma once
#include "utils/watch.h"
#include "ldap/attributes.h"

namespace y {
  namespace ldap {
    class account {
    public:
      account();

      // load - save
      bool load(const UID  & id);
      bool load(UID_NUMBER   id);
      bool load(const DN   & id);
      bool save();

      bool empty(); // true if account does not contain any data

      // set - get
      const UID_NUMBER & uidNumber(); account & uidNumber(const UID_NUMBER & value);
      const UID        & uid      (); account & uid      (const UID        & value);
      const DN         & dn       (); 
      const CN         & cn       (); account & cd       (const CN         & value);
      const SN         & sn       (); account & sn       (const SN         & value);
      const FULL_NAME  & fullName (); account & fullName (const FULL_NAME  & value);
      const HOMEDIR    & homeDir  (); account & homeDir  (const HOMEDIR    & value);
      const WISA_ID    & wisaID   (); account & wisaID   (const WISA_ID    & value);
      const MAIL       & mail     (); account & mail     (const MAIL       & value);
      const DATE       & birthDay (); account & birthDay (const DATE       & value);
      const PASSWORD   & password (); account & password (const PASSWORD   & value);

    private:
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

      bool _new; // false if the account is loaded from ldap
    };
  };
}