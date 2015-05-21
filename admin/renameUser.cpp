/* 
 * File:   renameUser.cpp
 * Author: yvan
 * 
 * Created on May 8, 2015, 12:16 PM
 */

#include "renameUser.h"
#include <string>
#include <iostream>
#include "ldap/server.h"
#include "utils/config.h"
#include "samba/samba.h"
#include "utils/convert.h"
#include "admin/userAdmin.h"
#include <boost/locale.hpp>

using namespace std;
using namespace y::ldap;

renameUser & RenameUser() {
  static renameUser s;
  return s;
}

void renameUser::printHelp() {
  cout << "With this you can change a user's first name and name." << endl;
  cout << endl;
  cout << "Usage: admin user rename <uid> <cn> <sn>" << endl;
  cout << endl;
  cout << "<uid> the ldap ID of this user" << endl;
  cout << "<cn>  new first name" << endl;
  cout << "<sn>  new last name" << endl;
}

void renameUser::parse(int argc, char ** argv) {
  if(argc < 3) {
    printHelp();
    return;
  }
  
  
  ::string uid(argv[0]);
  ::string cn (argv[1]);
  ::string sn (argv[2]);
  
  y::ldap::server s;
  account & acc = s.getAccount(UID(uid));
  if(acc.isNew()) {
    cout << "This user does not exist." << endl;
    return;
  }

  acc.cn(cn);
  acc.sn(sn);
  
  ::string fullname(cn);
  fullname += " " + sn;
  
  cout << "Name "           << acc.fullName()() 
       << " replaced with " << fullname         << endl;
  
  acc.fullName(y::ldap::FULL_NAME(fullname));
  s.commitChanges();
}