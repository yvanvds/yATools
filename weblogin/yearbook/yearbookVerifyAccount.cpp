/* 
 * File:   yearbookVerifyAccount.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 1:45 PM
 */

#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WLineEdit>
#include <Wt/WDateEdit>
#include <Wt/WLengthValidator>

#include "yearbookVerifyAccount.h"
#include "yearbookDB.h"

void yearbookVerifyAccount::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h3>Stap 1</h3>"));
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
  nameEdit->changed().connect(this, &yearbookVerifyAccount::nameEditChanged);

  Wt::WLengthValidator * validator = new Wt::WLengthValidator();
  validator->setMinimumLength(2);
  validator->setMandatory(true);
  nameEdit->setValidator(validator);
  
  surnameEdit = new Wt::WLineEdit();
  surnameEdit->setWidth(200);
  surnameEdit->setHeight(35);
  surnameEdit->changed().connect(this, &yearbookVerifyAccount::surnameEditChanged); 
  surnameEdit->setValidator(validator);
  
  groupEdit = new Wt::WLineEdit();
  groupEdit->setWidth(200);
  groupEdit->setHeight(35);
  groupEdit->changed().connect(this, &yearbookVerifyAccount::groupEditChanged); 

  dateEdit = new Wt::WDateEdit();
  dateEdit->setWidth(200);
  dateEdit->setHeight(35);
  dateEdit->changed().connect(this, &yearbookVerifyAccount::dateEditChanged);
  
  mailEdit = new Wt::WLineEdit();
  mailEdit->setWidth(200);
  mailEdit->setHeight(35);
  mailEdit->changed().connect(this, &yearbookVerifyAccount::mailEditChanged); 
  
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

void yearbookVerifyAccount::onShow() {
  nameEdit->setText(YearbookDB().name());
  surnameEdit->setText(YearbookDB().surname());
  groupEdit->setText(YearbookDB().group());
  dateEdit->setDate(YearbookDB().birthday());
  mailEdit->setText(YearbookDB().mail());
  nameEdit->setFocus();
}

void yearbookVerifyAccount::nameEditChanged() {
  if(nameEdit->validate() == Wt::WValidator::Valid) {
    YearbookDB().name(nameEdit->text());
    feedback->setText("Je naam werd gewijzigd.");
    feedback->setStyleClass("alert alert-success");
    nameEdit->setStyleClass("form-control");
    allOK = true;
  } else {
    feedback->setText("Zo kort kan een naam niet zijn.");
    feedback->setStyleClass("alert alert-danger");
    nameEdit->setStyleClass("form-control invalid");
    nameEdit->setFocus();
    allOK = false;
  }
}

void yearbookVerifyAccount::surnameEditChanged() {
  if(surnameEdit->validate() == Wt::WValidator::Valid) {
    feedback->setText("Je familienaam werd gewijzigd.");
    feedback->setStyleClass("alert alert-success");
    nameEdit->setStyleClass("form-control");
    YearbookDB().surname(surnameEdit->text());
    allOK = true;
  } else {
    feedback->setText("Zo kort kan een naam niet zijn.");
    feedback->setStyleClass("alert alert-danger");
    surnameEdit->setStyleClass("form-control invalid");
    surnameEdit->setFocus();
    allOK = false;
  }
}

void yearbookVerifyAccount::groupEditChanged() {
  yearbookDB().group(groupEdit->text());
}

void yearbookVerifyAccount::dateEditChanged() {
  if(dateEdit->date().isValid()) {
    YearbookDB().birthday(dateEdit->date());
    feedback->setText("Je geboortedatum werd gewijzigd.");
    feedback->setStyleClass("alert alert-success");
    dateEdit->setStyleClass("form-control");
    allOK = true;
    
  } else {
    feedback->setText("Deze datum is niet geldig");
    feedback->setStyleClass("alert alert-danger");
    dateEdit->setStyleClass("form-control invalid");
    dateEdit->setFocus();
    allOK = false;
  }
}

void yearbookVerifyAccount::mailEditChanged() {
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
  if(value.find("sanctamaria") != std::string::npos) {
    valid = false;
    message = "dit adres wordt binnenkort afgesloten";
  }
  if(valid) {
    YearbookDB().mail(mailEdit->text());
    feedback->setText("Je email adres werd gewijzigd.");
    feedback->setStyleClass("alert alert-success");
    mailEdit->setStyleClass("form-control");
    allOK = true;
  } else {
    feedback->setText(message);
    feedback->setStyleClass("alert alert-danger");
    mailEdit->setStyleClass("form-control invalid");
    mailEdit->setFocus();
    allOK = false;
  }
  
}

bool yearbookVerifyAccount::onNext() {
  allOK = false;
  nameEditChanged();
  if(!allOK) return false;
  surnameEditChanged();
  if(!allOK) return false;
  dateEditChanged();
  if(!allOK) return false;
  mailEditChanged();
  if(!allOK) return false;
  
  YearbookDB().saveUser();
  return true;  
}