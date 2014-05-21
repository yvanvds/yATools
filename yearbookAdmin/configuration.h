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

class yearbookAdmin;

class configuration : public Wt::WContainerWidget {
public:
  configuration(yearbookAdmin * parent);
  
private:
  yearbookAdmin * parent;
  
  Wt::WDateEdit * openDate;
  Wt::WDateEdit * closeDate;
  Wt::WText * currentDate;
  
  Wt::WLineEdit * question1;
  Wt::WLineEdit * question2;
  Wt::WLineEdit * question3;
  Wt::WLineEdit * question4;
  
};

#endif	/* CONFIGURATION_H */

