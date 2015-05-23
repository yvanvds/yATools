/* 
 * File:   wisaCompareNames.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:47 PM
 */

#ifndef WISACOMPARENAMES_H
#define	WISACOMPARENAMES_H

#include "../base/stackPage.h"

class wisaImport;

class wisaCompareNames : public stackPage {
public:
  wisaCompareNames(wisaImport * parentObject) : parentObject(parentObject) {}
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};

#endif	/* WISACOMPARENAMES_H */

