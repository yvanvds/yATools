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
  
  void entryCancel();
  void entryRemove();
  void entrySave();
  void entryApprove();
  
  yearbookAdmin * parent;
  int currentEntry;
  
  Wt::WDialog * dialog;
  Wt::WImage * dialogImage;
  Wt::WLineEdit * dialogName;
  Wt::WLineEdit * dialogSurname;
  Wt::WLineEdit * dialogClass;
  Wt::WText * dialogBirthday;
  Wt::WText * dialogEmail;
  Wt::WTextArea * answer1;
  Wt::WTextArea * answer2;
  Wt::WTextArea * answer3;
  Wt::WTextArea * answer4;
  
};

#endif	/* REVIEW_H */

