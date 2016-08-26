/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   viewAccount.cpp
 * Author: yvan
 * 
 * Created on August 26, 2016, 4:22 PM
 */

#include "viewAccount.h"
#include <Wt/WPanel>
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include <Wt/WText>

void viewAccount::create(y::ldap::account* account) {
  this->account = account;
  
  Wt::WPanel * panel = new Wt::WPanel(this);
  panel->setStyleClass("panel panel-primary");
  panel->setTitle("<h3>Account Details</h3>");
  panel->setMaximumSize(800, Wt::WLength::Auto);
  panel->setMargin("0 auto");
  
  Wt::WContainerWidget * content = new Wt::WContainerWidget();
  panel->setCentralWidget(content);
  content->setPadding("1%");
  
  Wt::WTable * table = new Wt::WTable();
  content->addWidget(table);
  
  int row = 0;
  
  table->elementAt(row,0)->addWidget(new Wt::WText("Voornaam: "));
  table->elementAt(row,1)->addWidget(new Wt::WText(account->cn().get().wt()));
  row++;
  
  table->elementAt(row,0)->addWidget(new Wt::WText("Naam: "));
  table->elementAt(row,1)->addWidget(new Wt::WText(account->sn().get().wt()));
  row++;
  
  table->elementAt(row,0)->addWidget(new Wt::WText("E-mail account: "));
  table->elementAt(row,1)->addWidget(new Wt::WText(account->mail().get().wt()));
  row++;
  
  table->elementAt(row,0)->addWidget(new Wt::WText("E-mail alias: "));
  table->elementAt(row,1)->addWidget(new Wt::WText(account->mailAlias().get().wt()));
  row++;
  
  if(account->isStaff()) {
    table->elementAt(row,0)->addWidget(new Wt::WText("Copy Code: "));
    table->elementAt(row,1)->addWidget(new Wt::WText(string(account->uidNumber().get()).wt()));
    row++;
  }
  
  for(int i = 0; i < table->rowCount(); i++) {
    for(int j = 0; j < table->columnCount(); j++) {
      table->elementAt(i,j)->setPadding(5);
      table->elementAt(i,j)->setVerticalAlignment(Wt::AlignmentFlag::AlignMiddle);
    }
    table->elementAt(i, 0)->setWidth("200px");
  }
  
  table->setStyleClass("panel-body");
}