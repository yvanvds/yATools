/* 
 * File:   removeGroup.cpp
 * Author: yvan
 * 
 * Created on May 7, 2015, 1:55 PM
 */

#include "removeGroup.h"
#include <string>
#include <iostream>
#include "ldap/server.h"
#include "utils/convert.h"

using namespace std;
using namespace y::ldap;

removeGroup & RemoveGroup() {
  static removeGroup g;
  return g;
}

void removeGroup::printHelp() {
  cout << "With this you can remove a group from ldap." << endl;
  cout << endl;
  cout << "Usage: admin group remove [-e] <gid>" << endl;
  cout << endl;
  cout << "<gid>     name of this group" << endl;
  cout << "-e        search for an editable group" << endl;
}

void removeGroup::parse(int argc, char** argv) {
  if (argc < 1) {
    printHelp();
    return;
  }
  
  ::string arg(argv[0]);
  ::string name;
  bool editable = false;
  
  if(arg == "-e") {
    if(argc < 2) {
      printHelp();
      return;
    } else {
      name = argv[1];
      editable = true;
    }
  } else {
    name = arg;
  }
  
  group & grp = Server().getGroup(name, editable);
  
  if(grp.isNew()) {
    cout << "This group does not exist." << endl;
    return;
  }
  
  grp.flagForRemoval();
  grp.flagForCommit();
  Server().commitChanges();
  cout << "Group " << name << " deleted." << endl;
}