/* 
 * File:   password.cpp
 * Author: yvan
 * 
 * Created on August 20, 2014, 8:51 PM
 */

#include "password.h"
#include <iostream>
#include "ldap/server.h"
#include "utils/security.h"

using namespace std;

password & Password() {
  static password p;
  return p;
}

password::password() {
}

void password::printHelp() {
  cout << "help" << endl;
}

void password::parse(int argc, char ** argv) {
  if(argc < 3) {
    printHelp();
    return;
  } else {
    std::string uid(argv[2]);
    y::ldap::account & account = y::ldap::Server().getAccount(y::ldap::UID(uid));
    if(account.isNew()) {
      cout << "This account does not exist." << endl;
      return;
    } else {
      std::string password;
      if(argc > 3) {
        password = argv[3];
      } else {
        password = y::utils::Security().makePassword(8);
      }
      
      account.password(y::ldap::PASSWORD(password));
      y::ldap::Server().commitChanges();
      
      cout << "user    : " << account.uid()() << endl;
      cout << "password: " << password        << endl;
      cout << account.password()() << endl;
      
    }
  }
  
  
}

