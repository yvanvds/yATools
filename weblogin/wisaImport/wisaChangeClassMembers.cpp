/* 
 * File:   wisaChangeClassMembers.cpp
 * Author: yvan
 * 
 * Created on June 21, 2015, 1:21 PM
 */

#include "wisaChangeClassMembers.h"

wisaChangeClassMembers::wisaChangeClassMembers() {
}

wisaChangeClassMembers::wisaChangeClassMembers(const wisaChangeClassMembers& orig) {
}

wisaChangeClassMembers::~wisaChangeClassMembers() {
}

/*
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
  
  entries->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  entries->elementAt(0,1)->addWidget(new Wt::WText("Voornaam"));
  entries->elementAt(0,2)->addWidget(new Wt::WText("Klas"));
  entries->elementAt(0,3)->addWidget(new Wt::WText(" "));
  entries->elementAt(0,4)->addWidget(new Wt::WText("Nieuwe Klas"));
  
  container<wisaImport::wisaAccount> & wisaContent = parentObject->getWisaAccounts();
  int row = 1;
  for(int i = 0; i < wisaContent.elms(); i++) {
    if(!wisaContent[i].link) continue;
    if(wisaContent[i].link->group()() != wisaContent[i].group) {
      entries->elementAt(row, 0)->addWidget(new Wt::WText(wisaContent[i].sn.wt()));
      entries->elementAt(row, 1)->addWidget(new Wt::WText(wisaContent[i].cn.wt()));
      entries->elementAt(row, 2)->addWidget(new Wt::WText(wisaContent[i].link->group()().wt()));
      entries->elementAt(row, 3)->addWidget(new Wt::WText("=>"));
      entries->elementAt(row, 4)->addWidget(new Wt::WText(wisaContent[i].group.wt()));
      row++;
    }      
  }
}*/