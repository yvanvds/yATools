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
#include "samba/samba.h"
#include "utils/convert.h"

using namespace std;

password & Password() {
  static password p;
  return p;
}

password::password() {
}

void password::printHelp() {
  cout << "To change a user's password, you need to supply one or two arguments." << endl;
  cout << "<uid>      : the user's userID" << endl;
  cout << "[password] : the new password" << endl;
  cout << endl;
  cout << "If the second argument is omitted, a random password will be chosen." << endl;
}

void password::parse(int argc, char ** argv) {
  if(argc < 1) {
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
      std::wstring password;
      if(argc > 1) {
        password = strW(argv[1]);
      } else {
        password = strW(y::utils::Security().makePassword(8));
      }
      
      if(!y::utils::Security().isGoodPassword(str8(password))) {
        cout << "A password must be between 8-20 character long." << endl;
        cout << "It must contain one lower and one upper case character." << endl;
        cout << "It also needs one or more numbers." << endl;
        return;
      }
      
      account.password(y::ldap::PASSWORD(password));
      y::ldap::Server().commitChanges();
      
      wcout << L"user    : " << account.uid()() << endl;
      wcout << L"password: " << password        << endl;
      
    }
  }
  
  
}

