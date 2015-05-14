/* 
 * File:   yearbookDownload.h
 * Author: yvan
 *
 * Created on May 13, 2015, 7:36 PM
 */

#ifndef YEARBOOKDOWNLOAD_H
#define	YEARBOOKDOWNLOAD_H

class yearbookDownload : public Wt::WObject {
public:
  Wt::WWidget * get();
  
private:
  Wt::WContainerWidget * mainWidget;
  
  Wt::WFileResource * downloadFile;
  Wt::WText * downloadTitle;
  Wt::WContainerWidget * downloadContainer;
  Wt::WAnchor * downloadAnchor;
  
  void generatePDF();
  
};

yearbookDownload & YearbookDownload();

#endif	/* YEARBOOKDOWNLOAD_H */

