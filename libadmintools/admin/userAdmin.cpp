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


y::ldap::account & y::admin::userAdmin::add(const string & cn, 
                                            const string & sn,
                                            const y::ldap::GID & gid, 
                                            const string & schoolClass,
                                            const y::ldap::DATE & dateOfBirth,
                                            const y::ldap::WISA_ID & id, 
                                            const y::ldap::PASSWORD & pw) {
  
  y::ldap::account tempAccount(server);
  tempAccount.uid(y::ldap::UID(server->createUID(cn, sn)));
  tempAccount.group(gid); 
  
  // set group id
  switch(gid()) {
    case y::ldap::ROLE_EXTERN:
    case y::ldap::ROLE_EXTERN_WITH_MAIL:
      tempAccount.groupID(y::ldap::GID_NUMBER(20009));
      break;
    case y::ldap::ROLE_TEACHER:
    case y::ldap::ROLE_DIRECTOR:
    case y::ldap::ROLE_ADMIN:
    case y::ldap::ROLE_SUPPORT:
      tempAccount.groupID(y::ldap::GID_NUMBER(525));
      break;
    case y::ldap::ROLE_STUDENT:
      tempAccount.groupID(y::ldap::GID_NUMBER(1000));
      break;
    case y::ldap::ROLE_NONE:
      y::utils::Log().add("adding user without schoolRole! (this is wrong)");
  }
  
  y::samba::addUser(tempAccount);
  
  // load ldap account created by samba
  y::ldap::account & newAccount = server->getAccount(tempAccount.uid());
  //assert(!newAccount.isNew());
  
  if(newAccount.uid()().size() == 0) {
    // this happens on test server
    newAccount.uid(tempAccount.uid());
    newAccount.group(tempAccount.group());
    newAccount.groupID(tempAccount.groupID());
  }
  
  newAccount.cn(cn);
  newAccount.sn(sn);
  
  string fullName(cn);
  fullName += " "; fullName += sn;
  newAccount.fullName(y::ldap::FULL_NAME(fullName));
  
  newAccount.birthDay(dateOfBirth);
  newAccount.wisaID(id);
  newAccount.password(pw);
  
  newAccount.mail(server->createMail(cn, sn));
  newAccount.group(tempAccount.group());
  newAccount.groupID(tempAccount.groupID());
  newAccount.schoolClass(schoolClass);
  
  // add to group
  if(newAccount.isStaff()) {
    y::ldap::group & mailGroup = server->getGroup("personeel", true);
    mailGroup.members().New() = newAccount.mail()();
    mailGroup.flagForCommit();
  } else if(newAccount.isStudent()) {
    // this is a student belonging to a classgroup
    y::ldap::schoolClass & schoolClass = server->getClass(newAccount.schoolClass());
    schoolClass.addStudent(newAccount.dn());
    schoolClass.flagForCommit();
  }
  
  return newAccount;
}

void y::admin::userAdmin::remove(const y::ldap::account& acc) {
  // remove from groups first
  // if personeel, remove from that group
  if (acc.isStaff()) {
    y::ldap::group & personeel = server->getGroup("personeel", true);
    container<string> & members = personeel.members();
    for(int i = 0; i < members.elms(); i++) {
      if (members[i] == acc.mail()()) {
        members.remove(i);
        personeel.flagForCommit();
        break;
      }
      // for historical reasons members might be added with uid
      string mail(acc.uid()());
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
    y::ldap::schoolClass & schoolClass = server->getClass(acc.schoolClass());
    schoolClass.removeStudent(acc.dn());
    schoolClass.flagForCommit();
  }
  
  y::samba::delUser(acc);
}