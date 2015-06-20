/* 
 * File:   wisaNoID.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:23 PM
 */

#include "wisaNoID.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include <Wt/WIntValidator>
#include <Wt/WLineEdit>
#include <Wt/WCheckBox>
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"
#include "utils/convert.h"

void wisaNoID::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>Deze accounts hebben geen Wisa ID.</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaNoID::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText("Wisa ID"));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Verwijder"));
  entries->elementAt(0,4)->setContentAlignment(Wt::AlignCenter);
  
  ACCOUNTS & accounts = parentObject->ldap()->getAccounts();
  int row = 1;
  Wt::WIntValidator * validator = new Wt::WIntValidator(0, 100000);
  
  for(int i = 0; i < accounts.elms(); i++) {
    if(!accounts[i].isStudent()) {
      accounts[i].setImportStatus(WI_DISCARD);
    } else if(accounts[i].wisaID().get() == 0 ) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(accounts[i].sn().get().wt()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText(accounts[i].cn().get().wt()));
      entries->elementAt(row, 2)->addWidget(new Wt::WText(accounts[i].schoolClass().get().wt()));
      Wt::WLineEdit * wisaEdit = new Wt::WLineEdit();
      wisaEdit->setId(accounts[i].uid().get().utf8());
      wisaEdit->setValidator(validator);
      wisaEdit->setStyleClass("alert alert-warning");
      wisaEdit->setHeight(5);
      entries->elementAt(row, 3)->addWidget(wisaEdit);
      Wt::WCheckBox * remove = new Wt::WCheckBox();
      remove->resize(20,20);
      entries->elementAt(row, 4)->addWidget(remove);
      
      entries->elementAt(row, 0)->setContentAlignment(Wt::AlignMiddle);
      entries->elementAt(row, 1)->setContentAlignment(Wt::AlignMiddle);
      entries->elementAt(row, 2)->setContentAlignment(Wt::AlignMiddle);
      entries->elementAt(row, 3)->setContentAlignment(Wt::AlignMiddle);
      entries->elementAt(row, 4)->setContentAlignment(Wt::AlignMiddle | Wt::AlignCenter);
      row++;
    }
  }
}

bool wisaNoID::onNext() {
  for(int i = 1; i < entries->rowCount(); i++) {
    Wt::WLineEdit * le = (Wt::WLineEdit*)entries->rowAt(i)->elementAt(3)->widget(0);
    Wt::WCheckBox * cb = (Wt::WCheckBox*)entries->rowAt(i)->elementAt(4)->widget(0);
    if(cb->isChecked()) {
      y::ldap::account & acc = parentObject->ldap()->getAccount(UID(string(le->id())));
      acc.flagForRemoval();
      acc.setImportStatus(WI_DISCARD);
    } else if(le->validate() != Wt::WValidator::Valid) {
      le->setStyleClass("alert alert-danger");
      le->setHeight(5);
      return false;
    } else {
      if(!le->text().empty()) {
        int newID = 0;
        try {
          newID = boost::lexical_cast<int>(le->text());
        } catch (boost::bad_lexical_cast) {
          return false;
        }
        y::ldap::account & acc = parentObject->ldap()->getAccount(UID(string(le->id())));
        acc.wisaID(WISA_ID(newID));
        le->setStyleClass("alert alert-success");
        le->setHeight(5);
      }
    }
  }
  return true;
}