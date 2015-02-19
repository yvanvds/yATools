/* 
 * File:   removeUser.cpp
 * Author: yvan
 * 
 * Created on February 12, 2015, 10:03 PM
 */

#include "removeUser.h"
#include <string>
#include <iostream>
#include "ldap/server.h"
#include "utils/config.h"
#include "samba/samba.h"
#include "utils/convert.h"

using namespace std;
using namespace y::ldap;

removeUser & RemoveUser() {
  static removeUser s;
  return s;
}

void removeUser::printHelp() {
  cout << "With this you can remove a user from ldap and delete its homedirectory." << endl;
  cout << "To really hurt it, this will also delete its gmail account." << endl;
  cout << endl;
  cout << "Usage: admin user remove <uid>" << endl;
  cout << endl;
  cout << "<uid> the ldap ID of this user" << endl;
}

void removeUser::parse(int argc, char ** argv) {
  if (argc < 1) {
    printHelp();
    return;
  }
  
  std::wstring uid(strW(argv[0]));
  account & acc = Server().getAccount(UID(uid));
  if(acc.isNew()) {
    cout << "This user has already entered the void." << endl;
    return;
  }
  
  // if we get here, the user exists
  
  // if personeel, remove from that group
  if (acc.group()().compare(L"personeel") == 0 || acc.group()().compare(L"directie")) {
    group & personeel = Server().getGroup(CN(L"personeel"), true);
    container<std::wstring> & members = personeel.members();
    for(int i = 0; i < members.elms(); i++) {
      if (members[i].compare(acc.mail()()) == 0) {
        members.remove(i);
        personeel.flagForCommit();
        break;
      }
      // for historical reasons members might be added with uid
      std::wstring mail(uid);
      uid += L"@";
      uid += y::utils::Config().getDomain();
      if(members[i].compare(mail) == 0) {
        members.remove(i);
        personeel.flagForCommit();
        break;
      }
    }
  }
  
  // remove from class group
  if(acc.group()().compare(L"extern") != 0 && acc.group()().compare(L"externmail") != 0) {
    group & classGroup = Server().getGroup(CN(acc.group()()), false);
    container<std::wstring> & members = classGroup.members();
    for(int i = 0; i < members.elms(); i++) {
      if(members[i].compare(acc.dn()()) == 0) {
        members.remove(i);
        classGroup.flagForCommit();
        break;
      }
    }
  }
  
  y::samba::delUser(acc);
  Server().commitChanges();
}

