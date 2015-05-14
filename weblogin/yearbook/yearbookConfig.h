/* 
 * File:   yearbookConfig.h
 * Author: yvan
 *
 * Created on May 12, 2015, 7:16 PM
 */

#ifndef YEARBOOKCONFIG_H
#define	YEARBOOKCONFIG_H

#include <Wt/WObject>
#include <Wt/WTabWidget>
#include <Wt/WDateEdit>
#include <Wt/WLineEdit>
#include "utils/container.h"

class yearbookConfig : public Wt::WObject {
public:
  
  struct replacement {
    std::wstring key;
    Wt::WLineEdit * value;
  };
  
  Wt::WWidget * get();
  void loadContent();
private:
  
  void openDateChanged();
  void closeDateChanged();
  
  void question1Changed();
  void question2Changed();
  void question3Changed();
  void question4Changed();
  
  void calculateStatus();
  
  void addUserPushed();
  void removeUserPushed();
  
  void refreshUsers();
  
  Wt::WTabWidget * tabs;
  
  Wt::WDateEdit * openDate;
  Wt::WDateEdit * closeDate;
  Wt::WText * currentDate;
  
  Wt::WLineEdit * question1;
  Wt::WLineEdit * question2;
  Wt::WLineEdit * question3;
  Wt::WLineEdit * question4;
  
  
  container<replacement> replacements;
  void replacementChange();
};

yearbookConfig & YearbookConfig();

#endif	/* YEARBOOKCONFIG_H */

