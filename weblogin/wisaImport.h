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
#include "ldap/group.h"
#include "wisaImport/wisaCommitChanges.h"
#include "wisaImport/wisaCompareFile.h"
#include "wisaImport/wisaCompareGroups.h"
#include "wisaImport/wisaCompareNames.h"
#include "wisaImport/wisaConfirmSubmit.h"
#include "wisaImport/wisaNewGroups.h"
#include "wisaImport/wisaNoID.h"
#include "wisaImport/wisaParseFile.h"
#include "wisaImport/wisaUpload.h"
#include "utils/string.h"

class wisaImport {
public:
  struct wisaAccount {
    wisaAccount() : link(nullptr) {}
    void set(std::vector<std::wstring> & line);
    string cn;
    string sn;
    string group;
    string date;
    int ID;
    y::ldap::account * link;
  };
  
  struct wisaGroup {
    wisaGroup() : link(nullptr) {}
    string name;
    y::ldap::group * link;
  };
  
  y::gui::stackPageManager * get();
  void setWisaFile(const string & file);
  string getWisaFile();
  bool readLinesUTF8(std::wifstream * stream);
  bool readLinesLatin(std::ifstream * stream);
  bool tokenize(const std::wstring & line);
  void reset();
  
  container<wisaAccount> & getWisaAccounts();
  container<wisaGroup> & getWisaGroups();
  
  // push updates need access to application
  void setApplication(Wt::WApplication * app) { this->app = app; }
  Wt::WApplication * getApplication() { return app; }
  
  void showErrorOnScreen(const string & message);
  
private:
  string wisaFile;
  container<wisaAccount> wisaAccounts;
  container<wisaGroup> wisaGroups;
  
  y::gui::stackPageManager * manager;
  
  wisaUpload * wUpload;
  wisaParseFile * WParseFile;
  wisaNoID * WNoID;
  wisaCompareFile * WCompareFile;
  wisaCompareGroups * WCompareGroups;
  wisaCompareNames * WCompareNames;
  wisaNewGroups * WNewGroups;
  wisaConfirmSubmit * WConfirmSubmit;
  wisaCommitChanges * WCommitChanges;
  
  Wt::WApplication * app; // for locking
};

wisaImport & WisaImport();

#endif	/* WISAIMPORT_H */

