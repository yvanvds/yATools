/* 
 * File:   removeDialog.h
 * Author: yvan
 *
 * Created on May 24, 2014, 2:50 PM
 */

#ifndef REMOVEDIALOG_H
#define	REMOVEDIALOG_H

#include <admintools.h>
#include <Wt/WString>

class review;

class removeDialog : public y::gui::confirmationDialog {
public:
  removeDialog(review * parent);
  virtual void handleOK();
  
private:
  review * parent;
};

#endif	/* REMOVEDIALOG_H */

