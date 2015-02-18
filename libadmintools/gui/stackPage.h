/* 
 * File:   stackPage.h
 * Author: yvan
 *
 * Created on February 17, 2015, 11:06 AM
 */

#ifndef STACKPAGE_H
#define	STACKPAGE_H

class stackPage : public Wt::WObject {
public:
  stackPage();
  
  void create();
  
  virtual void setContent(Wt::WVBoxLayout * box) = 0;
  virtual void onShow() = 0;
  //virtual void validateAll();
  
  //void showPreviousButton(bool value);
  //void showNextButton(bool value);
  //void showSaveButton(bool value);
  
  //void hide();
  //void show();
  //bool visible();
  
protected:
  void previousClicked();
  void nextClicked();
 // void saveClicked();
  
  Wt::WContainerWidget * mainContent;
  Wt::WPushButton * previousButton;
  Wt::WPushButton * nextButton;
  Wt::WPushButton * saveButton;
  
  bool createDone;
  bool showPrevious;
  bool showNext;
};

#endif	/* STACKPAGE_H */

