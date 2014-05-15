/* 
 * File:   step2.h
 * Author: yvan
 *
 * Created on May 14, 2014, 2:01 PM
 */

#ifndef STEP2_H
#define	STEP2_H

#include "step.h"
#include <Wt/WTextArea>

class step2 : public step {
public:
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  
private:
  void contentChanged();
  
  Wt::WTextArea * textArea;  
  Wt::WText * hint;
};

#endif	/* STEP2_H */

