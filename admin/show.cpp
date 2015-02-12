/* 
 * File:   show.cpp
 * Author: yvan
 * 
 * Created on September 30, 2014, 4:30 PM
 */

#include "show.h"
#include <iostream>
#include "ldap/server.h"

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
    std::string uid(argv[0]);
    
    if(uid.compare("-?") == 0) {
      printHelp();
      return;
    }
    
    y::ldap::account & account = y::ldap::Server().getAccount(y::ldap::UID(uid));
    if(account.isNew()) {
      cout << "This account does not exist." << endl;
      return;
    } else {
      cout << endl;
      cout << "DN        : " << account.dn      ()() << endl;
      cout << "first name: " << account.cn      ()() << endl;
      cout << "surname   : " << account.sn      ()() << endl;
      cout << "full name : " << account.fullName()() << endl;
      cout << "email     : " << account.mail    ()() << endl;
      cout << endl;
      cout << "Birthday  : " << account.birthDay().asString() << endl;
      cout << "Group     : " << account.group   ()() << endl;
      cout << "Homedir   : " << account.homeDir ()() << endl;
    }
  }
}