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

TODO(update this class to reflect changes to class group and role)

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
  
  y::ldap::account values(nullptr);
  
  values.cn(CN(argv[0]));
  values.sn(SN(argv[1]));
  
  if (argc < 4) values.role(ROLE(ROLE::EXTERN));
  else {
    values.role(ROLE(ROLE::toRole(argv[3])));
    if(values.role().get() == ROLE::NONE) {
      cout << "Invalid role: " << argv[3];
      return;
    }
  }

  values.birthDay(argc > 2 ? DATE(argv[2]) : DATE("19700101"));
  values.wisaID(argc > 4 ? WISA_ID(std::stoi(argv[4])) : WISA_ID(0));
  ::string password(y::utils::Security().makePassword(8));
  
  y::ldap::server server;
  y::admin::userAdmin admin(&server);
  y::ldap::account & account = admin.add(values, PASSWORD(password));

  server.commitChanges();
  
  cout << "Added user "  << account.fullName().get() << " to " << account.role().get() << endl;
  cout << "  Login     : " << account.uid      ().get() << endl;
  cout << "  Password  : " << password                  << endl;
  cout << "  Mail Login: " << account.mailAlias().get() << endl;
  cout << "  Mail      : " << account.mail     ().get() << endl;
}