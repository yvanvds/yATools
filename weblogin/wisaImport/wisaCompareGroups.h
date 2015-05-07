/* 
 * File:   wisaCompareGroups.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:24 PM
 */

#ifndef WISACOMPAREGROUPS_H
#define	WISACOMPAREGROUPS_H

#include "gui/stackPage.h"

class wisaCompareGroups : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
};

#endif	/* WISACOMPAREGROUPS_H */

