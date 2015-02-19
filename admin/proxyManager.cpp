/* 
 * File:   proxyManager.cpp
 * Author: yvan
 * 
 * Created on February 15, 2015, 10:24 PM
 */

#include <iostream>
#include "proxyManager.h"
#include "utils/proxy.h"
#include "utils/convert.h"

using namespace std;
using namespace y::utils;

proxyManager & ProxyManager() {
  static proxyManager p;
  return p;
}

void proxyManager::printHelp() {
  cout << "I can help you control the Squid! You should enter " << endl;
  cout << "one of these: " << endl;
  cout << endl;
  cout << "--reset : reset the Squid to its default state"  << endl;
  cout << "--show  : show the status of all rooms" << endl;
  cout << "<room>  : find out the current status of a room" << endl;
  cout << "<room> CLOSED | FILTER | OPEN : change the status of a room" << endl;
  cout << endl; 
}

void proxyManager::parse(int argc, char ** argv) {
  if(argc < 1) {
    printHelp();
    return;
  } else {
    std::wstring arg(strW(argv[0]));
    if(arg.compare(L"--reset") == 0) {
      Proxy().reset().apply();
      return;
    } 
    
    if(arg.compare(L"--show") == 0) {
      container<y::data::row> rows;
      y::utils::Proxy().getAllRooms(rows);
      for (int i = 0; i < rows.elms(); i++) {
        wcout << rows[i][L"ID"].asString() << " is ";
        y::utils::proxy::STATUS status = (y::utils::proxy::STATUS)rows[i][L"status"].asInt();
        switch (status) {
          case y::utils::proxy::CLOSED: wcout << L"closed." << endl; break;
          case y::utils::proxy::FILTER: wcout << L"filtered." << endl; break;
          case y::utils::proxy::OPEN: wcout << L"open." << endl; break;
        }
      }
      return;
    }
    
    // other arguments are supposed to be rooms
    proxy::STATUS status = proxy::INVALID;
    status = y::utils::Proxy().status(arg);
    if(status == proxy::INVALID) {
      cout << "This room does not exist" << endl;
      return;
    } else {
      if(argc < 2) {
        // just display current status
        switch(status) {
          case proxy::OPEN  : wcout << arg << L" is open."     << endl; break;
          case proxy::FILTER: wcout << arg << L" is filtered." << endl; break;
          case proxy::CLOSED: wcout << arg << L" is closed."   << endl; break;
        }
      } else {
        wstring newStatus = strW(argv[1]);
        if(newStatus.compare(L"OPEN") == 0) {
          if(status == proxy::OPEN) {
            wcout << arg << L" is already open." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::OPEN);
            y::utils::Proxy().apply();
            wcout << arg << L" is now open." << endl;
            return;
          }
        }
        if(newStatus.compare(L"FILTER") == 0) {
          if(status == proxy::FILTER) {
            wcout << arg << L" is already filtered." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::FILTER);
            y::utils::Proxy().apply();
            wcout << arg << L" is now filtered." << endl;
            return;
          }
        }
        if(newStatus.compare(L"CLOSED") == 0) {
          if(status == proxy::CLOSED) {
            wcout << arg << L" is already closed." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::CLOSED);
            y::utils::Proxy().apply();
            wcout << arg << L" is now closed." << endl;
            return;
          }
        }
        
        // if we get here, the last argument was not valid
        cout << "This is not a valid status." << endl;
        return;
      }
    }
  }
}
