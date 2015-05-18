/* 
 * File:   yearbookConfirmRemove.h
 * Author: yvan
 *
 * Created on May 13, 2015, 5:11 PM
 */

#ifndef YEARBOOKCONFIRMREMOVE_H
#define	YEARBOOKCONFIRMREMOVE_H

#include <admintools.h>

class yearbookReview;

class yearbookConfirmRemove : public y::gui::confirmationDialog {
public:
  yearbookConfirmRemove(yearbookReview * parent);
  virtual void handleOK();
  
private:
  yearbookReview * parent;
};

#endif	/* YEARBOOKCONFIRMREMOVE_H */

