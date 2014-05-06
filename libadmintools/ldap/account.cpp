/* 
 * File:   account.cpp
 * Author: yvan
 * 
 * Created on January 14, 2014, 6:48 PM
 */

#include "ldap/account.h"

y::ldap::account::account() : 
  _new(true), 
  _uidNumber(UID_NUMBER(0)),
  _uid(UID("")),
  _dn(DN("")),
  _cn(CN("")),
  _sn(SN("")),
  _fullName(FULL_NAME("")),
  _homeDir(HOMEDIR("")),
  _wisaID(WISA_ID(0)),
  _mail(MAIL("")),
  _password(PASSWORD("")),
  _birthDay(DATE(DAY(1), MONTH(1), YEAR(1)))
  {}

bool y::ldap::account::load(const UID & id) {
  
}