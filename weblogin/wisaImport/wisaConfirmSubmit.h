/* 
 * File:   wisaConfirmSubmit.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:49 PM
 */

#ifndef WISACONFIRMSUBMIT_H
#define	WISACONFIRMSUBMIT_H


#include "../base/stackPage.h"

class wisaImport;

class wisaConfirmSubmit : public stackPage {
public:
  wisaConfirmSubmit(wisaImport * parentObject) : parentObject(parentObject) {}
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
  
  wisaImport * parentObject;
};

#endif	/* WISACONFIRMSUBMIT_H */

