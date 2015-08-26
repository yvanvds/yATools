/* 
 * File:   wisaCommitChanges.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:50 PM
 */

#ifndef WISACOMMITCHANGES_H
#define	WISACOMMITCHANGES_H

#include "../base/stackPage.h"
#include <Wt/WResource>
#include <Wt/Http/Response>
#include <Wt/Http/ResponseContinuation>
#include "utils/container.h"
#include "utils/string.h"

class fileDownload : public Wt::WResource {
  public:
    fileDownload(Wt::WObject * parent = 0);
   ~fileDownload();
    
    void handleRequest(const Wt::Http::Request& request, Wt::Http::Response& response);
    
    void addMessage(const string & message);
    bool empty();
    
    private:
      container<string> messages;
};

class wisaImport;

class wisaCommitStudents : public stackPage {
public:
  wisaCommitStudents(wisaImport * parentObject) : parentObject(parentObject), download(nullptr) {}
 ~wisaCommitStudents();
 
  void setContent(Wt::WVBoxLayout * box);
  int getPageIndex() { return pageIndex; }
  void onShow();
  bool onNext();
  
  void addMessage(const string & message);
  void addNewAccount(const y::ldap::account & account, const string & pw1, const string & pw2);
  void threadDone();
  
  wisaImport * getParentObject() { return parentObject; }
  
private:
  Wt::WTable * entries;
  Wt::WImage * waitImage;
  Wt::WContainerWidget * imageContainer;
  Wt::WVBoxLayout * box;
  Wt::WText * progress;
  int rowCounter;
  fileDownload * download;
  
  wisaImport * parentObject;
};

#endif	/* WISACOMMITCHANGES_H */

