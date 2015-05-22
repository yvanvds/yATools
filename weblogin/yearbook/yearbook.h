/* 
 * File:   yearbook.h
 * Author: yvan
 *
 * Created on May 12, 2015, 11:36 AM
 */

#ifndef YEARBOOK_H
#define	YEARBOOK_H

#include "../base/stackPage.h"
#include "../base/stackPageManager.h"
#include "yearbookVerifyAccount.h"
#include "yearbookQuestion.h"
#include "yearbookPhoto.h"
#include "yearbookDone.h"
#include "yearbookDB.h"
#include "ldap/account.h"

class yearbook : public Wt::WObject {
public:
  yearbook(yearbookDB * ptr);
  
  stackPageManager * get();
  void setAccount(y::ldap::account * account);
  
private:
  yearbookDB  * db;
  
  stackPageManager * manager;
  y::ldap::account * account;
  
  yearbookVerifyAccount * ybVerifyAccount;
  yearbookQuestion * ybQuestion1;
  yearbookQuestion * ybQuestion2;
  yearbookQuestion * ybQuestion3;
  yearbookQuestion * ybQuestion4;
  yearbookPhoto * ybPhoto;
  yearbookDone * ybDone;
};


#endif	/* YEARBOOK_H */

