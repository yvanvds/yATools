/* 
 * File:   debugFunctions.cpp
 * Author: yvan
 * 
 * Created on May 10, 2015, 4:18 PM
 */

#include "debugFunctions.h"
#include "ldap/server.h"
#include "ldap/account.h"
#include "smartschool/smartschool.h"
#include "utils/convert.h"
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
  
  if(std::string(argv[0]).compare("removeAllStudents") == 0) {
    removeAllStudents();
  } else if(std::string(argv[0]).compare("groupsToSmartschool") == 0) {
    groupsToSmartschool();
  } else if(std::string(argv[0]).compare("convert") == 0) {
    convertToNewAccount();
  }
}

void debugFunctions::removeAllStudents() {
  container<account> & accounts = Server().getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].groupID()() == 1000) {
      accounts[i].flagForRemoval();
    }
  }
  
  Server().commitChanges();
}

void debugFunctions::convertToNewAccount() {
  container<account> & accounts = Server().getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    accounts[i].convertToNewAccount();
  }
}

void debugFunctions::groupsToSmartschool() {
  container<group> & groups = Server().getGroups();
  for(int i = 0; i < groups.elms(); i++) {
    if(!groups[i].editable()) {
      y::Smartschool().addClass(groups[i]);
      std::cout << "Adding group: " << str8(groups[i].cn()) << std::endl;
    }
  }
  
  container<account> & accounts = Server().getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].groupID()() == 1000) {
      y::Smartschool().addUserToGroup(accounts[i], str8(accounts[i].group()()), false);
      std::cout << "Adding " << str8(accounts[i].fullName()()) << " to group " << str8(accounts[i].group()()) << std::endl;
    }
  }
}

