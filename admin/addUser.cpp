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

void addUser::printHelp(const std::string & process) {
  cout << "Add will add a user to the ldap database and create a home directory." << endl;
  cout << "Usage: " << process << " add <cn> <sn> [date] [group] [wisaID]" << endl;
  cout << endl;
  cout << "<cn>      Given name" << endl;
  cout << "<sn>      Surname" << endl;
  cout << "[date]    Date of birth. Defaults to 19700101" << endl;
  cout << "[group]   Group name. Defaults to extern" << endl;
  cout << "[wisaID]  Unique wisa ID. Defaults to 0" << endl;
}

void addUser::parse(int argc, char** argv) {
  if(argc < 4) {
    printHelp(argv[0]);
    return;
  }
  
  std::string cn(argv[2]);
  std::string sn(argv[3]);
  boost::algorithm::to_lower(cn);
  boost::algorithm::to_lower(sn);
  
  UID uid(Server().createUID(cn, sn));
  account tempAccount;
  
  tempAccount.uid(uid);
  tempAccount.group(GID(argc > 5 ? argv[5] : "extern"));
    
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
  
  acc.birthDay(DATE   (argc > 4 ? argv[4] : "19700101"  ));
  acc.wisaID  (WISA_ID(argc > 6 ? std::stoi(argv[6]) : 0));
  acc.password(PASSWORD(y::utils::Security().makePassword(8)));
  
  
}