/* 
 * File:   stepPhoto.h
 * Author: yvan
 *
 * Created on May 14, 2014, 4:46 PM
 */

#ifndef STEPPHOTO_H
#define	STEPPHOTO_H

#include <Wt/WFileUpload>
#include <Wt/WImage>
#include "step.h"

class stepPhoto : public step {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  void setUpload();
  
private:
  Wt::WVBoxLayout * box;
  Wt::WFileUpload * fileUpload;
  Wt::WText * hint;
  Wt::WImage * image;
};

#endif	/* STEPPHOTO_H */

