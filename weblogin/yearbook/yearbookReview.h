/* 
 * File:   yearbookReview.h
 * Author: yvan
 *
 * Created on May 12, 2015, 10:18 PM
 */

#ifndef YEARBOOKREVIEW_H
#define	YEARBOOKREVIEW_H

#include "yearbookConfirmRemove.h"
#include "yearbookDB.h"

class yearbookReview : public Wt::WObject {
public:
  yearbookReview(yearbookDB * ptr);
  
  Wt::WWidget * get();
  
  void removeCurrentEntry();
  
private:
  void openDialog(int withEntry);
  void loadTableContent();
  void createDialog();
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
  
  int currentEntry;
  
  yearbookDB * db;
  Wt::WContainerWidget * mainWidget;
  
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
  Wt::WContainerWidget * dialogContainer;
  yearbookConfirmRemove * warningAtRemove;
  
};


#endif	/* YEARBOOKREVIEW_H */

