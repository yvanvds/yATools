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
#include "ldap/account.h"

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
  Wt::WTable * entries;
};

class wisaCompareFile : public y::gui::stackPage {
public:

  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WText * message1;
  Wt::WText * message2;
  Wt::WText * message3;
  Wt::WText * message4;
};

class wisaNoID : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
  bool onNext();
private:
  Wt::WTable * entries;
};

class wisaCompareGroups : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
};

class wisaCompareNames : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WTable * entries;
};

class wisaNewGroups : public y::gui::stackPage {
public:
  void setContent(Wt::WVBoxLayout * box);
  void onShow();
private:
  Wt::WText * message;
};

class wisaImport {
public:
  y::gui::stackPageManager * get();
  void setWisaFile(const std::string & file);
  std::string getWisaFile();
  
  struct wisaEntry {
    wisaEntry() : link(nullptr) {}
    void set(std::vector<std::wstring> & line);
    std::wstring cn;
    std::wstring sn;
    std::wstring group;
    std::wstring date;
    int ID;
    y::ldap::account * link;
  };
  
  container<wisaEntry> & getWisaContents();
  
private:
  std::string wisaFile;
  container<wisaEntry> wisaContents;
  
  y::gui::stackPageManager * manager;
  
  wisaUpload * wUpload;
  wisaParseFile * WParseFile;
  wisaNoID * WNoID;
  wisaCompareFile * WCompareFile;
  wisaCompareGroups * WCompareGroups;
  wisaCompareNames * WCompareNames;
  wisaNewGroups * WNewGroups;
};

wisaImport & WisaImport();

#endif	/* WISAIMPORT_H */

