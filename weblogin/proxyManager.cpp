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
#include "utils/container.h"
#include "utils/proxy.h"
#include "data/row.h"

room::room(const string & name, proxyManager * parent) 
  : name(name), parent(parent) {}

void room::create(Wt::WTableRow* row) {
  label = new Wt::WText(name.wt());
  row->elementAt(0)->addWidget(label);
  bgroup = new Wt::WButtonGroup();
  
  button1 = new Wt::WRadioButton("dicht");
  button2 = new Wt::WRadioButton("filter");
  button3 = new Wt::WRadioButton("open");
  
  bgroup->addButton(button1, y::utils::proxy::CLOSED);
  bgroup->addButton(button2, y::utils::proxy::FILTER);
  bgroup->addButton(button3, y::utils::proxy::OPEN);
  
  row->elementAt(1)->addWidget(button1);
  row->elementAt(2)->addWidget(button2);
  row->elementAt(3)->addWidget(button3);
  row->addChild(bgroup);
  
  bgroup->setSelectedButtonIndex(0);
  bgroup->checkedChanged().connect(this, &room::buttonClicked);
}

void room::buttonClicked(Wt::WRadioButton * selected) {
  Wt::WButtonGroup * group = selected->group();
  parent->getRoom(group)->setStatus((y::utils::proxy::STATUS)group->selectedButtonIndex());
}

Wt::WButtonGroup * room::getGroup() {
  return bgroup;
}

void room::setStatus(y::utils::proxy::STATUS status, bool silent) {
  assert(status != y::utils::proxy::INVALID);
  
  switch(status) {
    case y::utils::proxy::OPEN  : {
      label->setStyleClass("label label-success");
      bgroup->setSelectedButtonIndex(y::utils::proxy::OPEN);
      break;
    }
    case y::utils::proxy::FILTER: {
      label->setStyleClass("label label-warning"); 
      bgroup->setSelectedButtonIndex(y::utils::proxy::FILTER);
      break;
    }
    case y::utils::proxy::CLOSED: {
      label->setStyleClass("label label-danger" );
      bgroup->setSelectedButtonIndex(y::utils::proxy::CLOSED);
      break;
    }
  }
  
  if(!silent) {
    y::utils::Proxy().status(this->name, status);
    y::utils::Proxy().apply();
  }
  
}

Wt::WWidget * proxyManager::get() {
  
  Wt::WTable * table = new Wt::WTable();
  
  container<y::data::row> rows;
  y::utils::Proxy().getAllRooms(rows);
  
  for(int i = 0; i < rows.elms(); i++) {
    rooms.emplace_back(rows[i]["ID"].asString(), this);
    rooms.back().create(table->rowAt(i));
    rooms.back().setStatus((y::utils::proxy::STATUS)rows[i]["status"].asInt(), true);
  }
  
  
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
