/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on January 2, 2015, 7:05 PM
 */

#include <cstdlib>
#include "config.h"
using namespace std;


int main(int argc, char** argv) {
#ifndef DEBUG
  if(getuid()) {
    cout << "You must be root to execute this command!" << endl;
    return 0;
  }
#endif 
  cout << "Welcome to cockpit." << endl;
  
  // first check for config file
  Config().create();
  Config().save();
  
  return 0;
}

