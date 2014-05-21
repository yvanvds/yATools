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
    Wt::WTable * table = new Wt::WTable();

    table->elementAt(0,0)->addWidget(new Wt::WText("Open jaarboek op"));
    table->elementAt(1,0)->addWidget(new Wt::WText("Sluit jaarboek op"));

    openDate = new Wt::WDateEdit();
    table->elementAt(0,1)->addWidget(openDate);

    closeDate = new Wt::WDateEdit();
    table->elementAt(1,1)->addWidget(closeDate);

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
    table->elementAt(0,1)->addWidget(question1);

    question2 = new Wt::WLineEdit();
    question2->setTextSize(70);
    table->elementAt(1,1)->addWidget(question2);
    
    question3 = new Wt::WLineEdit();
    question3->setTextSize(70);
    table->elementAt(2,1)->addWidget(question3);
    
    question4 = new Wt::WLineEdit();
    question4->setTextSize(70);
    table->elementAt(3,1)->addWidget(question4);

    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    } 

    group->addWidget(table);
  }
  
}
