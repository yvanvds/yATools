/* 
 * File:   wisaParseFile.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:20 PM
 */

#ifndef WISAPARSEFILE_H
#define	WISAPARSEFILE_H

#include <Wt/WContainerWidget>

class wisaImport;

class wisaParseFile : public Wt::WContainerWidget {
public:
  wisaParseFile(wisaImport * parentObject);
  
  void onShow();
  
private:
  Wt::WVBoxLayout * box;
  Wt::WTable * entries;
  
  wisaImport * parentObject;
};

#endif	/* WISAPARSEFILE_H */

