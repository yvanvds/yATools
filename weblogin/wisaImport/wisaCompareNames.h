/* 
 * File:   wisaCompareNames.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:47 PM
 */

#ifndef WISACOMPARENAMES_H
#define	WISACOMPARENAMES_H

#include "gui/stackPage.h"

class wisaCompareNames : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
};

#endif	/* WISACOMPARENAMES_H */

