/* 
 * File:   wisaCommitClasses.h
 * Author: yvan
 *
 * Created on June 22, 2015, 6:27 PM
 */

#ifndef WISACOMMITCLASSES_H
#define	WISACOMMITCLASSES_H

#include "../base/stackPage.h"
#include <Wt/WResource>
#include <Wt/Http/Response>
#include <Wt/Http/ResponseContinuation>
#include <Wt/WVBoxLayout>
#include <Wt/WImage>
#include "admintools.h"

class wisaCommitClasses : public stackPage {
public:
  wisaCommitClasses(wisaImport * parentObject) : parentObject(parentObject) {}
  
  void setContent(Wt::WVBoxLayout * box);
  int getPageIndex() { return pageIndex; }
  void onShow();
  bool onNext();
  
  void addMessage(const string & message);
  void threadDone();
  
  wisaImport * getParentObject() { return parentObject; }
  
private:
  wisaImport * parentObject;
  Wt::WImage * waitImage;
  Wt::WVBoxLayout * box;
  Wt::WText * progress;
  Wt::WTable * entries;
  
  int rowCounter;
};

#endif	/* WISACOMMITCLASSES_H */

