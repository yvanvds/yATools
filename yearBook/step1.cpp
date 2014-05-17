/* 
 * File:   step1.cpp
 * Author: yvan
 * 
 * Created on May 13, 2014, 8:24 PM
 */

#include "step1.h"
#include "yearBook.h"

#include <gui/application.h>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WPanel>
#include <Wt/WDialog>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WBootstrapTheme>
#include <Wt/WTable>
#include <Wt/WLengthValidator>

void step1::setContent(Wt::WVBoxLayout * box) { 
  box->addWidget(new Wt::WText("<h1>Stap 1</h1>"));
  box->addWidget(new Wt::WText("<p>Kijk eerst even na of dit juist is, en verbeter indien nodig.</p><p></p>"));
  
  table = new Wt::WTable();

  table->elementAt(0,0)->addWidget(new Wt::WText("je voornaam: "));
  table->elementAt(1,0)->addWidget(new Wt::WText("je naam: "));
  table->elementAt(2,0)->addWidget(new Wt::WText("je klas: "));
  table->elementAt(3,0)->addWidget(new Wt::WText("je geboortedatum: "));
  table->elementAt(4,0)->addWidget(new Wt::WText("je email: "));
  
  nameEdit = new Wt::WLineEdit();
  nameEdit->setWidth(200);
  nameEdit->setHeight(35);
  nameEdit->changed().connect(this, &step1::nameEditChanged);

  Wt::WLengthValidator * validator = new Wt::WLengthValidator();
  validator->setMinimumLength(2);
  validator->setMandatory(true);
  nameEdit->setValidator(validator);
  
  surnameEdit = new Wt::WLineEdit();
  surnameEdit->setWidth(200);
  surnameEdit->setHeight(35);
  surnameEdit->changed().connect(this, &step1::surnameEditChanged); 
  surnameEdit->setValidator(validator);
  
  groupEdit = new Wt::WLineEdit();
  groupEdit->setWidth(200);
  groupEdit->setHeight(35);
  groupEdit->changed().connect(this, &step1::groupEditChanged); 

  dateEdit = new Wt::WDateEdit();
  dateEdit->setWidth(200);
  dateEdit->setHeight(35);
  dateEdit->changed().connect(this, &step1::dateEditChanged);
  
  mailEdit = new Wt::WLineEdit();
  mailEdit->setWidth(200);
  mailEdit->setHeight(35);
  mailEdit->changed().connect(this, &step1::mailEditChanged); 
  
  table->elementAt(0,1)->addWidget(nameEdit);
  table->elementAt(1,1)->addWidget(surnameEdit);
  table->elementAt(2,1)->addWidget(groupEdit);
  table->elementAt(3,1)->addWidget(dateEdit);
  table->elementAt(4,1)->addWidget(mailEdit);
  
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 2; j++) {
      table->elementAt(i, j)->setPadding(5);
    }
  } 
  
  box->addWidget(table, 1, Wt::AlignCenter);
  feedback = new Wt::WText("");
  box->addWidget(feedback);
  
  nameEdit->setFocus();
}

void step1::nameEditChanged() {
  if(nameEdit->validate() == Wt::WValidator::Valid) {
    parent->name = nameEdit->text();
    feedback->setText("Je naam werd gewijzigd.");
    feedback->setStyleClass("alert alert-success");
    nameEdit->setStyleClass("form-control");
  } else {
    feedback->setText("Zo kort kan een naam niet zijn.");
    feedback->setStyleClass("alert alert-danger");
    nameEdit->setStyleClass("form-control invalid");
  }
}

void step1::surnameEditChanged() {
  if(surnameEdit->validate() == Wt::WValidator::Valid) {
    parent->surname = surnameEdit->text();
    feedback->setText("Je familienaam werd gewijzigd.");
    feedback->setStyleClass("alert alert-success");
    nameEdit->setStyleClass("form-control");
  } else {
    feedback->setText("Zo kort kan een naam niet zijn.");
    feedback->setStyleClass("alert alert-danger");
    surnameEdit->setStyleClass("form-control invalid");
  }
}

void step1::groupEditChanged() {
  parent->store.group(groupEdit->text());
}

void step1::dateEditChanged() {
  if(dateEdit->date().isValid()) {
    parent->store.birthday(dateEdit->date());
    feedback->setText("Je geboortedatum werd gewijzigd.");
    feedback->setStyleClass("alert alert-success");
    dateEdit->setStyleClass("form-control");
    
  } else {
    feedback->setText("Deze datum is niet geldig");
    feedback->setStyleClass("alert alert-danger");
    dateEdit->setStyleClass("form-control invalid");
  }
}

void step1::mailEditChanged() {
  bool valid = true;
  Wt::WString message;
  
  std::string value = mailEdit->text().toUTF8();
  if (value.length() < 6) {
    valid = false;
    message = "je email adres is te kort";
  }

  if(value.find('@') == std::string::npos) {
    valid = false;
    message = "dit is geen geldig email adres";
  } 
  
  if(value.find('.') == std::string::npos) {
    valid = false;
    message = "dit is geen geldig email adres";
  } 
  if(valid) {
    parent->store.mail(mailEdit->text());
    feedback->setText("Je email adres werd gewijzigd.");
    feedback->setStyleClass("alert alert-success");
    mailEdit->setStyleClass("form-control");
  } else {
    feedback->setText(message);
    feedback->setStyleClass("alert alert-danger");
    mailEdit->setStyleClass("form-control invalid");
  }
  
}

void step1::onShow() {
  nameEdit->setText(parent->store.name());
  surnameEdit->setText(parent->store.surname());
  groupEdit->setText(parent->store.group());
  dateEdit->setDate(parent->store.birthday());
  mailEdit->setText(parent->store.mail());
}