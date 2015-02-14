/* 
 * File:   add.cpp
 * Author: yvan
 * 
 * Created on February 10, 2015, 6:42 PM
 */

#include "addUser.h"
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "ldap/server.h"
#include "utils/security.h"
#include "samba/samba.h"

using namespace std;
using namespace y::ldap;

addUser & AddUser() {
  static addUser s;
  return s;
}

void addUser::printHelp() {
  cout << "Add will add a user to the ldap database and create a home directory." << endl;
  cout << endl;
  cout << "Usage: admin user add <cn> <sn> [date] [group] [wisaID]" << endl;
  cout << endl;
  cout << "<cn>      Given name" << endl;
  cout << "<sn>      Surname" << endl;
  cout << "[date]    Date of birth. Defaults to 19700101" << endl;
  cout << "[group]   Group name. Defaults to extern" << endl;
  cout << "[wisaID]  Unique wisa ID. Defaults to 0" << endl;
}

void addUser::parse(int argc, char** argv) {
  if(argc < 2) {
    printHelp();
    return;
  }
  
  std::string cn(argv[0]);
  std::string sn(argv[1]);
  boost::algorithm::to_lower(cn);
  boost::algorithm::to_lower(sn);
  
  UID uid(Server().createUID(cn, sn));
  account tempAccount;
  
  tempAccount.uid(uid);
  tempAccount.group(GID(argc > 3 ? argv[3] : "extern"));
    
  // set group id
  if((tempAccount.group()()).compare("extern") == 0) {
    tempAccount.groupID(GID_NUMBER(20009));
  } else if(tempAccount.group()().compare("personeel") == 0) {
    tempAccount.groupID(GID_NUMBER(525));
  } else {
    tempAccount.groupID(GID_NUMBER(1000));
  }
  
  // samba creates the account in LDAP with samba parameters
  y::samba::addUser(tempAccount); 
  
  // now load the account created by samba
  account & acc = Server().getAccount(uid);
  assert(!acc.isNew()); // if this is a new account, samba failed to add it
  
  acc.cn(CN(cn));
  acc.sn(SN(sn));
  
  std::string fullName(cn);
  fullName += " "; fullName += sn;
  acc.fullName(FULL_NAME(fullName));
  
  acc.birthDay(DATE      (argc > 2 ? argv[2] : "19700101"  ));
  acc.wisaID  (WISA_ID   (argc > 4 ? std::stoi(argv[4]) : 0));
  
  std::string password(y::utils::Security().makePassword(8));
  acc.password(PASSWORD(password));
  
  acc.mail    (           Server().createMail(cn, sn));
  acc.group   (GID       (tempAccount.group  ()()));
  acc.groupID (GID_NUMBER(tempAccount.groupID()()));
  
  // add to group
  if(acc.group()().compare("personeel") == 0) {
    group & mailGroup = Server().getGroup(CN(acc.group()()), true);
    mailGroup.members().New() = acc.mail()();
    mailGroup.flagForCommit();
  } else if(acc.group()().compare("extern") != 0) {
    if(acc.group()().compare("externmail") != 0) {
      
      // this is a student belonging to a classgroup
      group & mailGroup = Server().getGroup(CN(acc.group()()), false);
      mailGroup.members().New() = acc.dn()();
      mailGroup.flagForCommit();
    }
  }
  
  Server().commitChanges();
  
  cout << "Added user " << fullName << " to " << acc.group()() << endl;
  cout << "  Login   : " << acc.uid()() << endl;
  cout << "  Password: " << password << endl;
  cout << "  Mail    : " << acc.mail()() << endl;
}