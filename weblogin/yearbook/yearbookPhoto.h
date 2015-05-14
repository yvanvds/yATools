/* 
 * File:   yearbookPhoto.h
 * Author: yvan
 *
 * Created on May 12, 2015, 3:42 PM
 */

#ifndef YEARBOOKPHOTO_H
#define	YEARBOOKPHOTO_H

#include "gui/stackPage.h"
#include <Wt/WFileUpload>
#include <Wt/WImage>
#include <Wt/WVBoxLayout>
#include <Wt/WText>

class yearbookPhoto : public y::gui::stackPage {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  bool onNext();
  void setUpload();
  
private:
  Wt::WVBoxLayout * box;
  Wt::WFileUpload * fileUpload;
  Wt::WText * hint;
  Wt::WImage * image;
};

#endif	/* YEARBOOKPHOTO_H */

