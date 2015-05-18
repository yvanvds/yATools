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
#include <assert.h>

y::admin::userAdmin & y::admin::User() {
  static userAdmin u;
  return u;
}

y::ldap::account & y::admin::userAdmin::add(const string & cn, 
                                            const string & sn,
                                            const y::ldap::GID & gid, 
                                            const y::ldap::DATE & dateOfBirth,
                                            const y::ldap::WISA_ID & id, 
                                            const y::ldap::PASSWORD & pw) {
  
  y::ldap::account tempAccount;
  tempAccount.uid(y::ldap::UID(y::ldap::Server().createUID(cn, sn)));
  tempAccount.group(gid); 
  
  // set group id
  if(gid() == "extern") {
    tempAccount.groupID(y::ldap::GID_NUMBER(20009));
  } else if(gid() == "personeel") {
    tempAccount.groupID(y::ldap::GID_NUMBER(525));
  } else if(gid() == "directie") {
    // distinction between personeel and directie is only important
    // for smartschool
    tempAccount.groupID(y::ldap::GID_NUMBER(525));
  }else {
    tempAccount.groupID(y::ldap::GID_NUMBER(1000));
  }
  
  y::samba::addUser(tempAccount);
  
  // load ldap account created by samba
  y::ldap::account & newAccount = y::ldap::Server().getAccount(tempAccount.uid());
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
  
  newAccount.mail(y::ldap::Server().createMail(cn, sn));
  newAccount.group(tempAccount.group());
  newAccount.groupID(tempAccount.groupID());
  
  // add to group
  if(newAccount.group()() == "personeel" || newAccount.group()() == "directie") {
    y::ldap::group & mailGroup = y::ldap::Server().getGroup("personeel", true);
    mailGroup.members().New() = newAccount.mail()();
    mailGroup.flagForCommit();
  } else if(newAccount.group()() != "extern") {
    if(newAccount.group()() != "externmail") {  
      // this is a student belonging to a classgroup
      y::ldap::group & mailGroup = y::ldap::Server().getGroup(newAccount.group()(), false);
      mailGroup.members().New() = newAccount.dn()();
      mailGroup.flagForCommit();
    }
  }
  
  return newAccount;
}

void y::admin::userAdmin::remove(const y::ldap::account& acc) {
  // remove from groups first
  // if personeel, remove from that group
  if (acc.group()() == "personeel" || acc.group()() == "directie") {
    y::ldap::group & personeel = y::ldap::Server().getGroup("personeel", true);
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
  if(acc.group()() != "extern" && acc.group()() != "externmail") {
    y::ldap::group & classGroup = y::ldap::Server().getGroup(acc.group()(), false);
    container<string> & members = classGroup.members();
    for(int i = 0; i < members.elms(); i++) {
      if(members[i] == acc.dn()()) {
        members.remove(i);
        classGroup.flagForCommit();
        break;
      }
    }
  }
  
  y::samba::delUser(acc);
}