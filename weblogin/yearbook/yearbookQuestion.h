/* 
 * File:   yearbookQuestion.h
 * Author: yvan
 *
 * Created on May 12, 2015, 3:15 PM
 */

#ifndef YEARBOOKQUESTION_H
#define	YEARBOOKQUESTION_H

#include "../base/stackPage.h"
#include "yearbookDB.h"

class yearbookQuestion : public stackPage {
public:
  yearbookQuestion(int ID, yearbookDB * ptr);
  virtual void setContent(Wt::WVBoxLayout * box);
  virtual void onShow();
  bool onNext();
  
private:
  void contentChanged();
  
  yearbookDB * db;
  
  Wt::WTextArea * textArea;
  Wt::WText * hint;
  
  int questionID;
  
};

#endif	/* YEARBOOKQUESTION_H */

