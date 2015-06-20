/* 
 * File:   show.cpp
 * Author: yvan
 * 
 * Created on September 30, 2014, 4:30 PM
 */

#include "show.h"
#include <iostream>
#include "ldap/server.h"
#include "utils/convert.h"

using namespace std;

show & Show() {
  static show s;
  return s;
}

show::show() {
}

void show::printHelp() {
  cout << "To show a user's details, you need to tell me it's ID." << endl;
  cout << "<uid> : a userID" << endl;
}

void show::parse(int argc, char ** argv) {
  if (argc < 1) {
    printHelp();
    return;
  } else {
    ::string uid(argv[0]);
    
    if(uid == "-?") {
      printHelp();
      return;
    }
    
    y::ldap::server s;
    y::ldap::account & account = s.getAccount(UID(uid));
    if(account.isNew()) {
      cout << "This account does not exist." << endl;
      return;
    } else {
      cout << endl;
      cout << "DN         : " << account.dn            ().get() << endl;
      cout << "login      : " << account.uid           ().get() << endl;
      cout << "first name : " << account.cn            ().get() << endl;
      cout << "surname    : " << account.sn            ().get() << endl;
      cout << "full name  : " << account.fullName      ().get() << endl;
      cout << "Homedir    : " << account.homeDir       ().get() << endl;
      cout << "Wisa ID    : " << account.wisaID        ().get() << endl;
      cout << "Wisa Name  : " << account.wisaName      ().get() << endl;
      cout << "email      : " << account.mail          ().get() << endl;
      cout << "email alias: " << account.mailAlias     ().get() << endl;
      cout << "Birthday   : " << account.birthDay      ().get() << endl;
      cout << "Role       : " << ROLE::toText(account.role().get()) << endl;
      cout << "Group ID   : " << account.groupID       ().get() << endl;
      cout << "Class      : " << account.schoolClass   ().get() << endl;
      cout << "BirthPlace : " << account.birthPlace    ().get() << endl;
      cout << "Gender     : " << GENDER::toText(account.gender().get()) << endl;
      cout << "AdminGroup : " << account.adminGroup    ().get() << endl;
      cout << "RegisterID : " << account.registerID    ().get() << endl;
      cout << "Nationality: " << account.nationality   ().get() << endl;
      cout << "Stem ID    : " << account.stemID        ().get() << endl;
      cout << "School ID  : " << account.schoolID      ().get() << endl;
      cout << "House Nr   : " << account.houseNumber   ().get() << endl;
      cout << "Bus        : " << account.houseNumberAdd().get() << endl;
      cout << "Street     : " << account.street        ().get() << endl;
      cout << "City       : " << account.city          ().get() << endl;
      cout << "Postal Code: " << account.postalCode    ().get() << endl;
    }
  }
}