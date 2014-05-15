/* 
 * File:   step6.h
 * Author: yvan
 *
 * Created on May 14, 2014, 4:35 PM
 */

#ifndef STEP6_H
#define	STEP6_H

#include "step.h"

class step6 : public step {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  
private:
  void contentChanged();
  
  Wt::WTextArea * textArea;  
  Wt::WText * hint;
};

#endif	/* STEP6_H */

