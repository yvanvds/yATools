/* 
 * File:   step5.h
 * Author: yvan
 *
 * Created on May 14, 2014, 4:17 PM
 */

#ifndef STEP5_H
#define	STEP5_H

#include "step.h"

class step5 : public step {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  
private:
  void contentChanged();
  
  Wt::WTextArea * textArea;  
  Wt::WText * hint;
};

#endif	/* STEP5_H */

