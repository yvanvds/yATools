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
#include "renameUser.h"
#include "addGroup.h"
#include "removeGroup.h"
#include "proxyManager.h"
#include "debugFunctions.h"
#include "smartschool/smartschool.h"
#include "ldap/server.h"
#include "utils/convert.h"
#include <boost/locale.hpp>
#include "utils/string.h"

using namespace std;

void printBasicHelp();
void printUserHelp ();
void printGroupHelp();

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
  
  ::string command(argv[1]);

  if(command == "password") {
    Password().parse(argc - 2, argv + 2);
    return 0;
  } else if(command == "show") {
    Show().parse(argc - 2, argv + 2);
    return 0;
  } else if(command == "find") {
    Find().parse(argc - 2, argv + 2);
    return 0;
  } else if(command == "user") {
    if(argc < 3) {
      printUserHelp();
      return 0;
    }
    ::string userCommand(argv[2]);
    if(userCommand == "add") {
      AddUser().parse(argc - 3, argv + 3);
      return 0;
    } else if(userCommand == "delete") {
      RemoveUser().parse(argc - 3, argv + 3);
      return 0;
    } else if (userCommand == "rename") {
      RenameUser().parse(argc -3, argv + 3);
      return 0;
    }
    
  } else if (command == "proxy") {
    ProxyManager().parse(argc - 2, argv + 2);
    return 0;
  } else if (command == "group") {
    if(argc < 3) {
      printGroupHelp();
      return 0;
    }
    ::string groupCommand(argv[2]);
    if(groupCommand == "add") {
      AddGroup().parse(argc - 3, argv + 3);
      return 0;
    } else if (groupCommand == "delete") {
      RemoveGroup().parse(argc - 3, argv + 3);
      return 0;
    }
  } else if (command == "debug") {
    DebugFunctions().parse(argc - 2, argv + 2);
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
  cout << "  user       : add or delete a user."     << endl;
  cout << "  proxy      : squid control."            << endl;
  
  cout << endl;
  cout << "Type 'admin <argument>' for more information about a" << endl;
  cout << "particular command." << endl;
}

void printUserHelp() {
  cout << "Please tell me what you'd like to do. Choose either " << endl;
  cout << "  add     : add a user to the system."        << endl;
  cout << "  delete  : delete a user from the system."   << endl;
  cout << "  rename  : change a user's first name and name." << endl;
}

void printGroupHelp() {
  cout << "Please tell me what you'd like to do. Choose either " << endl;
  cout << "  add     : add a group to the system."       << endl;
  cout << "  delete  : delete a group from the system."  << endl;
}