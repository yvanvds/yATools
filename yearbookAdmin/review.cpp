/* 
 * File:   review.cpp
 * Author: yvan
 * 
 * Created on May 20, 2014, 10:30 PM
 */

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WHBoxLayout>
#include <Wt/WImage>
#include <Wt/WFileResource>

#include "review.h"
#include "yearbookAdmin.h"
#include <boost/bind.hpp>

review::review(yearbookAdmin * parent) : parent(parent) {
  //this->setContentAlignment(Wt::AlignCenter | Wt::AlignTop);
  //this->setWidth("800px");
  
  {
    parent->db.load();
    
    Wt::WText * title = new Wt::WText("<h1>Inzendingen</h1>");
    title->addStyleClass("page-header");
    this->addWidget(title);
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    this->addWidget(group);
    
    Wt::WTable * table = new Wt::WTable(group);
    table->setHeaderCount(1);
    
    table->elementAt(0, 0)->addWidget(new Wt::WText("naam"));
    table->elementAt(0, 1)->addWidget(new Wt::WText("toegevoegd op"));
    table->elementAt(0, 2)->addWidget(new Wt::WText(""));
    
    table->columnAt(0)->setWidth("400px");
    table->columnAt(1)->setWidth("200px");
    table->columnAt(2)->setWidth("100px");
    
    for(int i = 0; i < parent->db.entries.size(); i++) {
      
      Wt::WString str = str8(parent->db.entries[i].name);
      str += " ";
      str += str8(parent->db.entries[i].surname);
      table->elementAt(i+1, 0)->addWidget(new Wt::WText(str));
      
      y::data::dateTime date = parent->db.entries[i].submitDate;
      y::ldap::DATE dldap(y::ldap::DAY(date.day()), y::ldap::MONTH(date.month()), y::ldap::YEAR(date.year()));
      table->elementAt(i+1, 1)->addWidget(new Wt::WText(dldap.asString()));

      Wt::WPushButton * button = new Wt::WPushButton("view");
      button->setWidth("80px");
      button->clicked().connect(boost::bind(&review::openDialog, this, i));
      table->elementAt(i+1, 2)->addWidget(button);
      
      if(parent->db.entries[i].approved) {
        table->rowAt(i+1)->setStyleClass("alert alert-success");
        button->setStyleClass("btn btn-success");
      } else {
        table->rowAt(i+1)->setStyleClass("alert alert-danger");
        button->setStyleClass("btn btn-danger");
      }
    }
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
        table->elementAt(i, j)->setVerticalAlignment(Wt::AlignMiddle);
      }
    }
    
    
    
  }
  
  // create dialog, but hide
  dialog = new Wt::WDialog(parent->root());
  dialog->resize("700px", "500px");
  Wt::WContainerWidget * container = new Wt::WContainerWidget(dialog->contents());
  //container->resize("700px", "500px");
  
  Wt::WHBoxLayout * box = new Wt::WHBoxLayout(container);;
  
  dialogImage = new Wt::WImage();
  dialogImage->setImageLink("http://placekitten.com/200/200");
  //dialogImage->setHeight("200px");
  box->addWidget(dialogImage);
  
  Wt::WTable * dialogTable = new Wt::WTable();
  dialogTable->columnAt(0)->setWidth("100px");
  dialogTable->columnAt(1)->setWidth("300px");
  box->addWidget(dialogTable);
  
  dialogTable->elementAt(0,0)->addWidget(new Wt::WText("voornaam: "));
  dialogName = new Wt::WLineEdit();
  dialogTable->elementAt(0,1)->addWidget(dialogName);
  
  dialogTable->elementAt(1,0)->addWidget(new Wt::WText("naam: "));
  dialogSurname = new Wt::WLineEdit();
  dialogTable->elementAt(1,1)->addWidget(dialogSurname);
  
  for(int i = 0; i < dialogTable->rowCount(); i++) {
    for(int j = 0; j < dialogTable->columnCount(); j++) {
      dialogTable->elementAt(i, j)->setPadding(5);
      dialogTable->elementAt(i, j)->setVerticalAlignment(Wt::AlignMiddle);
    }
  }
  
  
  dialog->rejectWhenEscapePressed(true);
  dialog->hide();
}

void review::openDialog(int withEntry) {
  currentEntry = withEntry;
  loadDialogContent();
  dialog->show();
}

void review::loadDialogContent() {
  Wt::WString title;
  title = str8(parent->db.entries[currentEntry].name);
  title += " ";
  title += str8(parent->db.entries[currentEntry].surname);
  dialog->setWindowTitle(title);
  
  if(parent->db.entries[currentEntry].photo.empty()) {
    dialogImage->setImageLink("http://placekitten.com/200/200");
  } else {
    Wt::WFileResource * r = new Wt::WFileResource(str8(parent->db.entries[currentEntry].photo));
    dialogImage->setImageLink(r);
    //dialogImage->setHeight("200px");
  }
  
  dialogName->setText(str8(parent->db.entries[currentEntry].name));
  dialogSurname->setText(str8(parent->db.entries[currentEntry].surname));
}