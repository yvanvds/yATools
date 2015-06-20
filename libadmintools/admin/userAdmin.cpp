/* 
 * File:   userAdmin.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 12:10 PM
 */

#include "userAdmin.h"
#include "utils/convert.h"
#include "utils/config.h"
#include "samba/samba.h"
#include "ldap/server.h"
#include "ldap/account.h"
#include "utils/log.h"
#include <assert.h>


y::ldap::account & y::admin::userAdmin::add(const y::ldap::account & values, const PASSWORD & pw) {
  
  y::ldap::account tempAccount(server);
  tempAccount.uid(UID(server->createUID(values.cn(), values.sn())));
  tempAccount.role(values.role()); 
  
  // set group id
  switch(values.role().get()) {
    case ROLE::EXTERN:
    case ROLE::EXTERN_WITH_MAIL:
      tempAccount.groupID(GID_NUMBER(20009));
      break;
    case ROLE::TEACHER:
    case ROLE::DIRECTOR:
    case ROLE::ADMIN:
    case ROLE::SUPPORT:
      tempAccount.groupID(GID_NUMBER(525));
      break;
    case ROLE::STUDENT:
      tempAccount.groupID(GID_NUMBER(1000));
      break;
    case ROLE::NONE:
      y::utils::Log().add("adding user without schoolRole! (this is wrong)");
  }
  
  y::samba::addUser(tempAccount);
  
  // load ldap account created by samba
  y::ldap::account & newAccount = server->getAccount(tempAccount.uid());
  //assert(!newAccount.isNew());
  
  if(newAccount.uid().get().size() == 0) {
    // this happens on test server
    newAccount.uid(tempAccount.uid());
    newAccount.role(tempAccount.role());
    newAccount.groupID(tempAccount.groupID());
  }
  
  newAccount.cn(values.cn());
  newAccount.sn(values.sn());
  
  string fullName(values.cn().get());
  fullName += " "; fullName += values.sn().get();
  newAccount.fullName(FULL_NAME(fullName));
  
  
  newAccount.wisaID(values.wisaID());
  newAccount.wisaName(values.wisaName());
  newAccount.mail(server->createMail(values.cn(), values.sn()));
  string alias = newAccount.uid().get();
  alias += "@";
  alias += utils::Config().getDomain();
  newAccount.mailAlias(MAIL_ALIAS(alias));
  newAccount.birthDay(values.birthDay());
  newAccount.password(pw);
  newAccount.role(tempAccount.role());
  newAccount.groupID(tempAccount.groupID());
  newAccount.schoolClass(values.schoolClass());
  newAccount.birthPlace(values.birthPlace());
  newAccount.gender(values.gender());
  newAccount.adminGroup(values.adminGroup());
  newAccount.registerID(values.registerID());
  newAccount.nationality(values.nationality());
  newAccount.stemID(values.stemID());
  newAccount.schoolID(values.schoolID());
  newAccount.houseNumber(values.houseNumber());
  newAccount.houseNumberAdd(values.houseNumberAdd());
  newAccount.city(values.city());
  newAccount.postalCode(values.postalCode());
  newAccount.street(values.street());
  newAccount.country(values.country());
  
  // add to group
  if(newAccount.isStaff()) {
    y::ldap::group & mailGroup = server->getGroup(CN("personeel"), true);
    mailGroup.members().New() = newAccount.mail().get();
    mailGroup.flagForCommit();
  } else if(newAccount.isStudent()) {
    // this is a student belonging to a classgroup
    y::ldap::schoolClass & schoolClass = server->getClass(CN(newAccount.schoolClass().get()));
    schoolClass.addStudent(newAccount.dn());
    schoolClass.flagForCommit();
  }
  
  return newAccount;
}

void y::admin::userAdmin::remove(const y::ldap::account& acc) {
  // remove from groups first
  // if personeel, remove from that group
  if (acc.isStaff()) {
    y::ldap::group & personeel = server->getGroup(CN("personeel"), true);
    container<string> & members = personeel.members();
    for(int i = 0; i < members.elms(); i++) {
      if (members[i] == acc.mail().get()) {
        members.remove(i);
        personeel.flagForCommit();
        break;
      }
      // for historical reasons members might be added with uid
      string mail(acc.uid().get());
      mail += "@";
      mail += y::utils::Config().getDomain();
      if(members[i] == mail) {
        members.remove(i);
        personeel.flagForCommit();
        break;
      }
    }
  }
  
  // remove from class group
  if(acc.isStudent()) {
    y::ldap::schoolClass & schoolClass = server->getClass(CN(acc.schoolClass().get()));
    schoolClass.removeStudent(acc.dn());
    schoolClass.flagForCommit();
  }
  
  y::samba::delUser(acc);
}