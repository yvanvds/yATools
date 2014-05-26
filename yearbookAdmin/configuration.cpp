/* 
 * File:   configuration.cpp
 * Author: yvan
 * 
 * Created on May 20, 2014, 8:45 PM
 */

#include <Wt/WWebWidget>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WTable>

#include "configuration.h"
#include "yearbookAdmin.h"

configuration::configuration(yearbookAdmin * parent) : parent(parent) {
  //this->setContentAlignment(Wt::AlignCenter | Wt::AlignTop);
  //this->setWidth("800px");
  
  {
    Wt::WText * title = new Wt::WText("<h1>Activatie</h1>");
    title->addStyleClass("page-header");
    this->addWidget(title);
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    this->addWidget(group);
    
    group->addWidget(new Wt::WText("<p>Tijdens deze periode zijn nieuwe inzendingen mogelijk. Een inzending kan gewijzigd worden tot de einddatum.</p>"));
    
    Wt::WTable * table = new Wt::WTable();

    table->elementAt(0,0)->addWidget(new Wt::WText("Open jaarboek op"));
    table->elementAt(1,0)->addWidget(new Wt::WText("Sluit jaarboek op"));

    openDate = new Wt::WDateEdit();
    table->elementAt(0,1)->addWidget(openDate);
    openDate->changed().connect(this, &configuration::openDateChanged);

    closeDate = new Wt::WDateEdit();
    table->elementAt(1,1)->addWidget(closeDate);
    closeDate->changed().connect(this, &configuration::closeDateChanged);

    currentDate = new Wt::WText("current status is unknown");
    currentDate->setStyleClass("alert alert-danger");

    table->elementAt(2,1)->addWidget(currentDate);
    table->rowAt(2)->setHeight("60px");
    table->rowAt(2)->elementAt(1)->setVerticalAlignment(Wt::AlignmentFlag::AlignBottom);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    } 

    group->addWidget(table);
    
    
  }
  
  {
    Wt::WText * title = new Wt::WText("<h1>Vragen</h1>");
    title->addStyleClass("page-header");
    this->addWidget(title);
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    this->addWidget(group);
    Wt::WTable * table = new Wt::WTable();

    table->elementAt(0,0)->addWidget(new Wt::WText("Vraag 1"));
    table->elementAt(1,0)->addWidget(new Wt::WText("Vraag 2"));
    table->elementAt(2,0)->addWidget(new Wt::WText("Vraag 3"));
    table->elementAt(3,0)->addWidget(new Wt::WText("Vraag 4"));
    
    question1 = new Wt::WLineEdit();
    question1->setTextSize(70);
    question1->changed().connect(this, &configuration::question1Changed);
    table->elementAt(0,1)->addWidget(question1);

    question2 = new Wt::WLineEdit();
    question2->setTextSize(70);
    question2->changed().connect(this, &configuration::question2Changed);
    table->elementAt(1,1)->addWidget(question2);
    
    question3 = new Wt::WLineEdit();
    question3->setTextSize(70);
    question3->changed().connect(this, &configuration::question3Changed);
    table->elementAt(2,1)->addWidget(question3);
    
    question4 = new Wt::WLineEdit();
    question4->setTextSize(70);
    question4->changed().connect(this, &configuration::question4Changed);
    table->elementAt(3,1)->addWidget(question4);

    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    } 

    group->addWidget(table);
  }
  
  {
    Wt::WText * title = new Wt::WText("<h1>Beheerders</h1>");
    title->addStyleClass("page-header");
    this->addWidget(title);
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    this->addWidget(group);
    
    group->addWidget(new Wt::WText("<p>De accounts in deze lijst hebben toegang tot deze interface.</p>"));
  
    Wt::WTable * table = new Wt::WTable();
    table->elementAt(0,0)->setRowSpan(3);
    
    users = new Wt::WSelectionBox();
    users->setMargin(10, Wt::Right);
    users->setLineHeight(5);
    users->setWidth(100);
    users->setSelectionMode(Wt::ExtendedSelection);
    table->elementAt(0, 0)->addWidget(users);
    
    newUser = new Wt::WLineEdit();
    table->elementAt(0,1)->addWidget(newUser);
    
    newUserButton = new Wt::WPushButton("voeg toe");
    newUserButton->clicked().connect(this, &configuration::addUserPushed);
    newUserButton->setStyleClass("btn btn-success");
    table->elementAt(0,2)->addWidget(newUserButton);
    
    removeUserButton = new Wt::WPushButton("verwijder selectie");
    removeUserButton->clicked().connect(this, &configuration::removeUserPushed);
    removeUserButton->setStyleClass("btn btn-danger");
    table->elementAt(1,1)->addWidget(removeUserButton);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    }
    
    group->addWidget(table);
  }

  loadContent();
}

void configuration::loadContent() {
  openDate->setDate(parent->db.getOpenDate());
  closeDate->setDate(parent->db.getCloseDate());
  calculateStatus();
  
  question1->setText(parent->db.getQuestion(0));
  question2->setText(parent->db.getQuestion(1));
  question3->setText(parent->db.getQuestion(2));
  question4->setText(parent->db.getQuestion(3));
  
  refreshUsers();
}

void configuration::addUserPushed() {
  parent->db.addUser(newUser->text().toUTF8());
  refreshUsers();
  newUser->setText("");
}

void configuration::removeUserPushed() {
  std::set<int> selection = users->selectedIndexes();
  for(std::set<int>::iterator it = selection.begin(); it != selection.end(); ++it) {
    parent->db.delUser(users->itemText(*it).toUTF8());
  }
  refreshUsers();
}

void configuration::refreshUsers() {
  users->clear();
  for (int i = 0; i < parent->db.validUsers.elms(); i++) {
    users->addItem(parent->db.validUsers[i]["accountName"].asString8());
  }
}

void configuration::openDateChanged() {
  parent->db.setOpenDate(openDate->date());
  calculateStatus();
}

void configuration::closeDateChanged() {
  parent->db.setCloseDate(closeDate->date());
  calculateStatus();
}

void configuration::calculateStatus() {
  Wt::WDate begin =  openDate->date();
  Wt::WDate end = closeDate->date();
  Wt::WDate current;
  current = Wt::WDate::currentServerDate();
  
  if(current >= begin && current <= end) {
    currentDate->setText("De client interface is open.");
    currentDate->setStyleClass("alert alert-success");
  } else {
    currentDate->setText("De client interface is gesloten.");
    currentDate->setStyleClass("alert alert-danger");
  }
}

void configuration::question1Changed() {
  parent->db.setQuestion(0, question1->text());
}

void configuration::question2Changed() {
  parent->db.setQuestion(1, question2->text());
}

void configuration::question3Changed() {
  parent->db.setQuestion(2, question3->text());
}

void configuration::question4Changed() {
  parent->db.setQuestion(3, question4->text());
}


