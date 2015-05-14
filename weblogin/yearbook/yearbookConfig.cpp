/* 
 * File:   yearbookConfig.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 7:16 PM
 */

#include <Wt/WWidget>
#include <Wt/WContainerWidget>
#include <Wt/WTabWidget>
#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WDateEdit>

#include "yearbookConfig.h"
#include "yearbookDB.h"


yearbookConfig & YearbookConfig() {
  static yearbookConfig s;
  return s;
}

void yearbookConfig::loadContent() {
  openDate->setDate(YearbookDB().getOpenDate());
  closeDate->setDate(YearbookDB().getCloseDate());
  calculateStatus();
  
  question1->setText(YearbookDB().getQuestion(0));
  question2->setText(YearbookDB().getQuestion(1));
  question3->setText(YearbookDB().getQuestion(2));
  question4->setText(YearbookDB().getQuestion(3));
}

Wt::WWidget * yearbookConfig::get() { 
  tabs = new Wt::WTabWidget();
  YearbookDB().loadConfig();
  YearbookDB().loadAllUsers("name", true);
  
  /***************************************************************
   Activation
   ***************************************************************/
  {
    Wt::WContainerWidget * activation = new Wt::WContainerWidget();
    tabs->addTab(activation, "Activatie");
    
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    group->setHeight(600);
    activation->addWidget(group);
    
    group->addWidget(new Wt::WText("<p>Tijdens deze periode zijn nieuwe inzendingen mogelijk. Een inzending kan gewijzigd worden tot de einddatum.</p>"));
    
    Wt::WTable * table = new Wt::WTable();

    table->elementAt(0,0)->addWidget(new Wt::WText("Open jaarboek op"));
    table->elementAt(1,0)->addWidget(new Wt::WText("Sluit jaarboek op"));

    openDate = new Wt::WDateEdit();
    table->elementAt(0,1)->addWidget(openDate);
    openDate->changed().connect(this, &yearbookConfig::openDateChanged);

    closeDate = new Wt::WDateEdit();
    table->elementAt(1,1)->addWidget(closeDate);
    closeDate->changed().connect(this, &yearbookConfig::closeDateChanged);

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
  
  /****************************************************************
   Questions
   ***************************************************************/
  {
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    tabs->addTab(group, "Vragen");
    
    group->addWidget(new Wt::WText("Deze vragen worden gesteld aan de leerlingen."));
    Wt::WTable * table = new Wt::WTable();

    table->elementAt(0,0)->addWidget(new Wt::WText("Vraag 1"));
    table->elementAt(1,0)->addWidget(new Wt::WText("Vraag 2"));
    table->elementAt(2,0)->addWidget(new Wt::WText("Vraag 3"));
    table->elementAt(3,0)->addWidget(new Wt::WText("Vraag 4"));
    
    question1 = new Wt::WLineEdit();
    question1->setTextSize(70);
    question1->changed().connect(this, &yearbookConfig::question1Changed);
    table->elementAt(0,1)->addWidget(question1);

    question2 = new Wt::WLineEdit();
    question2->setTextSize(70);
    question2->changed().connect(this, &yearbookConfig::question2Changed);
    table->elementAt(1,1)->addWidget(question2);
    
    question3 = new Wt::WLineEdit();
    question3->setTextSize(70);
    question3->changed().connect(this, &yearbookConfig::question3Changed);
    table->elementAt(2,1)->addWidget(question3);
    
    question4 = new Wt::WLineEdit();
    question4->setTextSize(70);
    question4->changed().connect(this, &yearbookConfig::question4Changed);
    table->elementAt(3,1)->addWidget(question4);

    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    } 

    group->addWidget(table);
  }
  
  /***************************************************************
   Classes
   ****************************************************************/
  {  
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    tabs->addTab(group, "Klassen");
    
    group->addWidget(new Wt::WText("<p>Geef hier de volledige naam voor elke klascode in.</p>"));
    
    Wt::WTable * table = new Wt::WTable(group);
    int tableIndex = 0;
    container<yearbookDB::entry> & entries = YearbookDB().getEntries();
    
    for (int i = 0; i < entries.elms(); i++) {
      std::wstring group = entries[i].group;
      bool inList = false;
      
      // see if we have this group in our list
      for (int j = 0; j < replacements.elms(); j++) {
        if (replacements[j].key.compare(group) == 0) {
          inList = true;
        }
      }
      
      // if not, add it
      if(!inList) {
        replacement & r = replacements.New();
        r.key = group;
        r.value = new Wt::WLineEdit();
        r.value->setWidth("150px");
        table->elementAt(tableIndex, 0)->addWidget(new Wt::WText(r.key));
        table->elementAt(tableIndex, 1)->addWidget(r.value);
        tableIndex++;
        
        // see if this exists in the database
        for(int j = 0; j < YearbookDB().getReplacements().elms(); j++) {
          if(YearbookDB().getReplacements()[j][L"original"].asString().compare(r.key) == 0) {
            r.value->setText(
              YearbookDB().getReplacements()[j][L"replacement"].asString()
            );
            break;
          }
        }
        
      }
    }
    
    Wt::WPushButton * button = new Wt::WPushButton("bewaren");
    button->clicked().connect(this, &yearbookConfig::replacementChange);
    button->setStyleClass("btn btn-success");
    button->setWidth("150px");
    table->elementAt(tableIndex, 1)->addWidget(button);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    }
  }
  loadContent();
  return tabs;
}

void yearbookConfig::openDateChanged() {
  YearbookDB().setOpenDate(openDate->date());
  calculateStatus();
}

void yearbookConfig::closeDateChanged() {
  YearbookDB().setCloseDate(closeDate->date());
  calculateStatus();
}

void yearbookConfig::calculateStatus() {
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

void yearbookConfig::question1Changed() {
  YearbookDB().setQuestion(0, question1->text());
}

void yearbookConfig::question2Changed() {
  YearbookDB().setQuestion(1, question2->text());
}

void yearbookConfig::question3Changed() {
  YearbookDB().setQuestion(2, question3->text());
}

void yearbookConfig::question4Changed() {
  YearbookDB().setQuestion(3, question4->text());
}

void yearbookConfig::replacementChange() {
  for (int i = 0; i < replacements.elms(); i++) {
    YearbookDB().replace(replacements[i].key, (replacements[i].value->text()));
  }
}