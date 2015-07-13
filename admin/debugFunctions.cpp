/* 
 * File:   debugFunctions.cpp
 * Author: yvan
 * 
 * Created on May 10, 2015, 4:18 PM
 */

#include "debugFunctions.h"
#include "admintools.h"
#include <iostream>

using namespace std;
using namespace y::ldap;



debugFunctions & DebugFunctions() {
  static debugFunctions s;
  return s;
}

void debugFunctions::printHelp() {
  cout << "You should never use these!!!" << std::endl;
  cout << "  removeAllStudents" << std::endl;
  cout << "  groupsToSmartschool" << std::endl;
  cout << "  convert" << std::endl;
}

void debugFunctions::parse(int argc, char ** argv) {
  if(argc < 1) {
    printHelp();
    return;
  }
  
  if(::string(argv[0]) == "removeAllStudents") {
    removeAllStudents();
  } else if(::string(argv[0]) == "groupsToSmartschool") {
    groupsToSmartschool();
  } else if(::string(argv[0]) == "test") {
    testFunction();
  }
}

void debugFunctions::removeAllStudents() {
  y::ldap::server s;
  ACCOUNTS & accounts = s.getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].groupID().get() == 1000) {
      accounts[i].flagForRemoval();
    }
  }
  
  s.commitChanges();
}

void debugFunctions::groupsToSmartschool() {
  y::ldap::server s;
  CLASSES & classes = s.getClasses();
  for(int i = 0; i < classes.elms(); i++) {
    y::Smartschool().addClass(classes[i]);
    std::cout << "Adding class: " << classes[i].cn().get() << std::endl;
  }
  
  /*ACCOUNTS & accounts = s.getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].groupID()() == 1000) {
      y::Smartschool().addUserToGroup(accounts[i], accounts[i].group()(), false);
      std::cout << "Adding " << accounts[i].fullName()() << " to group " << accounts[i].group()() << std::endl;
    }
  }*/
}

void debugFunctions::testFunction() {
  y::utils::Log().useConsole(true);
  y::ldap::server server;
  
  y::ldap::account & acc = server.getAccount(UID("abh"));
  acc.stemID(STEM_ID(1300002));
  
  server.commitChanges();
  
  std::cin.get();
}