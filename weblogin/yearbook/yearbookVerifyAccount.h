/* 
 * File:   yearbookVerifyAccount.h
 * Author: yvan
 *
 * Created on May 12, 2015, 1:45 PM
 */

#ifndef YEARBOOKVERIFYACCOUNT_H
#define	YEARBOOKVERIFYACCOUNT_H

#include "gui/stackPage.h"
#include "yearbookDB.h"

class yearbookVerifyAccount : public y::gui::stackPage {
public:
  yearbookVerifyAccount(yearbookDB * ptr) : db(ptr) {}
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
  bool onNext();
  
private:
  void nameEditChanged();
  void surnameEditChanged();
  void groupEditChanged();
  void dateEditChanged();
  void mailEditChanged();
  
  yearbookDB * db;
  
  Wt::WTable * table;
  Wt::WLineEdit * nameEdit;
  Wt::WLineEdit * surnameEdit;
  Wt::WLineEdit * groupEdit;
  Wt::WDateEdit * dateEdit;
  Wt::WLineEdit * mailEdit;
  Wt::WText * feedback;
  
  bool allOK;  
  
};

#endif	/* YEARBOOKVERIFYACCOUNT_H */

