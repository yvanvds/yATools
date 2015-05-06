/* 
 * File:   userAdmin.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 12:10 PM
 */

#include "userAdmin.h"
#include "utils/convert.h"
#include "samba/samba.h"
#include "ldap/server.h"
#include "ldap/account.h"
#include <assert.h>

y::admin::userAdmin & y::admin::User() {
  static userAdmin u;
  return u;
}

y::ldap::account & y::admin::userAdmin::add(const y::ldap::CN & cn, 
                                            const y::ldap::SN & sn,
                                            const y::ldap::GID & gid, 
                                            const y::ldap::DATE & dateOfBirth,
                                            const y::ldap::WISA_ID & id, 
                                            const y::ldap::PASSWORD & pw) {
  
  y::ldap::account tempAccount;
  tempAccount.uid(y::ldap::UID(y::ldap::Server().createUID(cn(), sn())));
  tempAccount.group(gid); 
  
  // set group id
  if(gid().compare(L"extern") == 0) {
    tempAccount.groupID(y::ldap::GID_NUMBER(20009));
  } else if(gid().compare(L"personeel") == 0) {
    tempAccount.groupID(y::ldap::GID_NUMBER(525));
  } else if(gid().compare(L"directie") == 0) {
    // distinction between personeel and directie is only important
    // for smartschool
    tempAccount.groupID(y::ldap::GID_NUMBER(525));
  }else {
    tempAccount.groupID(y::ldap::GID_NUMBER(1000));
  }
  
  y::samba::addUser(tempAccount);
  
  // load ldap account created by samba
  y::ldap::account & newAccount = y::ldap::Server().getAccount(tempAccount.uid());
  assert(!newAccount.isNew());
  
  newAccount.cn(cn);
  newAccount.sn(sn);
  
  std::wstring fullName(cn());
  fullName += L" "; fullName += sn();
  newAccount.fullName(y::ldap::FULL_NAME(fullName));
  
  newAccount.birthDay(dateOfBirth);
  newAccount.wisaID(id);
  newAccount.password(pw);
  
  newAccount.mail(y::ldap::Server().createMail(cn(), sn()));
  newAccount.group(tempAccount.group());
  newAccount.groupID(tempAccount.groupID());
  
  // add to group
  if(newAccount.group()().compare(L"personeel") == 0 || newAccount.group()().compare(L"directie") == 0) {
    y::ldap::group & mailGroup = y::ldap::Server().getGroup(y::ldap::CN(L"personeel"), true);
    mailGroup.members().New() = newAccount.mail()();
    mailGroup.flagForCommit();
  } else if(newAccount.group()().compare(L"extern") != 0) {
    if(newAccount.group()().compare(L"externmail") != 0) {
      
      // this is a student belonging to a classgroup
      y::ldap::group & mailGroup = y::ldap::Server().getGroup(y::ldap::CN(newAccount.group()()), false);
      mailGroup.members().New() = newAccount.dn()();
      mailGroup.flagForCommit();
    }
  }
  
  return newAccount;
}