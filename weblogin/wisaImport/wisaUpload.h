/* 
 * File:   wisaUpload.h
 * Author: yvan
 *
 * Created on May 6, 2015, 4:18 PM
 */

#ifndef WISAUPLOAD_H
#define	WISAUPLOAD_H

#include "gui/stackPage.h"

class wisaUpload : public y::gui::stackPage {
  public:
    wisaUpload();
    
    void setContent(Wt::WVBoxLayout * box);
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
};

#endif	/* WISAUPLOAD_H */

