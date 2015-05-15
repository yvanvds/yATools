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
#include "ldap/server.h"
#include "utils/security.h"
#include "samba/samba.h"
#include "utils/convert.h"
#include "admin/userAdmin.h"

using namespace std;
using namespace y::ldap;

addUser & AddUser() {
  static addUser s;
  return s;
}

void addUser::printHelp() {
  cout << "Add will add a user to the ldap database and create a home directory." << endl;
  cout << endl;
  cout << "Usage: admin user add <cn> <sn> [date] [group] [wisaID]" << endl;
  cout << endl;
  cout << "<cn>      Given name" << endl;
  cout << "<sn>      Surname" << endl;
  cout << "[date]    Date of birth. Defaults to 19700101" << endl;
  cout << "[group]   Group name. Defaults to extern" << endl;
  cout << "[wisaID]  Unique wisa ID. Defaults to 0" << endl;
}

void addUser::parse(int argc, char ** argv) {
  if(argc < 2) {
    printHelp();
    return;
  }
  
  std::wstring cn(strW(argv[0]));
  std::wstring sn(strW(argv[1]));
  
  y::ldap::GID gid(argc > 3 ? strW(argv[3]) : L"extern");
  y::ldap::DATE date(argc > 2 ? strW(argv[2]) : L"19700101");
  y::ldap::WISA_ID id(argc > 4 ? std::stoi(argv[4]) : 0);
  std::wstring password(strW(y::utils::Security().makePassword(8)));
  
  y::ldap::account & account = y::admin::User().add(cn, sn, gid, date, id, PASSWORD(password));

  Server().commitChanges();
  
  wcout << L"Added user "  << account.fullName()() << L" to " << account.group()() << endl;
  wcout << L"  Login   : " << account.uid()()  << endl;
  wcout << L"  Password: " << password         << endl;
  wcout << L"  Mail    : " << account.mail()() << endl;
}