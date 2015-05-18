/* 
 * File:   yearbookDone.h
 * Author: yvan
 *
 * Created on May 12, 2015, 4:35 PM
 */

#ifndef YEARBOOKDONE_H
#define	YEARBOOKDONE_H

#include "gui/stackPage.h"
#include "yearbookDB.h"

class yearbookDone : public y::gui::stackPage {
public:
  yearbookDone(yearbookDB * db) : db(db) {}
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  
private:
  yearbookDB * db;
};

#endif	/* YEARBOOKDONE_H */

