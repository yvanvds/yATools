/* 
 * File:   proxyManager.cpp
 * Author: yvan
 * 
 * Created on February 15, 2015, 7:38 PM
 */

#include <Wt/WWidget>
#include <Wt/WContainerWidget>
#include <Wt/WPanel>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WRadioButton>
#include <Wt/WButtonGroup>

#include "proxyManager.h"

proxyManager & ProxyManager() {
  static proxyManager s;
  return s;
}

room::room(const std::string & name) : name(name){}

void room::create(Wt::WTableRow* row) {
  label = new Wt::WText(name);
  row->elementAt(0)->addWidget(label);
  bgroup = new Wt::WButtonGroup();
  
  button1 = new Wt::WRadioButton("open");
  button2 = new Wt::WRadioButton("filter");
  button3 = new Wt::WRadioButton("dicht");
  
  bgroup->addButton(button1, OPEN);
  bgroup->addButton(button2, FILTER);
  bgroup->addButton(button3, CLOSED);
  
  row->elementAt(1)->addWidget(button1);
  row->elementAt(2)->addWidget(button2);
  row->elementAt(3)->addWidget(button3);
  
  bgroup->setSelectedButtonIndex(0);
  bgroup->checkedChanged().connect(this, &room::buttonClicked);
}

void room::buttonClicked(Wt::WRadioButton * selected) {
  Wt::WButtonGroup * group = selected->group();
  ProxyManager().getRoom(group)->setStatus((STATUS)group->selectedButtonIndex());
}

Wt::WButtonGroup * room::getGroup() {
  return bgroup;
}

void room::setStatus(STATUS status) {
  switch(status) {
    case OPEN  : label->setStyleClass("label label-success"); break;
    case FILTER: label->setStyleClass("label label-warning"); break;
    case CLOSED: label->setStyleClass("label label-danger" ); break;
  }
}

Wt::WWidget * proxyManager::get() {
  
  Wt::WTable * table = new Wt::WTable();
  
  rooms.emplace_back("co112");
  rooms.back().create(table->rowAt(0));
  rooms.emplace_back("co114");
  rooms.back().create(table->rowAt(1));
  rooms.emplace_back("co116");
  rooms.back().create(table->rowAt(2));
  rooms.emplace_back("co117");
  rooms.back().create(table->rowAt(3));
  rooms.emplace_back("co126");
  rooms.back().create(table->rowAt(4));
  rooms.emplace_back("co127");
  rooms.back().create(table->rowAt(5));
  rooms.emplace_back("co137");
  rooms.back().create(table->rowAt(6));
  rooms.emplace_back("olc");
  rooms.back().create(table->rowAt(7));
  rooms.emplace_back("ec202");
  rooms.back().create(table->rowAt(8));
  rooms.emplace_back("ec203");
  rooms.back().create(table->rowAt(9));
  rooms.emplace_back("vi215");
  rooms.back().create(table->rowAt(10));
  
  for(int i = 0; i < table->rowCount(); i++) {
    for(int j = 0; j < table->columnCount(); j++) {
      table->elementAt(i,j)->setPadding(5);
      table->elementAt(i,j)->setVerticalAlignment(Wt::AlignmentFlag::AlignMiddle);
    }
  }
  
  table->addStyleClass("table form-inline table-bordered table-hover");
  table->setMargin(0);
  
  Wt::WContainerWidget * result = new Wt::WContainerWidget();
  Wt::WPanel * panel = new Wt::WPanel(result);
  panel->setStyleClass("panel panel-primary");
  panel->setCentralWidget(table);
  panel->setTitle("<h3>Webtoegang</h3>");
  
  panel->setMaximumSize(800, Wt::WLength::Auto);
  
  return result;
}

room * proxyManager::getRoom(Wt::WButtonGroup* group) {
  for(int i = 0; i < rooms.size(); i++) {
    if(rooms[i].getGroup() == group) {
      return &rooms[i];
    }
  }
  
  return nullptr;
}
