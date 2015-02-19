/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on August 20, 2014, 5:22 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <unistd.h>
#include "utils/config.h"
#include "password.h"
#include "show.h"
#include "find.h"
#include "addUser.h"
#include "removeUser.h"
#include "proxyManager.h"
#include "smartschool/smartschool.h"
#include "ldap/server.h"
#include "utils/convert.h"
#include <boost/locale.hpp>

using namespace std;

void printBasicHelp();
void printUserHelp ();

int main(int argc, char ** argv) {
  boost::locale::generator gen;
  std::locale loc = gen("en_US.UTF-8");
  std::locale::global(loc);
  std::wcout.imbue(loc);

#ifndef DEBUG
  if(getuid()) {
    cout << "You must be root to execute this command!" << endl;
    return 0;
  }
#endif   
  if(argc < 2) {
    printBasicHelp();
    return 0;
  }
  
  y::utils::Config().load();
  
  y::Smartschool();
  return 0;
  
  wstring command(strW(argv[1]));

  if(command.compare(L"password") == 0) {
    Password().parse(argc - 2, argv + 2);
    return 0;
  } else if(command.compare(L"show") == 0) {
    Show().parse(argc - 2, argv + 2);
    return 0;
  } else if(command.compare(L"find") == 0) {
    Find().parse(argc - 2, argv + 2);
    return 0;
  } else if(command.compare(L"user") == 0) {
    if(argc < 3) {
      printUserHelp();
      return 0;
    }
    wstring userCommand(strW(argv[2]));
    if(userCommand.compare(L"add") == 0) {
      AddUser().parse(argc - 3, argv + 3);
      return 0;
    } else if(userCommand.compare(L"delete") == 0) {
      RemoveUser().parse(argc - 3, argv + 3);
      return 0;
    }
    return 0;
  } else if (command.compare(L"proxy") == 0) {
    ProxyManager().parse(argc - 2, argv + 2);
    return 0;
  }

  // if we get here, print help
  printBasicHelp();
  return 0;
}

void printBasicHelp() {
  cout << "Please give me more information." << endl;
  cout << "I accept:" << endl;
  cout << "  password   : change a user's password." << endl;
  cout << "  show       : show a user's details."    << endl;
  cout << "  find       : find a user by name."      << endl;
  cout << "  user       : add or remove a user."     << endl;
  cout << "  proxy      : squid control."            << endl;
  
  cout << endl;
  cout << "Type 'admin <argument>' for more information about a" << endl;
  cout << "particular command." << endl;
}

void printUserHelp() {
  cout << "Please tell me what you'd like to do. Choose either " << endl;
  cout << "  add     : add a user to the system."        << endl;
  cout << "  remove  : remove a user from the system."   << endl;
}