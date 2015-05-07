/* 
 * File:   wisaParseFile.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:20 PM
 */

#ifndef WISAPARSEFILE_H
#define	WISAPARSEFILE_H

#include "gui/stackPage.h"

class wisaParseFile : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
};

#endif	/* WISAPARSEFILE_H */

