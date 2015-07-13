/* 
 * File:   wisaCompareNames.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:47 PM
 */

#include "wisaCompareNames.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include "../wisaImport.h"
#include "admintools.h"

void wisaCompareNames::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>De volgende waarden worden aangepast.</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 450);
  
  
}

void wisaCompareNames::onShow() {
  entries->clear();
  
  nextButton->setStyleClass("btn btn-danger");
  nextButton->setText("Wijzig Database");
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Wijziging"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Nieuwe Waarde"));
  
  container<wisaImport::wisaAccount> & wisaContent = parentObject->getWisaAccounts();
  int row = 1;
  for(int i = 0; i < wisaContent.elms(); i++) {
    string name(wisaContent[i].cn.get());
    name += " ";
    name += wisaContent[i].sn.get();
  
    if(!wisaContent[i].link) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText("wordt toegevoegd."));
      row++;
    } else {
      if(wisaContent[i].link->cn() != wisaContent[i].cn) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe voornaam:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].cn.get().wt()));
        row++;
      }
      if(wisaContent[i].link->sn() != wisaContent[i].sn) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe naam:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].sn.get().wt()));
        row++;
      }
      if(wisaContent[i].link->gender() != wisaContent[i].gender) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe gender:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(GENDER::toText(wisaContent[i].gender.get()).wt()));
        row++;
      }
      if(wisaContent[i].link->birthDay() != wisaContent[i].birthday) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe geboortedatum:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].birthday.get().wt()));
        row++;
      }
      if(wisaContent[i].link->registerID() != wisaContent[i].registerID) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuw rijksregisternummer:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].registerID.get().wt()));
        row++;
      }
      if(wisaContent[i].link->nationality() != wisaContent[i].nationality) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe nationaliteit:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].nationality.get().wt()));
        row++;
      }
      if(wisaContent[i].link->stemID() != wisaContent[i].stemID) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuw stamboeknummer:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(string(wisaContent[i].stemID.get()).wt()));
        row++;
      }
      if(wisaContent[i].link->wisaID() != wisaContent[i].wisaID) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe wisa ID:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(string(wisaContent[i].wisaID.get()).wt()));
        row++;
      }
      if(wisaContent[i].link->schoolClass() != wisaContent[i].schoolClass) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe klas:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].schoolClass.get().wt()));
        row++;
      }
      if(wisaContent[i].link->street() != wisaContent[i].street) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe straat:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].street.get().wt()));
        row++;
      }
      if(wisaContent[i].link->houseNumber() != wisaContent[i].houseNumber) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuw huisnummer:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(string(wisaContent[i].houseNumber.get()).wt()));
        row++;
      }
      if(wisaContent[i].link->houseNumberAdd() != wisaContent[i].houseNumberAdd) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe bus:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].houseNumberAdd.get().wt()));
        row++;
      }
      if(wisaContent[i].link->postalCode() != wisaContent[i].postalCode) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe postcode:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].postalCode.get().wt()));
        row++;
      }
      if(wisaContent[i].link->city() != wisaContent[i].city) {
        entries->elementAt(row, 0)->addWidget(new Wt::WText(name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("nieuwe stad:"));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].city.get().wt()));
        row++;
      }
      
    }      
  }
}


bool wisaCompareNames::onNext() {
  parentObject->showNewPage(W_COMMITSTUDENTS);
  return false;
}

bool wisaCompareNames::onPrevious() {
  parentObject->showNewPage(W_COMPAREFILE);
  return false;
}