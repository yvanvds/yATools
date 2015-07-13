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
#include "wisaImport/wisaCommitStudents.h"
#include "wisaImport/wisaCompareFile.h"
#include "wisaImport/wisaCompareClasses.h"
#include "wisaImport/wisaCompareNames.h"
#include "wisaImport/wisaConfirmSubmit.h"
#include "wisaImport/wisaNewGroups.h"
#include "wisaImport/wisaNoID.h"
#include "wisaImport/wisaParseStudentFile.h"
#include "wisaImport/wisaUpload.h"
#include "wisaImport/wisaParseClassFile.h"
#include "wisaImport/wisaCommitClasses.h"
#include "utils/string.h"
#include "base/stackPageManager.h"

enum WISA_PAGE {
  W_UPLOAD,
  W_PARSE_STUDENT,
  W_PARSE_CLASS,
  W_NOID,
  W_COMPAREFILE,
  W_COMPAREGROUPS,
  W_ADDGROUPS,
  W_COMPARENAMES,
  W_CONFIRM,
  W_COMMITCLASSES,
  W_COMMITSTUDENTS,
};

class wisaImport : public stackPageManager {
public:
  struct wisaAccount {
    wisaAccount();
    bool set(std::vector<std::wstring> & line);
    CN cn;
    SN sn;
    GENDER gender;
    DATE birthday;
    BIRTHPLACE birthplace;
    REGISTER_ID registerID;
    NATION nationality;
    STEM_ID stemID;
    WISA_ID wisaID;
    SCHOOLCLASS schoolClass;
    DATE changeClassDate;
    STREET street;
    HOUSENUMBER houseNumber;
    HOUSENUMBER_ADD houseNumberAdd;
    POSTAL_CODE postalCode;
    CITY city;
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
  wisaCommitStudents * WCommitStudents;
  wisaCommitClasses * WCommitClasses;
  
  Wt::WApplication * app; // for locking
  
  y::ldap::server * ldapServer;
};


#endif	/* WISAIMPORT_H */

