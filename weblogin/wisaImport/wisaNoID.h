/* 
 * File:   wisaNoID.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:23 PM
 */

#ifndef WISANOID_H
#define	WISANOID_H

#include "../base/stackPage.h"

class wisaImport;

class wisaNoID : public stackPage {
public:
  wisaNoID(wisaImport * parentObject) : parentObject(parentObject) {}
  void setContent(Wt::WVBoxLayout * box);
  int getPageIndex() { return pageIndex; }
  void onShow();
  
  virtual bool onNext();
  virtual bool onPrevious();
  
  
  
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};
#endif	/* WISANOID_H */

