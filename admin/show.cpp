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
    std::wstring uid(strW(argv[0]));
    
    if(uid.compare(L"-?") == 0) {
      printHelp();
      return;
    }
    
    y::ldap::account & account = y::ldap::Server().getAccount(y::ldap::UID(uid));
    if(account.isNew()) {
      cout << "This account does not exist." << endl;
      return;
    } else {
      wcout << endl;
      wcout << L"DN        : " << account.dn      ()() << endl;
      wcout << L"first name: " << account.cn      () << endl;
      wcout << L"surname   : " << account.sn      () << endl;
      wcout << L"full name : " << account.fullName()() << endl;
      wcout << L"email     : " << account.mail    ()() << endl;
      wcout << endl;
      wcout << L"Birthday  : " << account.birthDay().asString() << endl;
      wcout << L"Group     : " << account.group   ()() << endl;
      wcout << L"Homedir   : " << account.homeDir ()() << endl;
    }
  }
}