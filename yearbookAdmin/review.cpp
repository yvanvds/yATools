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
#include <Wt/WTextArea>

review::review(yearbookAdmin * parent) : parent(parent) , warningAtRemove(this) {
  //this->setContentAlignment(Wt::AlignCenter | Wt::AlignTop);
  //this->setWidth("800px");
  
  {
    parent->db.load();
    
    Wt::WString s = "<h1>";
    s += std::to_string(parent->db.entries.size());
    s += " inzendingen</h1>";
    title = new Wt::WText(s);
    title->addStyleClass("page-header");
    this->addWidget(title);
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    this->addWidget(group);
    
    table = new Wt::WTable(group);
    loadTableContent();
    
  }
  
  // create dialog, but hide
  dialog = new Wt::WDialog(parent->root());
  dialog->resize("700px", "600px");
  container = new Wt::WContainerWidget(dialog->contents());
  Wt::WContainerWidget * personInfo = new Wt::WContainerWidget();
  personInfo->setStyleClass("well");
  personInfo->setHeight("300px");
  container->addWidget(personInfo); 
  container->setHeight("400px");
  container->setPadding("10px");
  container->setOverflow(Wt::WContainerWidget::OverflowScroll, Wt::Orientation::Vertical);
  
  Wt::WTable * dialogTable = new Wt::WTable();
  dialogTable->columnAt(0)->setWidth("230px");
  dialogTable->columnAt(1)->setWidth("100px");
  dialogTable->columnAt(2)->setWidth("300px");
  dialogTable->elementAt(0,0)->setRowSpan(5);
  
  personInfo->addWidget(dialogTable);
  
  dialogImage = new Wt::WImage();
  dialogImage->setImageLink("http://placekitten.com/200/200");
  //dialogImage->setHeight("200px");
  dialogTable->elementAt(0,0)->addWidget(dialogImage);
  
  dialogImageButton = new Wt::WPushButton("verwijder foto");
  dialogImageButton->setStyleClass("btn btn-danger");
  dialogImageButton->clicked().connect(this, &review::removeImage);
  dialogTable->elementAt(5,0)->addWidget(dialogImageButton);
  
  dialogTable->elementAt(0,1)->addWidget(new Wt::WText("<b>voornaam:</b>"));
  dialogName = new Wt::WLineEdit();
  dialogTable->elementAt(0,2)->addWidget(dialogName);
  
  dialogTable->elementAt(1,1)->addWidget(new Wt::WText("<b>naam:</b>"));
  dialogSurname = new Wt::WLineEdit();
  dialogTable->elementAt(1,2)->addWidget(dialogSurname);
  
  dialogTable->elementAt(2,1)->addWidget(new Wt::WText("<b>klas:</b>"));
  dialogClass = new Wt::WLineEdit();
  dialogTable->elementAt(2,2)->addWidget(dialogClass);
  
  dialogTable->elementAt(3,1)->addWidget(new Wt::WText("<b>verjaardag:</b>"));
  dialogBirthday = new Wt::WText();
  dialogTable->elementAt(3,2)->addWidget(dialogBirthday);
  
  dialogTable->elementAt(4,1)->addWidget(new Wt::WText("<b>email:</b>"));
  dialogEmail = new Wt::WText();
  dialogTable->elementAt(4,2)->addWidget(dialogEmail);
  
  for(int i = 0; i < dialogTable->rowCount(); i++) {
    for(int j = 0; j < dialogTable->columnCount(); j++) {
      dialogTable->elementAt(i, j)->setPadding(5);
      dialogTable->elementAt(i, j)->setVerticalAlignment(Wt::AlignMiddle);
    }
  }
  Wt::WString s;
  s = "<p>";
  s += parent->db.getQuestion(0);
  s += "</p>";
  container->addWidget(new Wt::WText(s));
  answer1 = new Wt::WTextArea();
  answer1->setRows(4);
  answer1->setColumns(60);
  container->addWidget(answer1);
  
  s = "<p>";
  s += parent->db.getQuestion(1);
  s += "</p>";
  container->addWidget(new Wt::WBreak());
  container->addWidget(new Wt::WText(s));
  answer2 = new Wt::WTextArea();
  answer2->setRows(4);
  answer2->setColumns(60);
  container->addWidget(answer2);
  
  s = "<p>";
  s += parent->db.getQuestion(2);
  s += "</p>";
  container->addWidget(new Wt::WText(s));
  answer3 = new Wt::WTextArea();
  answer3->setRows(4);
  answer3->setColumns(60);
  container->addWidget(answer3);
  
  s = "<p>";
  s += parent->db.getQuestion(3);
  s += "</p>";
  container->addWidget(new Wt::WText(s));
  answer4 = new Wt::WTextArea();
  answer4->setRows(4);
  answer4->setColumns(60);
  container->addWidget(answer4);
  
  Wt::WHBoxLayout * footer = new Wt::WHBoxLayout(dialog->footer());
  
  Wt::WPushButton * remove = new Wt::WPushButton("Verwijder");
  remove->setStyleClass("btn btn-danger");
  remove->clicked().connect(this, &review::entryRemove);
  footer->addWidget(remove);
  
  Wt::WPushButton * cancel = new Wt::WPushButton("Annuleer");
  //cancel->setStyleClass("btn");
  cancel->clicked().connect(this, &review::entryCancel);
  footer->addWidget(cancel);
  
  Wt::WPushButton * save = new Wt::WPushButton("Bewaar");
  //save->setStyleClass("btn");
  save->clicked().connect(this, &review::entrySave);
  footer->addWidget(save);
  
  Wt::WPushButton * approve = new Wt::WPushButton("Goedkeuren en volgende");
  approve->setStyleClass("btn btn-success");
  approve->clicked().connect(this, &review::entryApprove);
  footer->addWidget(approve);
  
  //dialog->rejectWhenEscapePressed(true);
  dialog->hide();
}

void review::openDialog(int withEntry) {
  currentEntry = withEntry;
  if(currentEntry < parent->db.entries.size()) {
    loadDialogContent();
    dialog->show();
  }
}

void review::loadDialogContent() {
  Wt::WString s = "<h1>";
  s += std::to_string(parent->db.entries.size());
  s += " inzendingen</h1>";
  title->setText(s);
  
  Wt::WString title;
  title = strWt(parent->db.entries[currentEntry].name);
  title += " ";
  title += strWt(parent->db.entries[currentEntry].surname);
  dialog->setWindowTitle(title);
  
  if(parent->db.entries[currentEntry].photo.empty()) {
    dialogImage->setImageLink("http://placekitten.com/200/200");
  } else {
    Wt::WFileResource * r = new Wt::WFileResource(str8(parent->db.entries[currentEntry].photo));
    dialogImage->setImageLink(r);
    dialogImage->setHeight("200px");
  }
  
  dialogName->setText(strWt(parent->db.entries[currentEntry].name));
  dialogSurname->setText(strWt(parent->db.entries[currentEntry].surname));
  dialogClass->setText(strWt(parent->db.entries[currentEntry].group));

  y::data::dateTime date = parent->db.entries[currentEntry].birthday;
  y::ldap::DATE dldap(y::ldap::DAY(date.day()), y::ldap::MONTH(date.month()), y::ldap::YEAR(date.year()));      
  dialogBirthday->setText(dldap.asString());
  
  dialogEmail->setText(str8(parent->db.entries[currentEntry].mail));
  
  answer1->setText(strWt(parent->db.entries[currentEntry].answer1));
  answer2->setText(strWt(parent->db.entries[currentEntry].answer2));
  answer3->setText(strWt(parent->db.entries[currentEntry].answer3));
  answer4->setText(strWt(parent->db.entries[currentEntry].answer4));
  std::string script;
  script = container->jsRef();
  script += ".scrollTop = 0";
  container->doJavaScript(script);
}

void review::entryCancel() {
  dialog->hide();
  loadTableContent();
}

void review::entryRemove() {
  dialog->hide();
  warningAtRemove.show();
}

void review::entrySave() {
  saveCurrentEntry();
  currentEntry++;
  if(currentEntry < parent->db.entries.size()) {
    loadDialogContent();
  } else {
    dialog->hide();
    loadTableContent();
  }
}

void review::entryApprove() {
  saveCurrentEntry(true);
  currentEntry++;
  if(currentEntry < parent->db.entries.size()) {
    loadDialogContent();
  } else {
    dialog->hide();
    loadTableContent();
  }
}

void review::removeCurrentEntry() {
  parent->db.remove(currentEntry);
  loadTableContent();
}

void review::loadTableContent() {
  table->clear();
  
  table->setHeaderCount(1);

  Wt::WText * naam = new Wt::WText("naam");
  naam->clicked().connect(this, &review::onNameClicked);
  table->elementAt(0, 0)->addWidget(naam);
  
  Wt::WText * klas = new Wt::WText("klas");
  klas->clicked().connect(this, &review::onGroupClicked);
  table->elementAt(0, 1)->addWidget(klas);
  
  Wt::WText * date = new Wt::WText("gewijzigd op");
  date->clicked().connect(this, &review::onDateClicked);
  table->elementAt(0, 2)->addWidget(date);

  table->columnAt(0)->setWidth("200px");
  table->columnAt(1)->setWidth("200px");
  table->columnAt(2)->setWidth("200px");
  table->columnAt(3)->setWidth("100px");

  for(int i = 0; i < parent->db.entries.size(); i++) {

    Wt::WString str = str8(parent->db.entries[i].name);
    str += " ";
    str += str8(parent->db.entries[i].surname);
    table->elementAt(i+1, 0)->addWidget(new Wt::WText(str));

    table->elementAt(i+1, 1)->addWidget(new Wt::WText(strWt(parent->db.entries[i].group)));
    
    y::data::dateTime date = parent->db.entries[i].submitDate;
    y::ldap::DATE dldap(y::ldap::DAY(date.day()), y::ldap::MONTH(date.month()), y::ldap::YEAR(date.year()));
    table->elementAt(i+1, 2)->addWidget(new Wt::WText(dldap.asString()));

    Wt::WPushButton * button = new Wt::WPushButton("view");
    button->setWidth("80px");
    button->clicked().connect(boost::bind(&review::openDialog, this, i));
    table->elementAt(i+1, 3)->addWidget(button);

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
  table->refresh();
}

void review::saveCurrentEntry(bool approve) {
  entry & e = parent->db.entries[currentEntry];
  e.name = str16(dialogName->text().toUTF8());
  e.surname = str16(dialogSurname->text().toUTF8());
  e.group = str16(dialogClass->text().toUTF8());
  e.answer1 = str16(answer1->text().toUTF8());
  e.answer2 = str16(answer2->text().toUTF8());
  e.answer3 = str16(answer3->text().toUTF8());
  e.answer4 = str16(answer4->text().toUTF8());
  e.approved = approve;
  parent->db.save(currentEntry);
}

void review::onDateClicked() {
  parent->db.reloadEntries("submitDate");
  loadTableContent();
}

void review::onGroupClicked() {
  parent->db.reloadEntries("classgroup");
  loadTableContent();
}

void review::onNameClicked() {
  parent->db.reloadEntries("name");
  loadTableContent();
}

void review::removeImage() {
  parent->db.entries[currentEntry].photo.clear();
  dialogImage->setImageLink("http://placekitten.com/200/200");
}