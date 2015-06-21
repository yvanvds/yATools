/* 
 * File:   wisaUpload.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:18 PM
 */

#ifndef WISAUPLOAD_H
#define	WISAUPLOAD_H

#include "../base/stackPage.h"

class wisaImport;

class wisaUpload : public stackPage {
  public:
    wisaUpload(wisaImport * parentObject);
   
    void setContent(Wt::WVBoxLayout * box);
    
    void onShow();
    void clear();
    
    int getPageIndex() { return pageIndex; }
    
  private:
    Wt::WContainerWidget * classContainer;
    Wt::WContainerWidget * studentContainer;
    Wt::WVBoxLayout * classBox;
    Wt::WVBoxLayout * studentBox;
    Wt::WFileUpload * classUpload;
    Wt::WFileUpload * studentUpload; 
    Wt::WText * classMessage;
    Wt::WText * studentMessage;
  
    Wt::WVBoxLayout * box;
    
    void classUploadFunc();
    void studentUploadFunc();
    void classUploadedFunc();
    void studentUploadedFunc();
    void classFileTooLargeFunc();
    void studentFileTooLargeFunc();
    void cleanClassUpload();
    void cleanStudentUpload();
    
    wisaImport * parentObject;
};

#endif	/* WISAUPLOAD_H */

