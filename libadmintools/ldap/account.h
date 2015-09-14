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
   
    class server;

    class account {
    public:
      account(y::ldap::server * server);

      bool isNew(); // true if account does not exist in ldap
      void clear();
      bool save ();
      
      // set - get
      const UID_NUMBER      & uidNumber     () const; account & uidNumber     (const UID_NUMBER      & value);
      const UID             & uid           () const; account & uid           (const UID             & value);
      const DN              & dn            () const; 
      const CN              & cn            () const; account & cn            (const CN              & value);
      const SN              & sn            () const; account & sn            (const SN              & value);
      const FULL_NAME       & fullName      () const; account & fullName      (const FULL_NAME       & value);
      const HOMEDIR         & homeDir       () const; account & homeDir       (const HOMEDIR         & value);
      const WISA_ID         & wisaID        () const; account & wisaID        (const WISA_ID         & value);
      const WISA_NAME       & wisaName      () const; account & wisaName      (const WISA_NAME       & value);
      const MAIL            & mail          () const; account & mail          (const MAIL            & value);
      const MAIL_ALIAS      & mailAlias     () const; account & mailAlias     (const MAIL_ALIAS      & value);
      const DATE            & birthDay      () const; account & birthDay      (const DATE            & value);
      const PASSWORD        & password      () const; account & password      (const PASSWORD        & value);
      const ROLE            & role          () const; account & role          (const ROLE            & value);
      const GID_NUMBER      & groupID       () const; account & groupID       (const GID_NUMBER      & value);
      const SCHOOLCLASS     & schoolClass   () const; account & schoolClass   (const SCHOOLCLASS     & value);
      const DATE            & classChange   () const; account & classChange   (const DATE            & value);
      const BIRTHPLACE      & birthPlace    () const; account & birthPlace    (const BIRTHPLACE      & value);
      const GENDER          & gender        () const; account & gender        (const GENDER          & value);
      const ADMINGROUP      & adminGroup    () const; account & adminGroup    (const ADMINGROUP      & value);
      const REGISTER_ID     & registerID    () const; account & registerID    (const REGISTER_ID     & value);
      const NATION          & nationality   () const; account & nationality   (const NATION          & value);
      const STEM_ID         & stemID        () const; account & stemID        (const STEM_ID         & value);
      const SCHOOL_ID       & schoolID      () const; account & schoolID      (const SCHOOL_ID       & value);
      const HOUSENUMBER     & houseNumber   () const; account & houseNumber   (const HOUSENUMBER     & value);
      const HOUSENUMBER_ADD & houseNumberAdd() const; account & houseNumberAdd(const HOUSENUMBER_ADD & value);
      const CITY            & city          () const; account & city          (const CITY            & value);
      const POSTAL_CODE     & postalCode    () const; account & postalCode    (const POSTAL_CODE     & value);
      const STREET          & street        () const; account & street        (const STREET          & value);
      const COUNTRY         & country       () const; account & country       (const COUNTRY         & value);
      
      bool isStaff  () const;
      bool isStudent() const;
      
      // will flag this account for removal during server commit
      void flagForRemoval   () { _flaggedForRemoval = true; }
      bool flaggedForRemoval() { return _flaggedForRemoval; }   
      
      // returns password if changed during this request, otherwise empty string
      string getPasswordText() const;
      
      // used for wisa import
      WISA_IMPORT getImportStatus();
      account   & setImportStatus(WISA_IMPORT status);
     
      
    private:
      bool load(const UID         & id);
      bool load(const UID_NUMBER  & id);
      bool load(const DN          & id); 
      bool load(const WISA_NAME   & id);
      
      // shared code for load functions
      bool load(const data & d);
      
      y::ldap::server * server;
      
      intWatch   <UID_NUMBER     >  _uidNumber    ;
      stringWatch<UID            >  _uid          ;
      stringWatch<DN             >  _dn           ;
      stringWatch<CN             >  _cn           ;
      stringWatch<SN             >  _sn           ;
      stringWatch<FULL_NAME      >  _fullName     ;
      stringWatch<HOMEDIR        >  _homeDir      ;
      intWatch   <WISA_ID        >  _wisaID       ;
      stringWatch<WISA_NAME      >  _wisaName     ;
      stringWatch<MAIL           >  _mail         ;
      stringWatch<MAIL_ALIAS     >  _mailAlias    ;
      dateWatch  <DATE           >  _birthDay     ;
      stringWatch<PASSWORD       >  _password     ;
      roleWatch  <ROLE           >  _role         ;
      intWatch   <GID_NUMBER     >  _groupID      ;
      stringWatch<SCHOOLCLASS    >  _schoolClass  ;
      dateWatch  <DATE           >  _classChange  ;
      stringWatch<BIRTHPLACE     >  _birthPlace   ;
      genderWatch<GENDER         >  _gender       ;
      intWatch   <ADMINGROUP     >  _adminGroup   ;
      stringWatch<REGISTER_ID    >  _registerID   ;
      stringWatch<NATION         >  _nationality  ;
      intWatch   <STEM_ID        >  _stemID       ;
      intWatch   <SCHOOL_ID      >  _schoolID     ;
      intWatch   <HOUSENUMBER    >  _houseNumber  ;
      stringWatch<HOUSENUMBER_ADD> _houseNumberAdd;
      stringWatch<CITY           >  _city         ;
      stringWatch<POSTAL_CODE    >  _postalCode   ;
      stringWatch<STREET         >  _street       ;
      stringWatch<COUNTRY        >  _country      ;
      
      bool _new; // false if the account is loaded from ldap
      string _passwordClearText; // used to update samba password
      
      // new accounts don't have these
      bool _hasKrbName; 
      bool _hasSchoolPersonClass;
      
      WISA_IMPORT _importStatus;
      bool _flaggedForRemoval;
      
      
      friend class server;
    };
  };
}

#endif	/* LDAPACCOUNT_H */