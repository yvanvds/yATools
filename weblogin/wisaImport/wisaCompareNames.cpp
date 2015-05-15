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
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"

void wisaCompareNames::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>De volgende namen worden aangepast.</h4>"));
  
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaCompareNames::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText("Nieuwe Naam"));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Nieuwe Voornaam"));
  entries->elementAt(0,0)->setPadding(5);
  entries->elementAt(0,1)->setPadding(5);
  entries->elementAt(0,2)->setPadding(5);
  entries->elementAt(0,3)->setPadding(5);
  entries->elementAt(0,4)->setPadding(5);
  
  container<wisaImport::wisaAccount> & wisaContent = WisaImport().getWisaAccounts();
  int row = 1;
  for(int i = 0; i < wisaContent.elms(); i++) {
    if(!wisaContent[i].link) continue;
    if(wisaContent[i].link->sn().compare(wisaContent[i].sn) != 0 
            || wisaContent[i].link->cn().compare(wisaContent[i].cn) != 0) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaContent[i].link->sn()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText(wisaContent[i].link->cn()));
      entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].group));
      entries->elementAt(row, 3)->addWidget(new Wt::WText(wisaContent[i].sn));
      entries->elementAt(row, 4)->addWidget(new Wt::WText(wisaContent[i].cn));
      row++;
    }      
  }
}
