/* 
 * File:   proxyManager.cpp
 * Author: yvan
 * 
 * Created on February 15, 2015, 10:24 PM
 */

#include <iostream>
#include "proxyManager.h"
#include "utils/proxy.h"

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
  cout << "<room>  : find out the current status of a room" << endl;
  cout << "<room> CLOSED | FILTER | OPEN : change the status of a room" << endl;
  cout << endl; 
}

void proxyManager::parse(int argc, char** argv) {
  if(argc < 1) {
    printHelp();
    return;
  } else {
    std::string arg(argv[0]);
    if(arg.compare("--reset") == 0) {
      Proxy().reset();
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
        string newStatus = argv[1];
        if(newStatus.compare("OPEN") == 0) {
          if(status == proxy::OPEN) {
            cout << arg << " is already open." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::OPEN);
            cout << arg << " is now open." << endl;
            return;
          }
        }
        if(newStatus.compare("FILTER") == 0) {
          if(status == proxy::FILTER) {
            cout << arg << " is already filtered." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::FILTER);
            cout << arg << " is now filtered." << endl;
            return;
          }
        }
        if(newStatus.compare("CLOSED") == 0) {
          if(status == proxy::CLOSED) {
            cout << arg << " is already closed." << endl;
            return;
          } else {
            y::utils::Proxy().status(arg, proxy::CLOSED);
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
