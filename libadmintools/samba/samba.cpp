/* 
 * File:   samba.cpp
 * Author: yvan
 * 
 * Created on August 19, 2014, 9:15 PM
 */

#include "samba.h"
#include "../system/process.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "utils/convert.h"

string groupName(const GID_NUMBER & id) {
  if(id() ==   525) return "personeel";
  if(id() == 20009) return "extern"   ;
  
  // of none of the above, calculate according to year
  string result("y");
  auto now = std::chrono::system_clock::now();
  time_t tt = std::chrono::system_clock::to_time_t(now);
  tm local_time = *std::localtime(&tt);
  int year = 1900 + local_time.tm_year;
  result += year;
  return result;
}

void y::samba::changePassword(const string & user, const string & password) {
  string command("sudo /usr/sbin/smbldap-passwd -p ");
  command += user + " ";
  command += password;
  /*if(!y::sys::Exec(command, y::sys::stdOut)) {
    assert(false);
  }*/
  command.execute();
}

void y::samba::addUser(const ldap::account & account) { 
  string command("sudo /usr/sbin/smbldap-useradd -a -g ");
  command += account.groupID()();
  command += " -m -d /home/";
  command += groupName(account.groupID());
  command += "/";
  command += account.uid()();
  command += " -o ou=";
  command += groupName(account.groupID());
  command += " -C '\\\\ATSCHOOL\\homes' -D 'H:' -E ' STARTUP.BAT' -F";
  command += " '\\\\ATSCHOOL\\profiles\\Default' -H '[U]' ";
  command += account.uid()();
  /*if(!y::sys::Exec(command, y::sys::stdOut)) {
    assert(false);
  }*/
  command.execute();
}

void y::samba::delUser(const ldap::account& account) {
  string command("sudo /usr/sbin/smbldap-userdel -r " + account.uid()());
  command.execute();
}