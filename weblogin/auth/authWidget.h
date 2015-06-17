/* 
 * File:   authWidget.h
 * Author: yvan
 *
 * Created on June 13, 2015, 8:23 PM
 */

#ifndef AUTHWIDGET_H
#define	AUTHWIDGET_H

#include <Wt/Auth/AuthWidget>
#include <Wt/WWidget>
#include "session.h"

class authWidget : public Wt::Auth::AuthWidget {
public:
  authWidget(userSession & s);
  virtual Wt::WWidget * createLostPasswordView();
protected:
  virtual void createLoginView();
   
  
private:
  userSession & _session;
};

#endif	/* AUTHWIDGET_H */

