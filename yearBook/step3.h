/* 
 * File:   step3.h
 * Author: yvan
 *
 * Created on May 14, 2014, 4:05 PM
 */

#ifndef STEP3_H
#define	STEP3_H

#include "step.h"

class step3 : public step {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  
private:
  void contentChanged();
  
  Wt::WTextArea * textArea;  
  Wt::WText * hint;
};

#endif	/* STEP3_H */

