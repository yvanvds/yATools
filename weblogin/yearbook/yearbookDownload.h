/* 
 * File:   yearbookDownload.h
 * Author: yvan
 *
 * Created on May 13, 2015, 7:36 PM
 */

#ifndef YEARBOOKDOWNLOAD_H
#define	YEARBOOKDOWNLOAD_H

#include "yearbookDB.h"

class yearbookDownload : public Wt::WContainerWidget {
public:
  yearbookDownload(yearbookDB * ptr);
 ~yearbookDownload();
  
private:
  yearbookDB * db;
  
  Wt::WFileResource * downloadFile;
  Wt::WText * downloadTitle;
  Wt::WContainerWidget * downloadContainer;
  Wt::WAnchor * downloadAnchor;
  
  void generatePDF();
  
};


#endif	/* YEARBOOKDOWNLOAD_H */

