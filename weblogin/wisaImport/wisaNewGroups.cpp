/* 
 * File:   wisaNewGroups.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:48 PM
 */

#include "wisaNewGroups.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"



void wisaNewGroups::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h4>Wijzigingen aan klassen.</h4>"));
    
  // table scroll
  Wt::WScrollArea * scroll = new Wt::WScrollArea();
  box->addWidget(scroll);
  
  entries = new Wt::WTable();
  entries->setHeaderCount(1);
  entries->setWidth(700);
  scroll->setWidget(entries);
  scroll->setMaximumSize(750, 500);
}

void wisaNewGroups::onShow() {
  entries->clear();
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,0)->setPadding(5);
  entries->elementAt(0,1)->addWidget(new Wt::WText("Status"));
  entries->elementAt(0,1)->setPadding(5);
  
  GROUPS & groups = parentObject->ldap()->getGroups();
  container<wisaImport::wisaGroup> & wisaGroups = parentObject->getWisaGroups();
  
  int row = 1;
  for(int i = 0; i < groups.elms(); i++) {
    if(groups[i].editable()) {
      groups[i].setImportStatus(WI_DISCARD);
    } else {
      bool found = false;
      for(int j = 0; j < wisaGroups.elms(); j++) {
        if(wisaGroups[j].name == groups[i].cn()) {
          groups[i].setImportStatus(WI_ACCOUNTED);
          wisaGroups[j].link = &groups[i];
          found = true;
          break;
        }
      }
      if(!found) {
        groups[i].flagForRemoval();
        entries->elementAt(row, 0)->addWidget(new Wt::WText(groups[i].cn().wt()));
        entries->elementAt(row, 1)->addWidget(new Wt::WText("wordt verwijderd"));
        row++;
      }
    }
  }
  
  for(int i = 0; i < wisaGroups.elms(); i++) {
    if(wisaGroups[i].link == nullptr) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaGroups[i].name.wt()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText("wordt toegevoegd"));
      row++;
    }
  }
}
