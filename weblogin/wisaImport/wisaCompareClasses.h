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

class wisaCompareClasses : public stackPage {
public:
  wisaCompareClasses(wisaImport * parentObject) : parentObject(parentObject) {}
  void setContent(Wt::WVBoxLayout * box);
  int getPageIndex() { return pageIndex; }
  void onShow();
  
  virtual bool onNext();
  virtual bool onPrevious();
  
private:
  
  Wt::WTable * entries;
  Wt::WText * title;
  
  wisaImport * parentObject;
  bool dbChanges;
};

#endif	/* WISACOMPAREGROUPS_H */

