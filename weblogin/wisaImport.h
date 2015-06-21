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
#include "wisaImport/wisaCompareClasses.h"
#include "wisaImport/wisaCompareNames.h"
#include "wisaImport/wisaConfirmSubmit.h"
#include "wisaImport/wisaNewGroups.h"
#include "wisaImport/wisaNoID.h"
#include "wisaImport/wisaParseStudentFile.h"
#include "wisaImport/wisaUpload.h"
#include "wisaImport/wisaParseClassFile.h"
#include "utils/string.h"
#include "base/stackPageManager.h"

enum WISA_PAGE {
  W_UPLOAD,
  W_PARSE_STUDENT,
  W_PARSE_CLASS,
  W_NOID,
  W_COMPAREFILE,
  W_COMPAREGROUPS,
  W_COMPARENAMES,
  W_NEWGROUPS,
  W_CONFIRM,
  W_COMMIT,
};

class wisaImport : public stackPageManager {
public:
  struct wisaAccount {
    wisaAccount() : link(nullptr) {}
    bool set(std::vector<std::wstring> & line);
    string cn;
    string sn;
    string schoolClass;
    string date;
    int ID;
    y::ldap::account * link;
  };
  
  struct wisaClass {
    wisaClass() : link(nullptr) {}
    bool set(std::vector<std::wstring> & line);
    string name;
    string description;
    int adminGroup;
    int schoolID;
    string titular;
    string adjunct;
    y::ldap::schoolClass * link;
  };
  
  
  wisaImport(y::ldap::server * server);

  
  void setWisaStudentFile(const string & file);
  void setWisaClassFile(const string & file);
  
  string getWisaStudentFile();
  string getWisaClassFile();
  
  bool readLinesUTF8(std::wifstream * stream, bool students = false);
  bool readLinesLatin(std::ifstream * stream, bool students = false);
  bool tokenize(const std::wstring & line, bool students = false);
  void reset();
  
  container<wisaAccount> & getWisaAccounts();
  container<wisaClass> & getWisaClasses();
  
  // push updates need access to application
  void setApplication(Wt::WApplication * app) { this->app = app; }
  Wt::WApplication * getApplication() { return app; }
  
  void showErrorOnScreen(const string & message);
  
  y::ldap::server * ldap() { return ldapServer; }
  
  void showNewPage(WISA_PAGE value);
  
private:
  string wisaStudentFile;
  string wisaClassFile;
  container<wisaAccount> wisaAccounts;
  container<wisaClass> wisaClasses;
  
  wisaUpload * wUpload;
  wisaParseStudentFile * WParseStudentFile;
  wisaParseClassFile * WParseClassFile;
  wisaNoID * WNoID;
  wisaCompareFile * WCompareFile;
  wisaCompareClasses * WCompareClasses;
  wisaCompareNames * WCompareNames;
  wisaNewGroups * WNewGroups;
  wisaConfirmSubmit * WConfirmSubmit;
  wisaCommitChanges * WCommitChanges;
  
  Wt::WApplication * app; // for locking
  
  y::ldap::server * ldapServer;
};


#endif	/* WISAIMPORT_H */

