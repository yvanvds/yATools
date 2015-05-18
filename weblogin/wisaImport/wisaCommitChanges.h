/* 
 * File:   wisaCommitChanges.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:50 PM
 */

#ifndef WISACOMMITCHANGES_H
#define	WISACOMMITCHANGES_H

#include "gui/stackPage.h"
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

class wisaCommitChanges : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
  bool onNext();
  void addMessage(const string & message, bool lastUpdate = false);
  void addNewAccountMessage(const string & message);
  
private:
  Wt::WTable * entries;
  Wt::WVBoxLayout * box;
  Wt::WText * progress;
  int rowCounter;
  int streamCounter;
  fileDownload * download;
};

#endif	/* WISACOMMITCHANGES_H */

