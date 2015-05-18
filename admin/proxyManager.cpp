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
    ::string arg(argv[0]);
    if(arg == "--reset") {
      Proxy().reset().apply();
      return;
    } 
    
    if(arg == "--show") {
      container<y::data::row> rows;
      y::utils::Proxy().getAllRooms(rows);
      for (int i = 0; i < rows.elms(); i++) {
        cout << rows[i]["ID"].asString() << " is ";
        y::utils::proxy::STATUS status = (y::utils::proxy::STATUS)rows[i]["status"].asInt();
        switch (status) {
          case y::utils::proxy::CLOSED: cout << "closed." << endl; break;
          case y::utils::proxy::FILTER: cout << "filtered." << endl; break;
          case y::utils::proxy::OPEN: cout << "open." << endl; break;
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
          case proxy::OPEN  : cout << arg << " is open."     << endl; break;
          case proxy::FILTER: cout << arg << " is filtered." << endl; break;
          case proxy::CLOSED: cout << arg << " is closed."   << endl; break;
        }
      } else {
        ::string newStatus = argv[1];
        if(newStatus == "OPEN") {
          if(status == proxy::OPEN) {
            cout << arg << " is already open." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::OPEN);
            y::utils::Proxy().apply();
            cout << arg << " is now open." << endl;
            return;
          }
        }
        if(newStatus == "FILTER") {
          if(status == proxy::FILTER) {
            cout << arg << " is already filtered." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::FILTER);
            y::utils::Proxy().apply();
            cout << arg << " is now filtered." << endl;
            return;
          }
        }
        if(newStatus == "CLOSED") {
          if(status == proxy::CLOSED) {
            cout << arg << " is already closed." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::CLOSED);
            y::utils::Proxy().apply();
            cout << arg << " is now closed." << endl;
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
