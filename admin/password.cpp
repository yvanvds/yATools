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
    ::string uid(argv[0]);
    
    if(uid == "-?") {
      printHelp();
      return;
    }
    
    y::ldap::server server;
    y::ldap::account & account = server.getAccount(UID(uid));
    if(account.isNew()) {
      cout << "This account does not exist." << endl;
      return;
    } else {
      ::string password;
      if(argc > 1) {
        password = argv[1];
      } else {
        password = y::utils::Security().makePassword(8);
      }
      
      if(!y::utils::Security().isGoodPassword(password)) {
        cout << "A password must be between 8-20 character long." << endl;
        cout << "It must contain one lower and one upper case character." << endl;
        cout << "It also needs one or more numbers." << endl;
        return;
      }
      
      account.password(PASSWORD(password));
      server.commitChanges();
      
      cout << "user    : " << account.uid().get() << endl;
      cout << "password: " << password            << endl;
      
    }
  }
  
  
}

