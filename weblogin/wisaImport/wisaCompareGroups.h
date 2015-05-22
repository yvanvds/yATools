/* 
 * File:   wisaCompareGroups.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:24 PM
 */

#ifndef WISACOMPAREGROUPS_H
#define	WISACOMPAREGROUPS_H

#include "../base/stackPage.h"

class wisaImport;

class wisaCompareGroups : public stackPage {
public:
  wisaCompareGroups(wisaImport * parentObject);
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};

#endif	/* WISACOMPAREGROUPS_H */

