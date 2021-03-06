/* 
 * File:   wisaParseFile.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:20 PM
 */

#ifndef WISAPARSEFILE_H
#define	WISAPARSEFILE_H

#include "../base/stackPage.h"

class wisaImport;

class wisaParseStudentFile : public stackPage {
public:
  wisaParseStudentFile(wisaImport * parentObject);
  
  void setContent(Wt::WVBoxLayout * box);
  int getPageIndex() { return pageIndex; }
  void onShow();
  
  virtual bool onNext();
  virtual bool onPrevious();
  
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};

#endif	/* WISAPARSEFILE_H */

