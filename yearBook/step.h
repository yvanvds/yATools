/* 
 * File:   step.h
 * Author: yvan
 *
 * Created on May 14, 2014, 2:36 PM
 */

#ifndef STEP_H
#define	STEP_H

#include <admintools.h>


class yearBook;

class step : public Wt::WObject {
public:
  step();
  
  void create(yearBook * parent);
  
  virtual void setContent(Wt::WVBoxLayout * box) = 0;
  virtual void onShow() = 0;
  
  void showPreviousButton(bool value);
  void showNextButton(bool value);
  void showSaveButton(bool value);
  
  void hide();
  void show();
  bool visible();
  
  yearBook * parent;
private:
  
  void logoutClicked();
  void previousClicked();
  void nextClicked();
  void saveClicked();
  
  Wt::WPanel * mainPanel;
  Wt::WContainerWidget * mainContent;
  
  Wt::WPushButton * logOutButton;
  Wt::WPushButton * previousButton;
  Wt::WPushButton * nextButton;
  Wt::WPushButton * saveButton;

  
  bool createDone;
  bool showPrevious;
  bool showNext;
  bool showSave;
};


#endif	/* STEP_H */

