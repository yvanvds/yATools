/* 
 * File:   removeUser.cpp
 * Author: yvan
 * 
 * Created on February 12, 2015, 10:03 PM
 */

#include "removeUser.h"
#include <string>
#include <iostream>
#include "ldap/server.h"
#include "utils/config.h"
#include "samba/samba.h"
#include "utils/convert.h"
#include "admin/userAdmin.h"

using namespace std;
using namespace y::ldap;

removeUser & RemoveUser() {
  static removeUser s;
  return s;
}

void removeUser::printHelp() {
  cout << "With this you can remove a user from ldap and delete its homedirectory." << endl;
  cout << "To really hurt it, this will also delete its gmail account." << endl;
  cout << endl;
  cout << "Usage: admin user remove <uid>" << endl;
  cout << endl;
  cout << "<uid> the ldap ID of this user" << endl;
}

void removeUser::parse(int argc, char ** argv) {
  if (argc < 1) {
    printHelp();
    return;
  }
  
  std::wstring uid(strW(argv[0]));
  account & acc = Server().getAccount(UID(uid));
  if(acc.isNew()) {
    cout << "This user has already entered the void." << endl;
    return;
  }
  
  // if we get here, the user exists
  y::admin::User().remove(acc);
  Server().commitChanges();
}

