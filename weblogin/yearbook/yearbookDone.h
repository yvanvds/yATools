/* 
 * File:   yearbookDone.h
 * Author: yvan
 *
 * Created on May 12, 2015, 4:35 PM
 */

#ifndef YEARBOOKDONE_H
#define	YEARBOOKDONE_H

#include "gui/stackPage.h"

class yearbookDone : public y::gui::stackPage {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  
private:
  
};

#endif	/* YEARBOOKDONE_H */

