/* 
 * File:   debugFunctions.cpp
 * Author: yvan
 * 
 * Created on May 10, 2015, 4:18 PM
 */

#include "debugFunctions.h"
#include "admintools.h"
#include <iostream>

#include <boost/locale.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>

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
  } else if(::string(argv[0]) == "cleanup") {
    cleanupClasses();
  } else if(::string(argv[0]) == "studentsToClasses") {
    reAddAllStudentsToClasses();
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

void debugFunctions::cleanupClasses() {
  y::ldap::server s;
  ACCOUNTS & accounts = s.getAccounts();
  CLASSES & classes = s.getClasses();
  for (int i =0; i < classes.elms(); i++) {
    std::cout << "Cleaning class " << classes[i].cn().get() << std::endl;
    
    // remove empty values
    classes[i].removeStudent(DN(""));
    
startover:

    for(auto it = classes[i].students().begin(); it != classes[i].students().end(); ++it) {
      std::cout << "  " << it->c_str() << std::endl;
      
      if(!s.hasAccount(DN(*it))) {
        std::cout << "removing..." << std::endl;
        classes[i].removeStudent(DN(*it));
        classes[i].flagForCommit();
        goto startover;
          
      } else {
        // account is found
        y::ldap::account & account = s.getAccount(DN(*it));
        if(account.schoolClass().get() != classes[i].cn().get()) {
          std::cout << "Moving..." << std::endl;
            
          // remove from current class
          classes[i].removeStudent(account.dn());
            
          // add to new class
          s.getClass(CN(account.schoolClass().get())).addStudent(account.dn());
          goto startover;
          
        }
      }
    
    }
  }
  
  s.commitChanges();
}

void debugFunctions::reAddAllStudentsToClasses() {
  y::ldap::server s;
  ACCOUNTS & accounts = s.getAccounts();
  CLASSES & classes = s.getClasses();
  for(int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].isStudent()) {
      ::string currentClass = accounts[i].schoolClass().get();
      
      if(currentClass.empty()) {
        std::cout << "This student has no class: " << std::endl;
        std::cout << accounts[i].dn().get() << std::endl;
        std::cout << "continue?";
        std::string input;
        std::cin >> input;
        if(input != "y") return;
      } else {
        schoolClass & sc = s.getClass(CN(currentClass));
        if(sc.addStudent(accounts[i].dn())) {
          std::cout << "Student added to class: " << std::endl;
          std::cout << accounts[i].dn().get() << std::endl;
        }
      }
      
      
    }
  }
  
  s.commitChanges();
}

void debugFunctions::testFunction() {
  y::utils::Log().useConsole(true);
  
  boost::locale::generator gen;
  std::locale utf8 = gen("en_US.UTF-8");
  ::string file = "accounts.csv";
  std::wifstream stream(file.utf8());
  
  bool firstAccount = true;
  
  std::wstring line;
  while(std::getline(stream, line)) {
    std::wstring id;
    std::wstring pw;
    int count = 0;
    for(int i = 0; i < line.size(); i++) {
      if (count < 3) {
        if(line[i] == ';') count++;
      } else {
        if(count == 3) {
          if(line[i] != ';') id += line[i];
          else count = 4;
        } else if(count == 4) {
          if(line[i] != ';') pw += line[i];
          else count = 5;
        } 
      }
    }
    
    boost::algorithm::trim(id);
    boost::algorithm::trim(pw);
    
    if(firstAccount) {
      std::wcout << "id: " << id << " pw1: " << pw << std::endl;
      y::Smartschool().setCoAccount(::string(id), ::string(pw), true);
    } else {
      std::wcout << "id: " << id << " pw2: " << pw << std::endl;
      y::Smartschool().setCoAccount(::string(id), ::string(pw), false);
    }
    firstAccount = !firstAccount;
  }
  

  y::utils::Log().add("end of program");
  //std::cin.get();
}