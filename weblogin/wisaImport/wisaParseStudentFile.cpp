/* 
 * File:   wisaParseFile.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:20 PM
 */

#include "wisaParseStudentFile.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"

wisaParseStudentFile::wisaParseStudentFile(wisaImport * parentObject)
: parentObject(parentObject) {}


void wisaParseStudentFile::setContent(Wt::WVBoxLayout * box) { 
  box->addWidget(new Wt::WText("<h4>Controleer of dit er ok uit ziet. (Let op de accenten!)</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);  
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 450);
}

void wisaParseStudentFile::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("_Naam_"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("_Voornaam_"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("_Gender_"));
  entries->elementAt(0,3)->addWidget(new Wt::WText("__GeboorteDatum__"));
  entries->elementAt(0,4)->addWidget(new Wt::WText("_GeboortePlaats_"));
  entries->elementAt(0,5)->addWidget(new Wt::WText("_Rijksregister_"));
  entries->elementAt(0,6)->addWidget(new Wt::WText("_Nationaliteit_"));
  entries->elementAt(0,7)->addWidget(new Wt::WText("_Stamnummer_"));
  entries->elementAt(0,8)->addWidget(new Wt::WText("_Wisa_ID_"));
  entries->elementAt(0,9)->addWidget(new Wt::WText("_Klas_"));
  entries->elementAt(0,10)->addWidget(new Wt::WText("__Wijzigen_Vanaf__"));
  entries->elementAt(0,11)->addWidget(new Wt::WText("____Straat____"));
  entries->elementAt(0,12)->addWidget(new Wt::WText("_Huisnummer_"));
  entries->elementAt(0,13)->addWidget(new Wt::WText("_Bus_"));
  entries->elementAt(0,14)->addWidget(new Wt::WText("_Postcode_"));
  entries->elementAt(0,15)->addWidget(new Wt::WText("_Stad_"));

  
  container<wisaImport::wisaAccount> & wisaContent = parentObject->getWisaAccounts();
  
  for(int i = 0; i < wisaContent.elms(); i++) {
    entries->elementAt(i+1, 0)->addWidget(new Wt::WText(wisaContent[i].sn.get().wt()));
    entries->elementAt(i+1, 1)->addWidget(new Wt::WText(wisaContent[i].cn.get().wt()));
    entries->elementAt(i+1, 2)->addWidget(new Wt::WText(GENDER::toText(wisaContent[i].gender.get()).wt()));
    entries->elementAt(i+1, 3)->addWidget(new Wt::WText(wisaContent[i].birthday.get().wt()));
    entries->elementAt(i+1, 4)->addWidget(new Wt::WText(wisaContent[i].birthplace.get().wt()));
    entries->elementAt(i+1, 5)->addWidget(new Wt::WText(wisaContent[i].registerID.get().wt()));
    entries->elementAt(i+1, 6)->addWidget(new Wt::WText(wisaContent[i].nationality.get().wt()));
    entries->elementAt(i+1, 7)->addWidget(new Wt::WText(string(wisaContent[i].stemID.get()).wt()));
    entries->elementAt(i+1, 8)->addWidget(new Wt::WText(string(wisaContent[i].wisaID.get()).wt()));
    entries->elementAt(i+1, 9)->addWidget(new Wt::WText(wisaContent[i].schoolClass.get().wt()));
    entries->elementAt(i+1, 10)->addWidget(new Wt::WText(wisaContent[i].changeClassDate.get().wt()));
    entries->elementAt(i+1, 11)->addWidget(new Wt::WText(wisaContent[i].street.get().wt()));
    entries->elementAt(i+1, 12)->addWidget(new Wt::WText(string(wisaContent[i].houseNumber.get()).wt()));
    entries->elementAt(i+1, 13)->addWidget(new Wt::WText(wisaContent[i].houseNumberAdd.get().wt()));
    entries->elementAt(i+1, 14)->addWidget(new Wt::WText(wisaContent[i].postalCode.get().wt()));
    entries->elementAt(i+1, 15)->addWidget(new Wt::WText(wisaContent[i].city.get().wt()));
  }
  
  entries->columnAt(3)->setWidth(250);
  entries->columnAt(10)->setWidth(250);
  
  for(int i = 0; i < entries->rowCount(); i++) {
    for(int j = 0; j < entries->columnCount(); j++) {
      entries->elementAt(i, j)->setPadding(5);
      entries->elementAt(i, j)->setVerticalAlignment(Wt::AlignMiddle);
    }
  }
  entries->refresh();
  
}

bool wisaParseStudentFile::onNext() {
  parentObject->showNewPage(W_NOID);
  return false;
}

bool wisaParseStudentFile::onPrevious() {
  parentObject->showNewPage(W_UPLOAD);
  return false;
}