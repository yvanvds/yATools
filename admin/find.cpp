/* 
 * File:   find.cpp
 * Author: yvan
 * 
 * Created on February 10, 2015, 4:10 PM
 */

#include "find.h"
#include <iostream>
#include "admintools.h"

using namespace std;

::find & Find() {
  static ::find s;
  return s;
}

void ::find::printHelp() {
  cout << "I will help you find a user, even if you're not sure of its name." << endl;
  cout << "<cn> : presumed first name" << endl;
  cout << "<sn> : presumed last name" << endl;
}

void ::find::parse(int argc, char ** argv) {
  if (argc < 1) {
    printHelp();
    return;
  }
  
  ::string cn(argv[0]);
  ::string sn;
  std::vector<UID_NUMBER> results;
  y::ldap::server s;
  
  if (argc > 1) {
    sn = argv[1];
  }
  
  // try full name first
  if(!cn.empty() && !sn.empty()) {
    ::string query;
    query  = "(&(cn="; query += cn; 
    query += ")(sn=" ; query += sn; query += "))"; 
    if(s.findAccounts(query, results)) {
      cout << "Exact match:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = s.getAccount(results[i]);
        cout << "  " << account.fullName().get() << " (" << account.uid().get() << ")" << endl;
      }
      results.clear();
    } else {
      cout << "No exact match found" << endl;
    }
    
    cout << "Press enter to show similar results." << endl;
    cin.get();
    
    query  = "(&(cn~="; query += cn; 
    query += ")(sn~=" ; query += sn; query += "))"; 
    if(s.findAccounts(query, results)) {
      cout << "similar matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = s.getAccount(results[i]);
        cout << "  " << account.fullName().get() << " (" << account.uid().get() << ")" << endl;
      }
      results.clear();
    } else {
      cout << "No similar matches found" << endl;
      
    }
  }
    
  // try first name only
  if(!cn.empty()) {
    if(sn.empty() || y::utils::ask("Search on first name only?")) {
      ::string query;
      query  = "(cn="; query += cn; query += ")"; 
      if(s.findAccounts(query, results)) {
        cout << "Exact matches:" << endl;
        for(int i = 0; i < results.size(); i++) {
          y::ldap::account & account = s.getAccount(results[i]);
          cout << "  " << account.fullName().get() << " (" << account.uid().get() << ")" << endl;
        }
        results.clear();
      } else {
        cout << "No exact match found" << endl;
      }
    
      cout << "Press enter to show similar results." << endl;
      cin.get();
    
      query  = "(cn~="; query += cn; query += ")"; 
      if(s.findAccounts(query, results)) {
        cout << "similar matches:" << endl;
        for(int i = 0; i < results.size(); i++) {
          y::ldap::account & account = s.getAccount(results[i]);
          cout << "  " << account.fullName().get() << " (" << account.uid().get() << ")" << endl;
        }
        results.clear();
      } else {
        cout << "No similar matches found" << endl;
      }
    }
  }
  
  // try last name
  if(!sn.empty() && y::utils::ask("Search on last name only?")) {
    ::string query;
    query  = "(sn="; query += sn; query += ")"; 
    if(s.findAccounts(query, results)) {
      cout << "Exact matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = s.getAccount(results[i]);
        cout << "  " << account.fullName().get() << " (" << account.uid().get() << ")" << endl;
      }
      results.clear();
    } else {
      cout << "No exact match found" << endl;
    }

    cout << "Press enter to show similar results." << endl;
    cin.get();

    query  = "(sn~="; query += sn; query += ")"; 
    if(s.findAccounts(query, results)) {
      cout << "similar matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = s.getAccount(results[i]);
        cout << "  " << account.fullName().get() << " (" << account.uid().get() << ")" << endl;
      }
      results.clear();
    } else {
      cout << "No similar matches found" << endl;
    }
  } 
}