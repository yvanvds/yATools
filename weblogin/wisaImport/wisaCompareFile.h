/* 
 * File:   wisaCompareFile.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:22 PM
 */

#ifndef WISACOMPAREFILE_H
#define	WISACOMPAREFILE_H

#include "../base/stackPage.h"

class wisaImport;

class wisaCompareFile : public stackPage {
public:
  wisaCompareFile(wisaImport * parentObject);
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WText * message1;
  Wt::WText * message2;
  Wt::WText * message3;
  Wt::WText * message4;
  
  wisaImport * parentObject;
};

#endif	/* WISACOMPAREFILE_H */

