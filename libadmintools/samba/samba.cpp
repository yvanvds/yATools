/* 
 * File:   samba.cpp
 * Author: yvan
 * 
 * Created on August 19, 2014, 9:15 PM
 */

#include "samba.h"
#include "../system/process.h"
#include <string>

void y::samba::changePassword(const std::string & user, const std::string & password) {
  std::string command = "echo ";
  command.append(password);
  command.append(" | /usr/sbin/smbldap-passwd -p ");
  command.append(user);
  if(!y::sys::Exec(command, y::sys::stdOut)) {
    assert(false);
  }
}

void y::samba::addUser(const ldap::account & account) { 
  std::string command = "/usr/sbin/smbldap-useradd -a -g ";
  command.append(std::to_string(account.groupID()()));
  command.append(" -m -d /home/");
  command.append(account.group()());
  command.append(" -C '\\\\ATSCHOOL\\homes' -D 'H:' -E ' STARTUP.BAT' -F");
  command.append(" '\\\\ATSCHOOL\\profiles\\Default' -H '[U]' ");
  command.append(account.uid()());
  if(!y::sys::Exec(command, y::sys::stdOut)) {
    assert(false);
  }
}

void y::samba::delUser(const ldap::account& account) {
  std::string command = "/usr/sbin/smbldap-userdel -r ";
  command.append(account.uid()());
  if(!y::sys::Exec(command, y::sys::stdOut)) {
    assert(false);
  }
}