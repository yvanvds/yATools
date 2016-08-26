/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   viewAccount.h
 * Author: yvan
 *
 * Created on August 26, 2016, 4:22 PM
 */

#ifndef VIEWACCOUNT_H
#define VIEWACCOUNT_H

#include <Wt/WContainerWidget>
#include "ldap/account.h"
#include "ldap/server.h"

class viewAccount : public Wt::WContainerWidget {
public:
  viewAccount(y::ldap::server * server) : server(server) {}
  
  void create(y::ldap::account * account);
 
private:
  y::ldap::account * account;
  y::ldap::server * server;
  
};

#endif /* VIEWACCOUNT_H */

