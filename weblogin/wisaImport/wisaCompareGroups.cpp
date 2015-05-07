/* 
 * File:   wisaCompareGroups.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:24 PM
 */

#include "wisaCompareGroups.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"

void wisaCompareGroups::setContent(Wt::WVBoxLayout* box) {
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

void wisaCompareGroups::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText(" "));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Nieuwe Klas"));
  
  container<wisaImport::wisaAccount> & wisaContent = WisaImport().getWisaAccounts();
  int row = 1;
  for(int i = 0; i < wisaContent.elms(); i++) {
    if(!wisaContent[i].link) continue;
    if(wisaContent[i].link->group()().compare(wisaContent[i].group) != 0) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaContent[i].sn));
      entries->elementAt(row, 1)->addWidget(new Wt::WText(wisaContent[i].cn));
      entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].link->group()()));
      entries->elementAt(row, 3)->addWidget(new Wt::WText("=>"));
      entries->elementAt(row, 4)->addWidget(new Wt::WText(wisaContent[i].group));
      row++;
    }      
  }
}
