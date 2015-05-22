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
  wisaNoID(wisaImport * parentObject);
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
  bool onNext();
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};
#endif	/* WISANOID_H */

