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
#include "utils/convert.h"

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
  
  std::wstring cn(strW(argv[0]));
  std::wstring sn;
  std::vector<y::ldap::UID_NUMBER> results;
  
  if (argc > 1) {
    sn = strW(argv[1]);
  }
  
  // try full name first
  if(!cn.empty() && !sn.empty()) {
    std::wstring query;
    query  = L"(&(cn="; query += cn; 
    query += L")(sn=" ; query += sn; query += L"))"; 
    if(y::ldap::Server().findAccounts(query, results)) {
      cout << "Exact match:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
        wcout << L"  " << account.fullName()() << L" (" << account.uid()() << L")" << endl;
      }
      results.clear();
    } else {
      cout << "No exact match found" << endl;
    }
    
    cout << "Press enter to show similar results." << endl;
    cin.get();
    
    query  = L"(&(cn~="; query += cn; 
    query += L")(sn~=" ; query += sn; query += L"))"; 
    if(y::ldap::Server().findAccounts(query, results)) {
      cout << "similar matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
        wcout << L"  " << account.fullName()() << L" (" << account.uid()() << L")" << endl;
      }
      results.clear();
    } else {
      cout << "No similar matches found" << endl;
      
    }
  }
    
  // try first name only
  if(!cn.empty()) {
    if(sn.empty() || y::utils::ask("Search on first name only?")) {
      std::wstring query;
      query  = L"(cn="; query += cn; query += L")"; 
      if(y::ldap::Server().findAccounts(query, results)) {
        cout << "Exact matches:" << endl;
        for(int i = 0; i < results.size(); i++) {
          y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
          wcout << L"  " << account.fullName()() << L" (" << account.uid()() << L")" << endl;
        }
        results.clear();
      } else {
        cout << "No exact match found" << endl;
      }
    
      cout << "Press enter to show similar results." << endl;
      cin.get();
    
      query  = L"(cn~="; query += cn; query += L")"; 
      if(y::ldap::Server().findAccounts(query, results)) {
        cout << "similar matches:" << endl;
        for(int i = 0; i < results.size(); i++) {
          y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
          wcout << L"  " << account.fullName()() << L" (" << account.uid()() << L")" << endl;
        }
        results.clear();
      } else {
        cout << "No similar matches found" << endl;
      }
    }
  }
  
  // try last name
  if(!sn.empty() && y::utils::ask("Search on last name only?")) {
    std::wstring query;
    query  = L"(sn="; query += sn; query += L")"; 
    if(y::ldap::Server().findAccounts(query, results)) {
      cout << "Exact matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
        wcout << L"  " << account.fullName()() << L" (" << account.uid()() << L")" << endl;
      }
      results.clear();
    } else {
      cout << "No exact match found" << endl;
    }

    cout << "Press enter to show similar results." << endl;
    cin.get();

    query  = L"(sn~="; query += sn; query += L")"; 
    if(y::ldap::Server().findAccounts(query, results)) {
      cout << "similar matches:" << endl;
      for(int i = 0; i < results.size(); i++) {
        y::ldap::account & account = y::ldap::Server().getAccount(results[i]);
        wcout << L"  " << account.fullName()() << L" (" << account.uid()() << L")" << endl;
      }
      results.clear();
    } else {
      cout << "No similar matches found" << endl;
    }
  }
  
  
}