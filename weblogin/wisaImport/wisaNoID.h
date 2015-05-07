/* 
 * File:   wisaNoID.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:23 PM
 */

#ifndef WISANOID_H
#define	WISANOID_H

#include "gui/stackPage.h"

class wisaNoID : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
  bool onNext();
private:
  Wt::WTable * entries;
};
#endif	/* WISANOID_H */

