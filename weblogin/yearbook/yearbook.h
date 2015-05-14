/* 
 * File:   yearbook.h
 * Author: yvan
 *
 * Created on May 12, 2015, 11:36 AM
 */

#ifndef YEARBOOK_H
#define	YEARBOOK_H

#include "gui/stackPage.h"
#include "gui/stackPageManager.h"
#include "yearbookVerifyAccount.h"
#include "yearbookQuestion.h"
#include "yearbookPhoto.h"
#include "yearbookDone.h"
#include "ldap/account.h"

class yearbook {
public:
  yearbook();
  
  y::gui::stackPageManager * get();
  void setAccount(y::ldap::account * account);
  
private:
  y::gui::stackPageManager * manager;
  y::ldap::account * account;
  
  yearbookVerifyAccount * ybVerifyAccount;
  yearbookQuestion * ybQuestion1;
  yearbookQuestion * ybQuestion2;
  yearbookQuestion * ybQuestion3;
  yearbookQuestion * ybQuestion4;
  yearbookPhoto * ybPhoto;
  yearbookDone * ybDone;
};

yearbook & Yearbook();

#endif	/* YEARBOOK_H */

