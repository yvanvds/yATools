/* 
 * File:   studentPasswords.h
 * Author: yvan
 *
 * Created on July 15, 2015, 4:28 PM
 */

#ifndef STUDENTPASSWORDS_H
#define	STUDENTPASSWORDS_H

#include <Wt/WContainerWidget>
#include <Wt/WAnchor>
#include <Wt/WProgressBar>
#include "ldap/server.h"
#include "utils/string.h"
#include "passwordFile.h"

class studentPasswords : public Wt::WContainerWidget {
public:
  studentPasswords(y::ldap::server * server) : server(server) {}

  
  void create();
  
private:
  void showClass(string schoolClass);
  void changePasswords();
  void reset();
  
  y::ldap::server * server;
  Wt::WContainerWidget * buttons;
  Wt::WTable * table;
  Wt::WAnchor * anchor;
  Wt::WProgressBar * progress;
  
  string currentClass;
  
  passwordFile pfile;
};

#endif	/* STUDENTPASSWORDS_H */

