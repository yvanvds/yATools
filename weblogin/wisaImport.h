/* 
 * File:   wisaImport.h
 * Author: yvan
 *
 * Created on February 17, 2015, 10:46 AM
 */

#ifndef WISAIMPORT_H
#define	WISAIMPORT_H

#include "gui/stackPage.h"
#include "gui/stackPageManager.h"

class wisaUpload : public y::gui::stackPage {
  public:
    wisaUpload();
    
    void setContent(Wt::WVBoxLayout * box);
    void onShow();
    
  private:
    Wt::WFileUpload * fileUpload; 
    Wt::WText * message;
    Wt::WVBoxLayout * box;
    
    void uploadFunc();
    void uploadedFunc();
    void fileTooLargeFunc();
    void cleanUpload();
};

class wisaParseFile : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WText * filename;
};

class wisaImport {
public:
  y::gui::stackPageManager * get();
  void setWisaFile(const std::string & file);
  std::string getWisaFile();
  
  struct wisaEntry {
    void set(std::vector<std::wstring> & line);
    std::wstring cn;
    std::wstring sn;
    std::wstring group;
    std::wstring date;
    std::wstring ID;
  };
  
  container<wisaEntry> & getWisaContents();
  
private:
  std::string wisaFile;
  container<wisaEntry> wisaContents;
  
  y::gui::stackPageManager * manager;
  
  wisaUpload * wUpload;
  wisaParseFile * WParseFile;
};

wisaImport & WisaImport();

#endif	/* WISAIMPORT_H */

