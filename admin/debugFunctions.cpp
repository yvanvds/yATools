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
  cout << "  resetStemID" << std::endl;
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
  } else if(::string(argv[0]) == "resetStemID") {
    resetStemID();
  }
}

void debugFunctions::resetStemID() {
  y::ldap::server s;
  ACCOUNTS & accounts = s.getAccounts();
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].role().get() == ROLE::STUDENT) {
      std::cout << "changing " << accounts[i].fullName().get() << std::endl;
      accounts[i].postalCode(POSTAL_CODE("10"));
    }
  }
  s.commitChanges();
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
    y::Smartschool().saveClass(classes[i]);
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
  
  y::ldap::account & account = server.getAccount(UID("abeh"));
  account.schoolClass(account.schoolClass());
  
//  for(int i = 0; i < accounts.elms(); i++) {
//    if(accounts[i].isStudent()) {
//      accounts[i].schoolClass(accounts[i].schoolClass());
//    }
//  }
  
  server.commitChanges();
  y::utils::Log().add("end of program");
  //std::cin.get();
}