/* 
 * File:   configuration.h
 * Author: yvan
 *
 * Created on May 20, 2014, 8:45 PM
 */

#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include <Wt/WDateEdit>
#include <Wt/WLineEdit>
#include <Wt/WSelectionBox>

class yearbookAdmin;

class configuration : public Wt::WContainerWidget {
public:
  configuration(yearbookAdmin * parent);
  void loadContent();
  
  
private:
  void openDateChanged();
  void closeDateChanged();
  
  void question1Changed();
  void question2Changed();
  void question3Changed();
  void question4Changed();
  
  yearbookAdmin * parent;
  
  Wt::WDateEdit * openDate;
  Wt::WDateEdit * closeDate;
  Wt::WText * currentDate;
  
  Wt::WLineEdit * question1;
  Wt::WLineEdit * question2;
  Wt::WLineEdit * question3;
  Wt::WLineEdit * question4;
  
  Wt::WSelectionBox * users;
  Wt::WLineEdit * newUser;
  Wt::WPushButton * newUserButton;
  Wt::WPushButton * removeUserButton;
  Wt::WText * userFeedback;
};

#endif	/* CONFIGURATION_H */

