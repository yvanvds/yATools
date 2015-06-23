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
#include <Wt/WMessageBox>
#include "admintools.h"
#include "../wisaImport.h"

void wisaCompareClasses::setContent(Wt::WVBoxLayout* box) {
  title = new Wt::WText("<h4>De volgende klassen worden aangepast.</h4>");
  box->addWidget(title);
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 450);
}

void wisaCompareClasses::onShow() {
  // overwrite buttons
  previousButton->setStyleClass("btn btn-success");
  previousButton->setText("Toch maar niet");
  
  nextButton->setStyleClass("btn btn-danger");
  nextButton->setText("Wijzig Database");
  
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Actie"));
  
  dbChanges = false;
  
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
      dbChanges = true;
    } 
  }
  
  for(int i = 0; i < wisaClasses.elms(); i++) {
    if(wisaClasses[i].link == nullptr) {
      y::ldap::schoolClass & newClass = parentObject->ldap()->getClass(CN(wisaClasses[i].name));
      if(!newClass.isNew()) {
        string s = "Klas kan niet gemaakt worden: ";
        s += wisaClasses[i].name;
        Wt::WMessageBox * message = new Wt::WMessageBox(
                "Error!",
                s.c_str(),
                Wt::Critical, Wt::Ok);
        message->buttonClicked().connect(std::bind([=] () {
          parentObject->reset();
          parentObject->showNewPage(W_UPLOAD);
          return;
        }));
      } else {
        newClass.description(DESCRIPTION(wisaClasses[i].description));
        newClass.adminGroup(ADMINGROUP(wisaClasses[i].adminGroup));
        newClass.schoolID(SCHOOL_ID(wisaClasses[i].schoolID));
        y::ldap::account & titular = parentObject->ldap()->getAccount(WISA_NAME(wisaClasses[i].titular));
        newClass.titular(TITULAR(titular.dn()));
        y::ldap::account & adjunct = parentObject->ldap()->getAccount(WISA_NAME(wisaClasses[i].adjunct));
        newClass.adjunct(ADJUNCT(adjunct.dn()));
        newClass.flagForCommit();
        entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("wordt toegevoegd"));
        row++;
        dbChanges = true;
      }
      
    } else {
      y::ldap::schoolClass * link = wisaClasses[i].link;
      
      if(wisaClasses[i].description != link->description().get()) {
        link->description(DESCRIPTION(wisaClasses[i].description));
        link->flagForCommit();
        entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("krijgt beschrijving: "));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaClasses[i].description.wt()));
        dbChanges = true;
        row++;
      }
      
      if(wisaClasses[i].adminGroup != link->adminGroup().get()) {
        link->adminGroup(ADMINGROUP(wisaClasses[i].adminGroup));
        link->flagForCommit();
        entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("krijgt administratieve group: "));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(string(wisaClasses[i].adminGroup).wt()));
        dbChanges = true;
        row++;
      }
      
      if(wisaClasses[i].schoolID != link->schoolID().get()) {
        link->schoolID(SCHOOL_ID(wisaClasses[i].schoolID));
        link->flagForCommit();
        entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("krijgt school ID: "));
        entries->elementAt(row, 2)->addWidget(new Wt::WText(string(wisaClasses[i].schoolID).wt()));
        dbChanges = true;
        row++;
      }
      
      // get account of titular
      y::ldap::account * oldTitular = nullptr;
      if(!link->titular().get().get().empty()) {
        oldTitular = &parentObject->ldap()->getAccount(link->titular().get());
        if(oldTitular->wisaName().get().empty()) {
          oldTitular = nullptr;
        }
      }
      
      if((oldTitular == nullptr && !wisaClasses[i].titular.empty())
      || (oldTitular != nullptr && (oldTitular->wisaName().get() != wisaClasses[i].titular))) {
        y::ldap::account & newTitular = parentObject->ldap()->getAccount(WISA_NAME(wisaClasses[i].titular));
        if(newTitular.wisaName().get().empty()) {
          entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
          entries->elementAt(row, 1)->addWidget(new Wt::WText("Error (ongeldige titularis naam): "));
          entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaClasses[i].titular.wt()));
          row++;
        } else {
          link->titular(TITULAR(newTitular.dn()));
          link->flagForCommit();
          entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
          entries->elementAt(row, 1)->addWidget(new Wt::WText("Nieuwe Titularis: "));
          entries->elementAt(row, 2)->addWidget(new Wt::WText(newTitular.fullName().get().wt()));
          dbChanges = true;
          row++;
        }
      }
      
      
      // get account of adjunct
      y::ldap::account * oldAdjunct = nullptr;
      if(!link->adjunct().get().get().empty()) {
        oldAdjunct = &parentObject->ldap()->getAccount(link->adjunct().get());
        if(oldAdjunct->wisaName().get().empty()) {
          oldAdjunct = nullptr;
        }
      }
      
      if((oldAdjunct == nullptr && !wisaClasses[i].adjunct.empty())
      || (oldAdjunct != nullptr && (oldAdjunct->wisaName().get() != wisaClasses[i].adjunct))) {
        y::ldap::account & newAdjunct = parentObject->ldap()->getAccount(WISA_NAME(wisaClasses[i].adjunct));
        if(newAdjunct.wisaName().get().empty()) {
          entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
          entries->elementAt(row, 1)->addWidget(new Wt::WText("Error (ongeldige adjunct naam): "));
          entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaClasses[i].adjunct.wt()));
          row++;
        } else {
          wisaClasses[i].link->adjunct(ADJUNCT(newAdjunct.dn()));
          wisaClasses[i].link->flagForCommit();
          entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaClasses[i].name.wt()));
          entries->elementAt(row, 1)->addWidget(new Wt::WText("Nieuwe Adjunct: "));
          entries->elementAt(row, 2)->addWidget(new Wt::WText(newAdjunct.fullName().get().wt()));
          dbChanges = true;
          row++;
        }
      }
    }
  }
  
  if(dbChanges) {
    nextButton->setStyleClass("btn btn-danger");
    nextButton->setText("Wijzig Database");
    title->setText("<h4>De volgende klassen worden aangepast.</h4>");
  } else {
    nextButton->setStyleClass("btn btn-success");
    nextButton->setText("Terug naar upload");
    title->setText("<h4>De database wordt niet gewijzigd.</h4>");
  }
}

bool wisaCompareClasses::onNext() {
  if(dbChanges) {
    parentObject->showNewPage(W_COMMITCLASSES);
  } else {
    parentObject->ldap()->clearClasses();
    parentObject->reset();
    parentObject->showNewPage(W_UPLOAD);
  }
  return false;
}

bool wisaCompareClasses::onPrevious() {
  parentObject->ldap()->clearClasses();
  parentObject->showNewPage(W_PARSE_CLASS);
  return false;
}