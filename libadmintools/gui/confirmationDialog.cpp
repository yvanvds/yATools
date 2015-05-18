/* 
 * File:   confirmationDialog.cpp
 * Author: yvan
 * 
 * Created on May 24, 2014, 1:20 PM
 */

#include <Wt/WObject>

#include "confirmationDialog.h"

y::gui::confirmationDialog::confirmationDialog(const Wt::WString& title) {
  dialog = new Wt::WDialog(title);
  text = new Wt::WText("", dialog->contents());
  cancel = new Wt::WPushButton("annuleer", dialog->footer());
  ok = new Wt::WPushButton("ok", dialog->footer());
  
  this->addChild(dialog);
  this->addChild(text);
  this->addChild(cancel);
  this->addChild(ok);
  
  ok->clicked().connect(dialog, &Wt::WDialog::accept);
  cancel->clicked().connect(dialog, &Wt::WDialog::reject);
  dialog->rejectWhenEscapePressed(true);
  
  dialog->finished().connect(this, &confirmationDialog::handleResult);
}

y::gui::confirmationDialog::~confirmationDialog() {
  dialog->hide();
}

void y::gui::confirmationDialog::setContents(const Wt::WString& text) {
  this->text->setText(text);
}

void y::gui::confirmationDialog::handleCancel() {
  
}

void y::gui::confirmationDialog::show() {
  dialog->show();
}

void y::gui::confirmationDialog::handleResult(Wt::WDialog::DialogCode code) {
  if(code == Wt::WDialog::Accepted) {
    handleOK();
  } else {
    handleCancel();
  }
}