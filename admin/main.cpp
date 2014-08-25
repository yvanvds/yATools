/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on August 20, 2014, 5:22 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <unistd.h>
#include "utils/config.h"
#include "password.h"

using namespace std;

void printBasicHelp();

int main(int argc, char** argv) {
  if(getuid()) {
    cout << "You must be root to execute this command!" << endl;
    return 0;
  }
  
  if(argc < 2) {
    printBasicHelp();
    return 0;
  }
  
  y::utils::Config().load();
  string command(argv[1]);

  if(command.compare("password") == 0) {
    Password().parse(argc, argv);
    return 0;
  }

  // if we get here, print help
  printBasicHelp();
  return 0;
}

void printBasicHelp() {
  cout << "The admin program can be used for user easy system administration." << endl;
  cout << "The first argument specifies what part of the admin interface will" << endl;
  cout << "be used." << endl << endl;
  cout << "Possible arguments are:" << endl;
  cout << "password   : change a user's password." << endl;
  
  cout << endl;
  cout << "Type admin <argument> -? for more information about a" << endl;
  cout << "particular command." << endl;
}