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

std::string groupName(const y::ldap::GID_NUMBER & id) {
  if(id() ==   525) return "personeel";
  if(id() == 20009) return "extern"   ;
  
  // of none of the above, calculate according to year
  std::string result("y");
  auto now = std::chrono::system_clock::now();
  time_t tt = std::chrono::system_clock::to_time_t(now);
  tm local_time = *std::localtime(&tt);
  int year = 1900 + local_time.tm_year;
  result += std::to_string(year);
  return result;
}

void y::samba::changePassword(const std::wstring & user, const std::wstring & password) {
  std::string command = "sudo /usr/sbin/smbldap-passwd -p ";
  command.append(str8(user));
  command.append(" ");
  command.append(str8(password));
  /*if(!y::sys::Exec(command, y::sys::stdOut)) {
    assert(false);
  }*/
  system(command.c_str());
}

void y::samba::addUser(const ldap::account & account) { 
  std::string command = "/usr/sbin/smbldap-useradd -a -g ";
  command.append(std::to_string(account.groupID()()));
  command.append(" -m -d /home/");
  command.append(groupName(account.groupID()));
  command.append("/");
  command.append(str8(account.uid()()));
  command.append(" -o ou=");
  command.append(groupName(account.groupID()));
  command.append(" -C '\\\\ATSCHOOL\\homes' -D 'H:' -E ' STARTUP.BAT' -F");
  command.append(" '\\\\ATSCHOOL\\profiles\\Default' -H '[U]' ");
  command.append(str8(account.uid()()));
  /*if(!y::sys::Exec(command, y::sys::stdOut)) {
    assert(false);
  }*/
  system(command.c_str());
}

void y::samba::delUser(const ldap::account& account) {
  std::string command = "/usr/sbin/smbldap-userdel -r ";
  command.append(str8(account.uid()()));
  std::cout << command << endl;
  if(!y::sys::Exec(command, y::sys::stdOut)) {
    assert(false);
  }
}