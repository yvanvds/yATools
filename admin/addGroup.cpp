/* 
 * File:   addGroup.cpp
 * Author: yvan
 * 
 * Created on May 7, 2015, 2:06 PM
 */

#include <iostream>
#include "addGroup.h"
#include "admintools.h"

using namespace std;
using namespace y::ldap;

addGroup & AddGroup() {
  static addGroup g;
  return g;
}

void addGroup::printHelp() {
  cout << "Add a group to the ldap database."     << endl;
  cout                                            << endl;
  cout << "Usage: admin group add [-e] <gid>"     << endl;
  cout                                            << endl;
  cout << "<gid>     name for this group"         << endl;
  cout << "-e        make this an editable group" << endl;
}

void addGroup::parse(int argc, char** argv) {
  if(argc < 1) {
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
  
  y::ldap::server server;
  group & grp = server.getGroup(CN(name), editable);
  if(!grp.isNew()) {
    cout << "This group already exists." << endl;
    return;
  } else {
    grp.flagForCommit();
    server.commitChanges();
    cout << "Group " << name << " added." << endl; 
  }
}