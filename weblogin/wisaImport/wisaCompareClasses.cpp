/* 
 * File:   wisaCompareGroups.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:24 PM
 */

#include "wisaCompareClasses.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include "admintools.h"
#include "../wisaImport.h"

void wisaCompareClasses::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>De volgende klassen worden aangepast.</h4>"));
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaCompareClasses::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Actie"));
  
  CLASSES & classes = parentObject->ldap()->getClasses();
  container<wisaImport::wisaClass> & wisaClasses = parentObject->getWisaClasses();
  
  int row = 1;
  for(int i = 0; i < classes.elms(); i++) {
    bool found = false;
    classes[i].setImportStatus(WI_NOT_ACCOUNTED);
    for(int j = 0; j < wisaClasses.elms(); j++) {
      if(wisaClasses[j].name == classes[i].cn().get()) {
        classes[i].setImportStatus(WI_ACCOUNTED);
        wisaClasses[j].link = &classes[i];
        found = true;
        break;
      }
    }
    if(!found) {
      classes[i].flagForRemoval();
      entries->elementAt(row, 0)->addWidget(new Wt::WText(classes[i].cn().get().wt()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText("wordt verwijderd"));
      row++;
    } 
  }
  
  for(int i = 0; i < wisaClasses.elms(); i++) {
    if(wisaClasses[i].link == nullptr) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText("wordt toegevoegd"));
      row++;
    } else {
      if(wisaClasses[i].description != wisaClasses[i].link->description().get()) {
        wisaClasses[i].link->description(DESCRIPTION(wisaClasses[i].description));
        entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("krijgt beschrijving: "));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaClasses[i].description.wt()));
      }
      
      if(wisaClasses[i].adminGroup != wisaClasses[i].link->adminGroup().get()) {
        wisaClasses[i].link->adminGroup(ADMINGROUP(wisaClasses[i].adminGroup));
        entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("krijgt administratieve group: "));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(string(wisaClasses[i].adminGroup).wt()));
      }
      
      if(wisaClasses[i].schoolID != wisaClasses[i].link->schoolID().get()) {
        wisaClasses[i].link->schoolID(SCHOOL_ID(wisaClasses[i].schoolID));
        entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("krijgt school ID: "));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(string(wisaClasses[i].schoolID).wt()));
      }
      
      // get account of titular
      y::ldap::account & oldTitular = parentObject->ldap()->getAccount(wisaClasses[i].link->titular().get());
      y::ldap::account & newTitular = parentObject->ldap()->getAccount(WISA_NAME(wisaClasses[i].titular));
      if(oldTitular.uidNumber() != newTitular.uidNumber()) {
        if(newTitular.isNew()) {
          entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
          entries->elementAt(row, 1)->addWidget(new Wt::WText("Error (ongeldige titularis naam): "));
          entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaClasses[i].titular.wt()));
        } else {
          wisaClasses[i].link->titular(TITULAR(newTitular.dn()));
          entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
          entries->elementAt(row, 1)->addWidget(new Wt::WText("Nieuwe Titularis: "));
          entries->elementAt(row, 2)->addWidget(new Wt::WText(newTitular.fullName().get().wt()));
        }
      }
      
      // get account of adjunct
      y::ldap::account & oldAdjunct = parentObject->ldap()->getAccount(wisaClasses[i].link->adjunct().get());
      y::ldap::account & newAdjunct = parentObject->ldap()->getAccount(WISA_NAME(wisaClasses[i].adjunct));
      if(oldAdjunct.uidNumber() != newAdjunct.uidNumber()) {
        if(newAdjunct.isNew()) {
          entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
          entries->elementAt(row, 1)->addWidget(new Wt::WText("Error (ongeldige adjunct naam): "));
          entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaClasses[i].adjunct.wt()));
        } else {
          wisaClasses[i].link->adjunct(ADJUNCT(newAdjunct.dn()));
          entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
          entries->elementAt(row, 1)->addWidget(new Wt::WText("Nieuwe Adjunct: "));
          entries->elementAt(row, 2)->addWidget(new Wt::WText(newAdjunct.fullName().get().wt()));
        }
      }
    }
  }
}

bool wisaCompareClasses::onNext() {
  parentObject->showNewPage(W_COMPAREGROUPS);
  return false;
}

bool wisaCompareClasses::onPrevious() {
  parentObject->showNewPage(W_PARSE_CLASS);
  return false;
}