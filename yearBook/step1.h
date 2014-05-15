/* 
 * File:   step1.h
 * Author: yvan
 *
 * Created on May 13, 2014, 8:24 PM
 */

#ifndef STEP1_H
#define	STEP1_H

#include "step.h"
#include <Wt/WTable>
#include <Wt/WDateEdit>

class step1 : public step {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  
private:
 
  void nameEditChanged();
  void surnameEditChanged();
  void groupEditChanged();
  void dateEditChanged();
  void mailEditChanged();
    
  Wt::WTable * table;
  
  Wt::WLineEdit * nameEdit;
  Wt::WLineEdit * surnameEdit;
  Wt::WLineEdit * groupEdit;
  Wt::WDateEdit * dateEdit;
  Wt::WLineEdit * mailEdit;
  Wt::WText * feedback;
  

  
};

#endif	/* STEP1_H */

