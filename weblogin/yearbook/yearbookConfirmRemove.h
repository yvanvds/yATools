/* 
 * File:   yearbookConfirmRemove.h
 * Author: yvan
 *
 * Created on May 13, 2015, 5:11 PM
 */

#ifndef YEARBOOKCONFIRMREMOVE_H
#define	YEARBOOKCONFIRMREMOVE_H

#include <admintools.h>


class yearbookConfirmRemove : public y::gui::confirmationDialog {
public:
  yearbookConfirmRemove();
  virtual void handleOK();
};

#endif	/* YEARBOOKCONFIRMREMOVE_H */

