/* 
 * File:   step4.h
 * Author: yvan
 *
 * Created on May 14, 2014, 4:11 PM
 */

#ifndef STEP4_H
#define	STEP4_H

#include "step.h"

class step4 : public step {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  
private:
  void contentChanged();
  
  Wt::WTextArea * textArea;  
  Wt::WText * hint;
};

#endif	/* STEP4_H */

