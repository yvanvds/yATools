/* 
 * File:   wisaNewGroups.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:48 PM
 */

#ifndef WISANEWGROUPS_H
#define	WISANEWGROUPS_H

#include "gui/stackPage.h"

class wisaImport;

class wisaNewGroups : public y::gui::stackPage {
public:
  wisaNewGroups(wisaImport * parentObject) : parentObject(parentObject) {}
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};

#endif	/* WISANEWGROUPS_H */

