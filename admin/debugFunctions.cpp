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
  } else if(::string(argv[0]) == "convert") {
    convertToNewAccount();
  }
}

void debugFunctions::removeAllStudents() {
  y::ldap::server s;
  ACCOUNTS & accounts = s.getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].groupID()() == 1000) {
      accounts[i].flagForRemoval();
    }
  }
  
  s.commitChanges();
}

void debugFunctions::convertToNewAccount() {
  y::ldap::server s;
  ACCOUNTS & accounts = s.getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    accounts[i].convertToNewAccount();
  }
  
}

void debugFunctions::groupsToSmartschool() {
  y::ldap::server s;
  GROUPS & groups = s.getGroups();
  for(int i = 0; i < groups.elms(); i++) {
    if(!groups[i].editable()) {
      y::Smartschool().addClass(groups[i]);
      std::cout << "Adding group: " << groups[i].cn() << std::endl;
    }
  }
  
  ACCOUNTS & accounts = s.getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].groupID()() == 1000) {
      y::Smartschool().addUserToGroup(accounts[i], accounts[i].group()(), false);
      std::cout << "Adding " << accounts[i].fullName()() << " to group " << accounts[i].group()() << std::endl;
    }
  }
}

