/* 
 * File:   authWidget.cpp
 * Author: yvan
 * 
 * Created on June 13, 2015, 8:23 PM
 */

#include "authWidget.h"
#include <Wt/Auth/LostPasswordWidget>
#include <Wt/Auth/AuthModel>

authWidget::authWidget(userSession& s) 
  : Wt::Auth::AuthWidget(userSession::auth(), s.users(), s.login())
  , _session(s) 
{}

void authWidget::createLoginView() {
  
  this->setTemplateText(tr("Wt.Auth.template.login"));
  createPasswordLoginView();
}

Wt::WWidget * authWidget::createLostPasswordView() {
  Wt::WWidget * widget = new Wt::Auth::LostPasswordWidget(this->model()->users(), *(this->model())->baseAuth());
  widget->setWidth(500);
  return widget;
}