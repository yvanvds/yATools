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

#include "yearbookReview.h"
#include "yearbookDB.h"

yearbookReview & YearbookReview() {
  static yearbookReview s;
  return s;
}

Wt::WWidget * yearbookReview::get() {
  YearbookDB().loadConfig();
  YearbookDB().loadAllUsers("name", true);
  
  mainWidget = new Wt::WContainerWidget();
  //mainWidget->addStyleClass("well");
  mainWidget->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  mainWidget->setOverflow(Wt::WContainerWidget::OverflowScroll, Wt::Orientation::Vertical);
  mainWidget->setHeight(600);
  
  Wt::WString s = "<h3>";
  s += std::to_string(YearbookDB().getEntries().elms());
  s += " inzendingen</h3>";
  title = new Wt::WText(s);
  title->addStyleClass("page-header");
  mainWidget->addWidget(title);
  
  table = new Wt::WTable(mainWidget);
  mainWidget->addWidget(table);
  loadTableContent();
  createDialog();
 
  return mainWidget;
}

void yearbookReview::createDialog() {
  dialog = new Wt::WDialog(mainWidget);
  dialog->resize("700px", "600px");
  dialogContainer = new Wt::WContainerWidget(dialog->contents());
  Wt::WContainerWidget * personInfo = new Wt::WContainerWidget();
  personInfo->setStyleClass("well");
  personInfo->setHeight("300px");
  dialogContainer->addWidget(personInfo); 
  dialogContainer->setHeight("400px");
  dialogContainer->setPadding("10px");
  dialogContainer->setOverflow(Wt::WContainerWidget::OverflowScroll, Wt::Orientation::Vertical);
  
  Wt::WTable * dialogTable = new Wt::WTable();
  dialogTable->columnAt(0)->setWidth("230px");
  dialogTable->columnAt(1)->setWidth("100px");
  dialogTable->columnAt(2)->setWidth("300px");
  dialogTable->elementAt(0,0)->setRowSpan(5);
  
  personInfo->addWidget(dialogTable);
  
  dialogImage = new Wt::WImage();
  dialogImage->setImageLink("http://placehold.it/600x400");
  dialogImage->setWidth("300px");
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
  Wt::WString s;
  s = "<p>";
  s += YearbookDB().getQuestion(0);
  s += "</p>";
  dialogContainer->addWidget(new Wt::WText(s));
  answer1 = new Wt::WTextArea();
  answer1->setRows(4);
  answer1->setColumns(60);
  dialogContainer->addWidget(answer1);
  
  s = "<p>";
  s += YearbookDB().getQuestion(1);
  s += "</p>";
  dialogContainer->addWidget(new Wt::WBreak());
  dialogContainer->addWidget(new Wt::WText(s));
  answer2 = new Wt::WTextArea();
  answer2->setRows(4);
  answer2->setColumns(60);
  dialogContainer->addWidget(answer2);
  
  s = "<p>";
  s += YearbookDB().getQuestion(2);
  s += "</p>";
  dialogContainer->addWidget(new Wt::WText(s));
  answer3 = new Wt::WTextArea();
  answer3->setRows(4);
  answer3->setColumns(60);
  dialogContainer->addWidget(answer3);
  
  s = "<p>";
  s += YearbookDB().getQuestion(3);
  s += "</p>";
  dialogContainer->addWidget(new Wt::WText(s));
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
  if(currentEntry < YearbookDB().getEntries().elms()) {
    loadDialogContent();
    dialog->show();
  }
}

void yearbookReview::loadDialogContent() {
  std::wstring s(L"<h3>");
  s += strW(std::to_string(YearbookDB().getEntries().elms()));
  s += L" inzendingen</h3>";
  title->setText(s);
  
  std::wstring title;
  title = YearbookDB().getEntries()[currentEntry].name;
  title += L" ";
  title += YearbookDB().getEntries()[currentEntry].surname;
  dialog->setWindowTitle(title);
  
  if(YearbookDB().getEntries()[currentEntry].photo.empty()) {
    dialogImage->setImageLink("http://placehold.it/600x400");
  } else {
    std::string s = str8(YearbookDB().getEntries()[currentEntry].photo);
    Wt::WFileResource * r = new Wt::WFileResource(s);
    dialogImage->setImageLink(r);
    dialogImage->setWidth("300px");
  }
  
  dialogName->setText(YearbookDB().getEntries()[currentEntry].name);
  dialogSurname->setText(YearbookDB().getEntries()[currentEntry].surname);
  dialogClass->setText(YearbookDB().getEntries()[currentEntry].group);

  y::data::dateTime date = YearbookDB().getEntries()[currentEntry].birthday;
  y::ldap::DATE dldap(y::ldap::DAY(date.day()), y::ldap::MONTH(date.month()), y::ldap::YEAR(date.year()));      
  dialogBirthday->setText(dldap.asString());
  
  dialogEmail->setText(str8(YearbookDB().getEntries()[currentEntry].mail));
  
  answer1->setText(YearbookDB().getEntries()[currentEntry].answer1);
  answer2->setText(YearbookDB().getEntries()[currentEntry].answer2);
  answer3->setText(YearbookDB().getEntries()[currentEntry].answer3);
  answer4->setText(YearbookDB().getEntries()[currentEntry].answer4);
  std::string script;
  script = dialogContainer->jsRef();
  script += ".scrollTop = 0";
  dialogContainer->doJavaScript(script);
}


void yearbookReview::entryCancel() {
  dialog->hide();
  loadTableContent();
}

void yearbookReview::entryRemove() {
  dialog->hide();
  warningAtRemove.show();
}

void yearbookReview::entrySave() {
  saveCurrentEntry();
  currentEntry++;
  if(currentEntry < YearbookDB().getEntries().elms()) {
    loadDialogContent();
  } else {
    dialog->hide();
    loadTableContent();
  }
}

void yearbookReview::entryApprove() {
  saveCurrentEntry(true);
  currentEntry++;
  if(currentEntry < YearbookDB().getEntries().elms()) {
    loadDialogContent();
  } else {
    dialog->hide();
    loadTableContent();
  }
}

void yearbookReview::removeCurrentEntry() {
  YearbookDB().removeUser(currentEntry);
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

  container<yearbookDB::entry> & entries = YearbookDB().getEntries();
  for(int i = 0; i < entries.elms(); i++) {

    Wt::WString str = entries[i].name;
    str += " ";
    str += entries[i].surname;
    table->elementAt(i+1, 0)->addWidget(new Wt::WText(str));

    table->elementAt(i+1, 1)->addWidget(new Wt::WText(entries[i].group));
    
    y::data::dateTime date = entries[i].submitDate;
    y::ldap::DATE dldap(y::ldap::DAY(date.day()), y::ldap::MONTH(date.month()), y::ldap::YEAR(date.year()));
    table->elementAt(i+1, 2)->addWidget(new Wt::WText(dldap.asString()));

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
  yearbookDB::entry & e = YearbookDB().getEntries()[currentEntry];
  e.name = strW(dialogName->text().toUTF8());
  e.surname = strW(dialogSurname->text().toUTF8());
  e.group = strW(dialogClass->text().toUTF8());
  e.answer1 = strW(answer1->text().toUTF8());
  e.answer2 = strW(answer2->text().toUTF8());
  e.answer3 = strW(answer3->text().toUTF8());
  e.answer4 = strW(answer4->text().toUTF8());
  e.approved = approve;
  YearbookDB().saveUser(e);
}

void yearbookReview::onDateClicked() {
  YearbookDB().loadAllUsers("submitDate", true);
  loadTableContent();
}

void yearbookReview::onGroupClicked() {
  YearbookDB().loadAllUsers("classgroup", true);
  loadTableContent();
}

void yearbookReview::onNameClicked() {
  YearbookDB().loadAllUsers("name", true);
  loadTableContent();
}

void yearbookReview::removeImage() {
  YearbookDB().getEntries()[currentEntry].photo.clear();
  dialogImage->setImageLink("http://placekitten.com/200/200");
}