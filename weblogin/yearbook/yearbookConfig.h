/* 
 * File:   yearbookConfig.h
 * Author: yvan
 *
 * Created on May 12, 2015, 7:16 PM
 */

#ifndef YEARBOOKCONFIG_H
#define	YEARBOOKCONFIG_H

#include <Wt/WContainerWidget>
#include <Wt/WTabWidget>
#include <Wt/WDateEdit>
#include <Wt/WLineEdit>
#include <Wt/WToolBar>
#include "utils/container.h"
#include "utils/string.h"
#include "yearbookDB.h"

class yearbookConfig : public Wt::WContainerWidget {
public:
  yearbookConfig(yearbookDB * ptr);
 ~yearbookConfig(); 
  
  struct replacement {
    string key;
    Wt::WLineEdit * value;
    string image;
  };
  
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
  
  void setImage(int group);
  void createUpload();
  
  yearbookDB * db;
  
  Wt::WTabWidget * tabs;
  
  Wt::WDateEdit * openDate;
  Wt::WDateEdit * closeDate;
  Wt::WText * currentDate;
  
  Wt::WLineEdit * question1;
  Wt::WLineEdit * question2;
  Wt::WLineEdit * question3;
  Wt::WLineEdit * question4;
  
  int currentGroup;
  Wt::WImage * groupImage;
  Wt::WFileUpload * imageUpload;
  Wt::WFileResource * imageResource;
  Wt::WFileResource * defaultResource;
  Wt::WText * imageHint;
  Wt::WContainerWidget * contentContainer;
  Wt::WToolBar * classes;
  
  container<replacement> replacements;
  void replacementChange();
};


#endif	/* YEARBOOKCONFIG_H */

