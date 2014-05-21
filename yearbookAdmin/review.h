/* 
 * File:   review.h
 * Author: yvan
 *
 * Created on May 20, 2014, 10:30 PM
 */

#ifndef REVIEW_H
#define	REVIEW_H

#include <Wt/WDateEdit>
#include <Wt/WLineEdit>
#include <Wt/WDialog>

class yearbookAdmin;

class review : public Wt::WContainerWidget {
public:
  review(yearbookAdmin * parent);
  
private:
  void openDialog(int withEntry);
  void loadDialogContent();
  
  yearbookAdmin * parent;
  int currentEntry;
  
  Wt::WDialog * dialog;
  Wt::WImage * dialogImage;
  Wt::WLineEdit * dialogName;
  Wt::WLineEdit * dialogSurname;
};

#endif	/* REVIEW_H */

