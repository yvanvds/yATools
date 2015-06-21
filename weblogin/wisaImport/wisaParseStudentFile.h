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

class wisaParseFile : public stackPage {
public:
  wisaParseFile(wisaImport * parentObject);
  
  void setContent(Wt::WVBoxLayout * box);
  
  void onShow();
  
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};

#endif	/* WISAPARSEFILE_H */

