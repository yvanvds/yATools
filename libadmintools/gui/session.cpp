/* 
 * File:   session.cpp
 * Author: yvan
 * 
 * Created on May 18, 2014, 9:33 PM
 */

#include "session.h"

y::gui::session::session(const Wt::WEnvironment & env) : Wt::WApplication(env) {
  theme = new Wt::WBootstrapTheme();
  theme->setVersion(Wt::WBootstrapTheme::Version3);
  this->setTheme(theme); 
  
  loginDialog.create(this);
  loginDialog.show();
  
}

y::gui::passwordDialog & y::gui::session::login() {
  return loginDialog;
}