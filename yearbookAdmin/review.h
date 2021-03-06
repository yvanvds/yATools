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
#include <Wt/WContainerWidget>
#include <Wt/WDialog>
#include <admintools.h>
#include "removeDialog.h"

class yearbookAdmin;

class review : public Wt::WContainerWidget {
public:
  review(yearbookAdmin * parent);
  void removeCurrentEntry();
  
private:
  void openDialog(int withEntry);
  void loadTableContent();
  void loadDialogContent();
  
  void entryCancel();
  void entryRemove();
  void entrySave();
  void entryApprove();
  
  void onNameClicked();
  void onGroupClicked();
  void onDateClicked();
  
  void saveCurrentEntry(bool approve = false);
  void removeImage();
  
  yearbookAdmin * parent;
  int currentEntry;
  
  Wt::WText * title;
  Wt::WDialog * dialog;
  Wt::WImage * dialogImage;
  Wt::WPushButton * dialogImageButton;
  Wt::WLineEdit * dialogName;
  Wt::WLineEdit * dialogSurname;
  Wt::WLineEdit * dialogClass;
  Wt::WText * dialogBirthday;
  Wt::WText * dialogEmail;
  Wt::WTextArea * answer1;
  Wt::WTextArea * answer2;
  Wt::WTextArea * answer3;
  Wt::WTextArea * answer4;
  Wt::WTable * table;
  Wt::WContainerWidget * container;
  removeDialog warningAtRemove;
};

#endif	/* REVIEW_H */

