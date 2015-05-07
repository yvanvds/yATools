/* 
 * File:   addGroup.cpp
 * Author: yvan
 * 
 * Created on May 7, 2015, 2:06 PM
 */

#include <string>
#include <iostream>
#include "addGroup.h"
#include "ldap/server.h"
#include "utils/convert.h"

using namespace std;
using namespace y::ldap;

addGroup & AddGroup() {
  static addGroup g;
  return g;
}

void addGroup::printHelp() {
  cout << "Add a group to the ldap database." << endl;
  cout << endl;
  cout << "Usage: admin group add [-e] <gid>" << endl;
  cout << endl;
  cout << "<gid>     name for this group" << endl;
  cout << "-e        make this an editable group" << endl;
}

void addGroup::parse(int argc, char** argv) {
  if(argc < 1) {
    printHelp();
    return;
  }
  
  std::wstring arg(strW(argv[0]));
  std::wstring name;
  bool editable = false;
  
  if(arg.compare(L"-e") == 0) {
    if(argc < 2) {
      printHelp();
      return;
    } else {
      name = strW(argv[1]);
      editable = true;
    }
  } else {
    name = arg;
  }
  
  group & grp = Server().getGroup(CN(name), editable);
  if(!grp.isNew()) {
    cout << "This group already exists." << endl;
    return;
  } else {
    grp.flagForCommit();
    Server().commitChanges();
    cout << "Group " << str8(name) << " added." << endl; 
  }
}