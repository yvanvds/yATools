/* 
 * File:   wisaNewGroups.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:48 PM
 */

#ifndef WISANEWGROUPS_H
#define	WISANEWGROUPS_H

#include "gui/stackPage.h"

class wisaNewGroups : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
};

#endif	/* WISANEWGROUPS_H */

