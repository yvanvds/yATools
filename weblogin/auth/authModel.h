/* 
 * File:   authModel.h
 * Author: yvan
 *
 * Created on June 14, 2015, 2:48 PM
 */

#ifndef AUTHMODEL_H
#define	AUTHMODEL_H

#include <Wt/Auth/AuthModel>
#include "session.h"

class authModel : public Wt::Auth::AuthModel {
public:
  authModel(userSession & s, Wt::WObject * parent = 0);
  
  bool validateField(Field field);
  
private:
  y::ldap::server ldapServer;
};

#endif	/* AUTHMODEL_H */

