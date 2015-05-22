/* 
 * File:   wisaUpload.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:18 PM
 */

#ifndef WISAUPLOAD_H
#define	WISAUPLOAD_H

#include <Wt/WContainerWidget>

class wisaImport;

class wisaUpload : public Wt::WContainerWidget {
  public:
    wisaUpload(wisaImport * parentObject);
   
    void onShow();
    void clear();
    
  private:
    Wt::WFileUpload * fileUpload; 
    Wt::WText * message;
    Wt::WVBoxLayout * box;
    
    void uploadFunc();
    void uploadedFunc();
    void fileTooLargeFunc();
    void cleanUpload();
    
    wisaImport * parentObject;
};

#endif	/* WISAUPLOAD_H */

