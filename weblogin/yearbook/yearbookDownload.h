/* 
 * File:   yearbookDownload.h
 * Author: yvan
 *
 * Created on May 13, 2015, 7:36 PM
 */

#ifndef YEARBOOKDOWNLOAD_H
#define	YEARBOOKDOWNLOAD_H

#include "yearbookDB.h"

class yearbookDownload : public Wt::WObject {
public:
  yearbookDownload(yearbookDB * ptr) : db(ptr) {}
  Wt::WWidget * get();
  
private:
  yearbookDB * db;
  Wt::WContainerWidget * mainWidget;
  
  Wt::WFileResource * downloadFile;
  Wt::WText * downloadTitle;
  Wt::WContainerWidget * downloadContainer;
  Wt::WAnchor * downloadAnchor;
  
  void generatePDF();
  
};


#endif	/* YEARBOOKDOWNLOAD_H */

