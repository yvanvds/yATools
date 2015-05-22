/* 
 * File:   wisaImport.h
 * Author: yvan
 *
 * Created on February 17, 2015, 10:46 AM
 */

#ifndef WISAIMPORT_H
#define	WISAIMPORT_H

#include <Wt/WPanel>
#include "ldap/account.h"
#include "ldap/group.h"
#include "ldap/server.h"
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

class wisaImport : public Wt::WPanel {
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
  
  enum WISA_TAB {
    WISA_TAB_UPLOAD,
    WISA_TAB_PARSE,
  };
  
  wisaImport(y::ldap::server * server) : ldapServer(server) {}
  
  void create();
  void gotoTab(WISA_TAB id);
  
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
  
  y::ldap::server * ldap() { return ldapServer; }
  
private:
  string wisaFile;
  container<wisaAccount> wisaAccounts;
  container<wisaGroup> wisaGroups;
  
  Wt::WTabWidget * tabs;
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
  
  y::ldap::server * ldapServer;
};


#endif	/* WISAIMPORT_H */

