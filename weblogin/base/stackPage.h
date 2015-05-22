/* 
 * File:   stackPage.h
 * Author: yvan
 *
 * Created on February 17, 2015, 11:06 AM
 */

#ifndef STACKPAGE_H
#define	STACKPAGE_H

#include <Wt/WObject>
#include <Wt/WVBoxLayout>
#include <Wt/WContainerWidget>


class stackPageManager;

class stackPage : public Wt::WContainerWidget {
public:
  void setIndex(int index) { pageIndex = index; }
  void create(stackPageManager * parent);
  void showButtons(bool previous, bool next);

  virtual void setContent(Wt::WVBoxLayout * box) = 0;
  virtual void onShow() = 0;

  virtual bool onNext() {return true;}
  virtual bool onPrevious() {return true;}

protected:
  void previousClicked();
  void nextClicked();

  Wt::WPushButton * previousButton;
  Wt::WPushButton * nextButton;

  int pageIndex;
  stackPageManager * parent;
};

#endif	/* STACKPAGE_H */

