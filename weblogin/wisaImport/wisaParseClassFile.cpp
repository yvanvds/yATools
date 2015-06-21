/* 
 * File:   wisaParseClassFile.cpp
 * Author: yvan
 * 
 * Created on June 21, 2015, 12:30 PM
 */

#include "wisaParseClassFile.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"

wisaParseClassFile::wisaParseClassFile(wisaImport * parentObject)
: parentObject(parentObject) {}

void wisaParseClassFile::setContent(Wt::WVBoxLayout * box) { 
  box->addWidget(new Wt::WText("<h4>Controleer of dit er ok uit ziet.</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 450);
}

void wisaParseClassFile::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Beschrijving"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("AdminCode"));
  entries->elementAt(0,3)->addWidget(new Wt::WText("School ID"));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Titularis"));
  entries->elementAt(0,5)->addWidget(new Wt::WText("Adjunct"));
  entries->elementAt(0,0)->setPadding(5);
  entries->elementAt(0,1)->setPadding(5);
  entries->elementAt(0,2)->setPadding(5);
  entries->elementAt(0,3)->setPadding(5);
  entries->elementAt(0,4)->setPadding(5);
  entries->elementAt(0,5)->setPadding(5);
  
  container<wisaImport::wisaClass> & wisaContent = parentObject->getWisaClasses();
  
  for(int i = 0; i < wisaContent.elms(); i++) {
    entries->elementAt(i+1, 0)->addWidget(new Wt::WText(wisaContent[i].name.wt()));
    entries->elementAt(i+1, 1)->addWidget(new Wt::WText(wisaContent[i].description.wt()));
    entries->elementAt(i+1, 2)->addWidget(new Wt::WText(string(wisaContent[i].adminGroup).wt()));
    entries->elementAt(i+1, 3)->addWidget(new Wt::WText(string(wisaContent[i].schoolID).wt()));
    entries->elementAt(i+1, 4)->addWidget(new Wt::WText(wisaContent[i].titular.wt()));
    entries->elementAt(i+1, 5)->addWidget(new Wt::WText(wisaContent[i].adjunct.wt()));
  }
}

bool wisaParseClassFile::onNext() {
  parentObject->showNewPage(W_COMPAREGROUPS);
  return false;
}

bool wisaParseClassFile::onPrevious() {
  parentObject->showNewPage(W_UPLOAD);
  return false;
}