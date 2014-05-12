/* 
 * File:   yearBook.h
 * Author: yvan
 *
 * Created on May 12, 2014, 7:47 PM
 */

#ifndef YEARBOOK_H
#define	YEARBOOK_H

#include <admintools.h>

using namespace y;

class yearBook : public Wt::WApplication {
public:
  yearBook(const Wt::WEnvironment & env);
private:
  // auth
  Wt::WDialog * loginDialog;
  Wt::WContainerWidget * loginContainer;
  Wt::WLineEdit * nameEdit;
  Wt::WLineEdit * passEdit;
  Wt::WPushButton * sendButton;
};

#endif	/* YEARBOOK_H */

