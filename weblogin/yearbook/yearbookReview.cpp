/* 
 * File:   yearbookReview.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 10:18 PM
 */

#include <Wt/WWidget>
#include <Wt/WTable>
#include <Wt/WContainerWidget>
#include <Wt/WImage>
#include <Wt/WTextArea>
#include <Wt/WHBoxLayout>
#include <Wt/WFileResource>
#include <Wt/WScrollArea>
#include <Wt/WPainter>
#include <Wt/WLineEdit>
#include <Wt/WBreak>

#include "yearbookReview.h"
#include "yearbookDB.h"
#include "../base/imageConvert.h"

yearbookReview::yearbookReview(yearbookDB* ptr) : db(ptr), dialogResource(nullptr) {
  db->loadConfig();
  db->loadAllUsers("name", true);
  
  //mainWidget->addStyleClass("well");
  setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  setOverflow(Wt::WContainerWidget::OverflowScroll, Wt::Orientation::Vertical);
  setHeight(600);
  
  string s = "<h3>";
  s += db->getEntries().elms();
  s += " inzendingen</h3>";
  title = new Wt::WText(s.wt());
  title->addStyleClass("page-header");
  addWidget(title);
  
  table = new Wt::WTable();
  addWidget(table);
  loadTableContent();
  createDialog();

  //warningAtRemove = new yearbookConfirmRemove();
  //warningAtRemove->setParent(this);
}

yearbookReview::~yearbookReview() {
  if(dialogResource != nullptr) {
    delete dialogResource;
  }
}

void yearbookReview::createDialog() {
  dialog = new Wt::WDialog(this);
  dialog->resize("700px", "600px");
  dialogContainer = new Wt::WContainerWidget(dialog->contents());
  Wt::WContainerWidget * personInfo = new Wt::WContainerWidget();
  personInfo->setStyleClass("well");
  personInfo->setHeight("300px");
  dialogContainer->addWidget(personInfo); 
  dialogContainer->setHeight("400px");
  dialogContainer->setPadding("10px");
  dialogContainer->setOverflow(Wt::WContainerWidget::OverflowScroll, Wt::Orientation::Vertical);
  
  dialogTable = new Wt::WTable();
  dialogTable->columnAt(0)->setWidth("230px");
  dialogTable->columnAt(1)->setWidth("100px");
  dialogTable->columnAt(2)->setWidth("300px");
  dialogTable->elementAt(0,0)->setRowSpan(5);
  
  personInfo->addWidget(dialogTable);
  
  dialogImage = new Wt::WImage();
  if(dialogResource != nullptr) delete dialogResource;
  dialogResource = new Wt::WFileResource("yearbook_latex/Pictures/placeholder.jpg");
  dialogImage->setImageLink(dialogResource);
  dialogImage->resize("300px", "200px");
  dialogTable->elementAt(0,0)->addWidget(dialogImage);
  
  dialogImageButton = new Wt::WPushButton("verwijder foto");
  dialogImageButton->setStyleClass("btn btn-danger");
  dialogImageButton->clicked().connect(this, &yearbookReview::removeImage);
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
  string s;
  s = "<p>";
  s += db->getQuestion(0);
  s += "</p>";
  dialogContainer->addWidget(new Wt::WText(s.wt()));
  answer1 = new Wt::WTextArea();
  answer1->setRows(4);
  answer1->setColumns(60);
  dialogContainer->addWidget(answer1);
  
  s = "<p>";
  s += db->getQuestion(1);
  s += "</p>";
  dialogContainer->addWidget(new Wt::WBreak());
  dialogContainer->addWidget(new Wt::WText(s.wt()));
  answer2 = new Wt::WTextArea();
  answer2->setRows(4);
  answer2->setColumns(60);
  dialogContainer->addWidget(answer2);
  
  s = "<p>";
  s += db->getQuestion(2);
  s += "</p>";
  dialogContainer->addWidget(new Wt::WText(s.wt()));
  answer3 = new Wt::WTextArea();
  answer3->setRows(4);
  answer3->setColumns(60);
  dialogContainer->addWidget(answer3);
  
  s = "<p>";
  s += db->getQuestion(3);
  s += "</p>";
  dialogContainer->addWidget(new Wt::WText(s.wt()));
  answer4 = new Wt::WTextArea();
  answer4->setRows(4);
  answer4->setColumns(60);
  dialogContainer->addWidget(answer4);
  
  Wt::WHBoxLayout * footer = new Wt::WHBoxLayout(dialog->footer());
  
  Wt::WPushButton * remove = new Wt::WPushButton("Verwijder");
  remove->setStyleClass("btn btn-danger");
  remove->clicked().connect(this, &yearbookReview::entryRemove);
  footer->addWidget(remove);
  
  Wt::WPushButton * cancel = new Wt::WPushButton("Annuleer");
  //cancel->setStyleClass("btn");
  cancel->clicked().connect(this, &yearbookReview::entryCancel);
  footer->addWidget(cancel);
  
  Wt::WPushButton * save = new Wt::WPushButton("Bewaar");
  //save->setStyleClass("btn");
  save->clicked().connect(this, &yearbookReview::entrySave);
  footer->addWidget(save);
  
  Wt::WPushButton * approve = new Wt::WPushButton("Goedkeuren en volgende");
  approve->setStyleClass("btn btn-success");
  approve->clicked().connect(this, &yearbookReview::entryApprove);
  footer->addWidget(approve);
  
  //dialog->rejectWhenEscapePressed(true);
  dialog->hide();
}

void yearbookReview::openDialog(int withEntry) {
  currentEntry = withEntry;
  if(currentEntry < db->getEntries().elms()) {
    loadDialogContent();
    dialog->show();
  }
}

void yearbookReview::loadDialogContent() {
  string s("<h3>");
  s += db->getEntries().elms();
  s += " inzendingen</h3>";
  title->setText(s.wt());
  
  string title;
  title = db->getEntries()[currentEntry].name;
  title += " ";
  title += db->getEntries()[currentEntry].surname;
  dialog->setWindowTitle(title.wt());
  
  dialogTable->elementAt(0,0)->removeWidget(dialogImage);
  delete dialogImage;
  dialogImage = new Wt::WImage();
  
  if(db->getEntries()[currentEntry].photo.empty()) {
    if(dialogResource != nullptr) delete dialogResource;
    dialogResource = new Wt::WFileResource("yearbook_latex/Pictures/placeholder.jpg");
    dialogImage->setImageLink(dialogResource);
    dialogImage->resize("300px", "200px");
  } else {
    string s = db->getEntries()[currentEntry].photo;
    
    if(dialogResource != nullptr) delete dialogResource;
    dialogResource = new Wt::WFileResource(s.utf8());
    dialogImage->setImageLink(dialogResource);
    
    int _width;
    int _height;
    GetDimensions(s.c_str(), _width, _height);
    float _ratio;
    
    if(_width > _height) {
      _ratio = _width / 300.f;
    } else {
      _ratio = _height / 200.f;
    }
    _width /= _ratio;
    _height /= _ratio;
    Wt::WLength w(_width);
    Wt::WLength h(_height);
    dialogImage->resize(w, h);
  }
  
  dialogTable->elementAt(0,0)->addWidget(dialogImage);
  
  dialogName->setText(db->getEntries()[currentEntry].name.wt());
  dialogSurname->setText(db->getEntries()[currentEntry].surname.wt());
  dialogClass->setText(db->getEntries()[currentEntry].group.wt());

  y::data::dateTime date = db->getEntries()[currentEntry].birthday;
  DATE dldap(DAY(date.day()), MONTH(date.month()), YEAR(date.year()));      
  dialogBirthday->setText(dldap.get().wt());
  
  dialogEmail->setText(db->getEntries()[currentEntry].mail.wt());
  
  answer1->setText(db->getEntries()[currentEntry].answer1.wt());
  answer2->setText(db->getEntries()[currentEntry].answer2.wt());
  answer3->setText(db->getEntries()[currentEntry].answer3.wt());
  answer4->setText(db->getEntries()[currentEntry].answer4.wt());
  string script;
  script = dialogContainer->jsRef();
  script += ".scrollTop = 0";
  dialogContainer->doJavaScript(script.utf8());
}


void yearbookReview::entryCancel() {
  dialog->hide();
  loadTableContent();
}

void yearbookReview::entryRemove() {
  dialog->hide();
  TODO(show warning again)
  //warningAtRemove.show();
  removeCurrentEntry();
}

void yearbookReview::entrySave() {
  saveCurrentEntry();
  currentEntry++;
  if(currentEntry < db->getEntries().elms()) {
    loadDialogContent();
  } else {
    dialog->hide();
    loadTableContent();
  }
}

void yearbookReview::entryApprove() {
  saveCurrentEntry(true);
  currentEntry++;
  if(currentEntry < db->getEntries().elms()) {
    loadDialogContent();
  } else {
    dialog->hide();
    loadTableContent();
  }
}

void yearbookReview::removeCurrentEntry() {
  db->removeUser(currentEntry);
  loadTableContent();
}

void yearbookReview::loadTableContent() {
  table->clear();
  
  table->setHeaderCount(1);

  Wt::WText * naam = new Wt::WText("naam");
  naam->clicked().connect(this, &yearbookReview::onNameClicked);
  table->elementAt(0, 0)->addWidget(naam);
  
  Wt::WText * klas = new Wt::WText("klas");
  klas->clicked().connect(this, &yearbookReview::onGroupClicked);
  table->elementAt(0, 1)->addWidget(klas);
  
  Wt::WText * date = new Wt::WText("gewijzigd op");
  date->clicked().connect(this, &yearbookReview::onDateClicked);
  table->elementAt(0, 2)->addWidget(date);

  table->columnAt(0)->setWidth("200px");
  table->columnAt(1)->setWidth("200px");
  table->columnAt(2)->setWidth("200px");
  table->columnAt(3)->setWidth("100px");

  container<yearbookDB::entry> & entries = db->getEntries();
  for(int i = 0; i < entries.elms(); i++) {

    string str = entries[i].name;
    str += " ";
    str += entries[i].surname;
    table->elementAt(i+1, 0)->addWidget(new Wt::WText(str.wt()));

    table->elementAt(i+1, 1)->addWidget(new Wt::WText(entries[i].group.wt()));
    
    y::data::dateTime date = entries[i].submitDate;
    DATE dldap(DAY(date.day()), MONTH(date.month()), YEAR(date.year()));
    table->elementAt(i+1, 2)->addWidget(new Wt::WText(dldap.get().wt()));

    Wt::WPushButton * button = new Wt::WPushButton("view");
    button->setWidth("80px");
    button->clicked().connect(boost::bind(&yearbookReview::openDialog, this, i));
    table->elementAt(i+1, 3)->addWidget(button);

    if(entries[i].approved) {
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

void yearbookReview::saveCurrentEntry(bool approve) {
  yearbookDB::entry & e = db->getEntries()[currentEntry];
  e.name = string(dialogName->text());
  e.surname = string(dialogSurname->text());
  e.group = string(dialogClass->text());
  e.answer1 = string(answer1->text());
  e.answer2 = string(answer2->text());
  e.answer3 = string(answer3->text());
  e.answer4 = string(answer4->text());
  e.approved = approve;
  db->saveUser(e);
}

void yearbookReview::onDateClicked() {
  db->loadAllUsers("submitDate", true);
  loadTableContent();
}

void yearbookReview::onGroupClicked() {
  db->loadAllUsers("classgroup", true);
  loadTableContent();
}

void yearbookReview::onNameClicked() {
  db->loadAllUsers("name", true);
  loadTableContent();
}

void yearbookReview::removeImage() {
  db->getEntries()[currentEntry].photo.clear();
  if(dialogResource != nullptr) delete dialogResource;
  dialogResource = new Wt::WFileResource("yearbook_latex/Pictures/placeholder.jpg");
  dialogImage->setImageLink(dialogResource);
  dialogImage->resize("300px", "200px");
}