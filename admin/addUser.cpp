/* 
 * File:   add.cpp
 * Author: yvan
 * 
 * Created on February 10, 2015, 6:42 PM
 */

#include "addUser.h"
#include <string>
#include <iostream>
#include <boost/locale.hpp>
#include "admintools.h"

using namespace std;

TODO(update this class to reflect changes to class, group and role)

addUser & AddUser() {
  static addUser s;
  return s;
}

void addUser::printHelp() {
  cout << "Add will add a user to the ldap database and create a home directory." << endl;
  cout << endl;
  cout << "Usage: admin user add <cn> <sn> [date] [role] [wisaID]" << endl;
  cout << endl;
  cout << "<cn>      Given name" << endl;
  cout << "<sn>      Surname" << endl;
  cout << "[date]    Date of birth. Defaults to 19700101" << endl;
  cout << "[role]    School role. Defaults to extern" << endl;
  cout << "[wisaID]  Unique wisa ID. Defaults to 0" << endl;
}

void addUser::parse(int argc, char ** argv) {
  if(argc < 2) {
    printHelp();
    return;
  }
  
  ::string cn(argv[0]);
  ::string sn(argv[1]);
  
  y::ldap::SCHOOLROLE role = y::ldap::ROLE_NONE;
  if (argc < 4) role = y::ldap::ROLE_EXTERN;
  else {
    role = y::ldap::SchoolRoleText(argv[3]);
    if(role == y::ldap::ROLE_NONE) {
      cout << "Invalid role: " << argv[3];
      return;
    }
  }
  
  y::ldap::ROLE gid(argc > 3 ? argv[3] : "extern");
  y::ldap::DATE date(argc > 2 ? argv[2] : "19700101");
  y::ldap::WISA_ID id(argc > 4 ? std::stoi(argv[4]) : 0);
  ::string password(y::utils::Security().makePassword(8));
  
  y::ldap::server server;
  y::admin::userAdmin admin(&server);
  y::ldap::account & account = admin.add(cn, sn, gid, date, id, y::ldap::PASSWORD(password));

  server.commitChanges();
  
  cout << "Added user "  << account.fullName()() << " to " << account.role()() << endl;
  cout << "  Login   : " << account.uid()()  << endl;
  cout << "  Password: " << password         << endl;
  cout << "  Mail    : " << account.mail()() << endl;
}