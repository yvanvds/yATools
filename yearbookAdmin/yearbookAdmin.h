/* 
 * File:   yearbookAdmin.h
 * Author: yvan
 *
 * Created on May 18, 2014, 8:25 PM
 */

#ifndef YEARBOOKADMIN_H
#define	YEARBOOKADMIN_H

#include <Wt/WApplication>
#include <Wt/WBootstrapTheme>

#include <admintools.h>
#include "configuration.h"
#include "review.h"
#include "dataconnect.h"
#include "download.h"

class yearbookAdmin : public y::gui::session {
public:
  yearbookAdmin(const Wt::WEnvironment & env);
  virtual bool validate();
  virtual void onLogin();
  void onSelected();
  

  
  dataconnect db;
  
private:

  configuration * confPage;
  review * reviewPage;
  download * downloadPage;
};


#endif	/* YEARBOOKADMIN_H */

