/* 
 * File:   wisaParseFile.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:20 PM
 */

#ifndef WISAPARSEFILE_H
#define	WISAPARSEFILE_H

#include "gui/stackPage.h"

class wisaImport;

class wisaParseFile : public y::gui::stackPage {
public:
  wisaParseFile(wisaImport * parentObject) : parentObject(parentObject) {}
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};

#endif	/* WISAPARSEFILE_H */

