/* 
 * File:   wisaConfirmSubmit.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:49 PM
 */

#ifndef WISACONFIRMSUBMIT_H
#define	WISACONFIRMSUBMIT_H


#include "gui/stackPage.h"

class wisaConfirmSubmit : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
  bool onNext();
  bool onPrevious();
private:
  Wt::WText * message1;
  Wt::WText * message2;
  Wt::WText * message3;
  Wt::WText * message4;
  Wt::WText * message5;
  Wt::WText * message6;
  Wt::WText * message7;
  Wt::WText * message8;
  Wt::WText * message9;
  Wt::WText * message10;
};

#endif	/* WISACONFIRMSUBMIT_H */

