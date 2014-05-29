/* 
 * File:   download.h
 * Author: yvan
 *
 * Created on May 28, 2014, 3:53 PM
 */

#ifndef DOWNLOAD_H
#define	DOWNLOAD_H

#include <Wt/WContainerWidget>

class yearbookAdmin;

class download : public Wt::WContainerWidget {
public:
  download(yearbookAdmin * parent);
  
private:
  yearbookAdmin * parent;
  
  Wt::WFileResource * downloadFile;
  Wt::WText * downloadTitle;
  Wt::WContainerWidget * downloadContainer;
  Wt::WAnchor * downloadAnchor;
  
  void generatePDF();
};

#endif	/* DOWNLOAD_H */

