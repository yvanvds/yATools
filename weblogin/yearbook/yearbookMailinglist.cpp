/* 
 * File:   yearbookMailinglist.cpp
 * Author: yvan
 * 
 * Created on August 23, 2016, 5:01 PM
 */

#include "yearbookMailinglist.h"
#include <Wt/WTextArea>

yearbookMailinglist::yearbookMailinglist(yearbookDB * ptr) : db(ptr) {
  addStyleClass("well");
  setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  
  addWidget(new Wt::WText("<p>Deze adressen kan je toevoegen aan een mailing list.</p>"));
  
  Wt::WTextArea * ta = new Wt::WTextArea(this);
  ta->setColumns(80);
  ta->setRows(20);
  
  db->loadAllUsers();
  container<yearbookDB::entry> & entries = db->getEntries();
  
  string content;
  for(unsigned int i = 0; i < entries.elms(); i++) {
    content += entries[i].name;
    content += " ";
    content += entries[i].surname;
    content += ", ";
    content += entries[i].mail;
    content += "\n";
  }
  
  ta->setText(content.wt());
}


yearbookMailinglist::~yearbookMailinglist() {
}

