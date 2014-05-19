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


class yearbookAdmin : public y::gui::session {
public:
  yearbookAdmin(const Wt::WEnvironment & env);
  virtual bool validate();
  virtual void onLogin();
private:

  
};


#endif	/* YEARBOOKADMIN_H */

