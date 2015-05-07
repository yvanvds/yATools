/* 
 * File:   wisaParseFile.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:20 PM
 */

#include "wisaParseFile.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"

void wisaParseFile::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>Controleer of dit er ok uit ziet. (Let op de accenten!)</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaParseFile::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText("GeboorteDatum"));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Wisa ID"));
  entries->elementAt(0,0)->setPadding(5);
  entries->elementAt(0,1)->setPadding(5);
  entries->elementAt(0,2)->setPadding(5);
  entries->elementAt(0,3)->setPadding(5);
  entries->elementAt(0,4)->setPadding(5);
  
  container<wisaImport::wisaAccount> & wisaContent = WisaImport().getWisaAccounts();
  
  for(int i = 0; i < wisaContent.elms(); i++) {
    entries->elementAt(i+1, 0)->addWidget(new Wt::WText(wisaContent[i].sn));
    entries->elementAt(i+1, 1)->addWidget(new Wt::WText(wisaContent[i].cn));
    entries->elementAt(i+1, 2)->addWidget(new Wt::WText(wisaContent[i].group));
    entries->elementAt(i+1, 3)->addWidget(new Wt::WText(wisaContent[i].date));
    entries->elementAt(i+1, 4)->addWidget(new Wt::WText(std::to_wstring(wisaContent[i].ID)));
  }
}