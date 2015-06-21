/* 
 * File:   wisaParseClassFile.h
 * Author: yvan
 *
 * Created on June 21, 2015, 12:30 PM
 */

#ifndef WISAPARSECLASSFILE_H
#define	WISAPARSECLASSFILE_H


#include "../base/stackPage.h"

class wisaImport;

class wisaParseClassFile : public stackPage {
public:
  wisaParseClassFile(wisaImport * parentObject);
  
  void setContent(Wt::WVBoxLayout * box);
  int getPageIndex() { return pageIndex; }
  void onShow();
  
  virtual bool onNext();
  virtual bool onPrevious();
  
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};


#endif	/* WISAPARSECLASSFILE_H */

