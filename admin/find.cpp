/* 
 * File:   find.cpp
 * Author: yvan
 * 
 * Created on February 10, 2015, 4:10 PM
 */

#include "find.h"
#include <iostream>
#include "ldap/server.h"
#include "utils/console.h"

using namespace std;

::find & Find() {
  static ::find s;
  return s;
}

void ::find::printHelp() {
  cout << "Find will help you find a user, even if you're not sure of its name." << endl;
  cout << "first argument            : presumed first name" << endl;
  cout << "second argument (optional): presumed last name" << endl;
}

void ::find::parse(int argc, char** argv) {
  if (argc < 3) {
    printHelp();
    return;
  }
  
  std::string cn(argv[2]);
  std::string sn;
  std::vector<y::ldap::UID_NUMBER> results;
  
  if (argc > 3) {
    sn = argv[3];
  }
  
  // try full name first
  if(!cn.empty() && !sn.empty()) {
    std::string query;
    query  = "(&(cn="; query += cn; 
    query += ")(sn=" ; query += sn; query += "))"; 
    if(y::ldap::Server().findAccounts(query, results)) {
      cout << "Exact match:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
        cout << "  " << account.fullName()() << " (" << account.uid()() << ")" << endl;
      }
      results.clear();
    } else {
      cout << "No exact match found" << endl;
    }
    
    cout << "Press enter to show similar results." << endl;
    cin.get();
    
    query  = "(&(cn~="; query += cn; 
    query += ")(sn~=" ; query += sn; query += "))"; 
    if(y::ldap::Server().findAccounts(query, results)) {
      cout << "similar matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
        cout << "  " << account.fullName()() << " (" << account.uid()() << ")" << endl;
      }
      results.clear();
    } else {
      cout << "No similar matches found" << endl;
      
    }
  }
    
  // try first name only
  if(!cn.empty()) {
    if(sn.empty() || y::utils::ask("Search on first name only?")) {
      std::string query;
      query  = "(cn="; query += cn; query += ")"; 
      if(y::ldap::Server().findAccounts(query, results)) {
        cout << "Exact matches:" << endl;
        for(int i = 0; i < results.size(); i++) {
          y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
          cout << "  " << account.fullName()() << " (" << account.uid()() << ")" << endl;
        }
        results.clear();
      } else {
        cout << "No exact match found" << endl;
      }
    
      cout << "Press enter to show similar results." << endl;
      cin.get();
    
      query  = "(cn~="; query += cn; query += ")"; 
      if(y::ldap::Server().findAccounts(query, results)) {
        cout << "similar matches:" << endl;
        for(int i = 0; i < results.size(); i++) {
          y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
          cout << "  " << account.fullName()() << " (" << account.uid()() << ")" << endl;
        }
        results.clear();
      } else {
        cout << "No similar matches found" << endl;
      }
    }
  }
  
  // try last name
  if(!sn.empty() && y::utils::ask("Search on last name only?")) {
    std::string query;
    query  = "(sn="; query += sn; query += ")"; 
    if(y::ldap::Server().findAccounts(query, results)) {
      cout << "Exact matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
        cout << "  " << account.fullName()() << " (" << account.uid()() << ")" << endl;
      }
      results.clear();
    } else {
      cout << "No exact match found" << endl;
    }

    cout << "Press enter to show similar results." << endl;
    cin.get();

    query  = "(sn~="; query += sn; query += ")"; 
    if(y::ldap::Server().findAccounts(query, results)) {
      cout << "similar matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
        cout << "  " << account.fullName()() << " (" << account.uid()() << ")" << endl;
      }
      results.clear();
    } else {
      cout << "No similar matches found" << endl;
    }
  }
  
  
}