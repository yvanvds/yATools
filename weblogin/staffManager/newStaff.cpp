/* 
 * File:   newStaff.cpp
 * Author: yvan
 * 
 * Created on June 19, 2015, 12:19 PM
 */


#include <Wt/WPanel>
#include <Wt/WLineEdit>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WComboBox>
#include <Wt/WDateEdit>
#include <Wt/WPushButton>
#include "newStaff.h"

void newStaff::create() {
  Wt::WPanel * panel = new Wt::WPanel(this);
  panel->setStyleClass("panel panel-primary");
  panel->setTitle("<h3>Personeelslid toevoegen</h3>");
  panel->setMinimumSize(800, 500);
  panel->setMaximumSize(800, Wt::WLength::Auto);
  panel->setMargin("0 auto");
  
  Wt::WContainerWidget * content = new Wt::WContainerWidget();
  panel->setCentralWidget(content);
  content->setPadding("1%");
  
  {
    Wt::WContainerWidget * c = new Wt::WContainerWidget(content);
    c->addStyleClass("well");
    c->setPadding("1%");
    
    Wt::WTable * table = new Wt::WTable();
    c->addWidget(table);
   
    table->elementAt(0,0)->addWidget(new Wt::WText("Voornaam"));
    firstName = new Wt::WLineEdit();
    firstName->resize(200, 35);
    firstName->setStyleClass("form-control");
    table->elementAt(0,1)->addWidget(firstName);
    
    table->elementAt(0,2)->addWidget(new Wt::WText("Naam"));
    surName = new Wt::WLineEdit();
    surName->resize(250, 35);
    surName->setStyleClass("form-control");
    table->elementAt(0,3)->addWidget(surName);
    
    table->elementAt(1,0)->addWidget(new Wt::WText("Geboortedatum"));
    dateOfBirth = new Wt::WDateEdit();
    dateOfBirth->resize(200, 35);
    dateOfBirth->setStyleClass("form-control");
    table->elementAt(1,1)->addWidget(dateOfBirth);
    
    table->elementAt(1,2)->addWidget(new Wt::WText("Gender"));
    gender = new Wt::WComboBox();
    gender->resize(150, 35);
    gender->setStyleClass("form-control");
    
    gender->addItem(GENDER::toText(GENDER::MALE).wt());
    gender->addItem(GENDER::toText(GENDER::FEMALE).wt());
    gender->addItem(GENDER::toText(GENDER::TRANSGENDER).wt());
    table->elementAt(1,3)->addWidget(gender);
    
    table->elementAt(2,0)->addWidget(new Wt::WText("Wisa ID"));
    wisaName = new Wt::WLineEdit();
    wisaName->resize(200, 35);
    wisaName->setStyleClass("form-control");
    table->elementAt(2,1)->addWidget(wisaName);
    
    table->elementAt(2,2)->addWidget(new Wt::WText("Functie"));
    role = new Wt::WComboBox();
    role->resize(150, 35);
    role->setStyleClass("form-control");
    role->addItem("Leraar");
    role->addItem("Secretariaat");
    role->addItem("Directie");
    table->elementAt(2,3)->addWidget(role);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i,j)->setPadding(5);
        table->elementAt(i,j)->setVerticalAlignment(Wt::AlignmentFlag::AlignMiddle);
      }
    }

    table->setStyleClass("panel-body");
  }
  
  saveButton = new Wt::WPushButton("Maak Account");
  saveButton->resize(150, 35);
  saveButton->setStyleClass("btn btn-primary");
  saveButton->clicked().connect(this, &newStaff::addAccount);
  content->addWidget(saveButton);
  
  {
    result = new Wt::WContainerWidget(content);
    result->addStyleClass("well");
    result->setPadding("1%");
    
    Wt::WTable * table = new Wt::WTable();
    result->addWidget(table);
    
    table->elementAt(0,0)->addWidget(new Wt::WText("naam: "));
    resultName = new Wt::WText();
    table->elementAt(0,1)->addWidget(resultName);
    
    table->elementAt(1,0)->addWidget(new Wt::WText("login: "));
    resultUid = new Wt::WText();
    table->elementAt(1,1)->addWidget(resultUid);
    
    table->elementAt(2,0)->addWidget(new Wt::WText("mail: "));
    resultMail = new Wt::WText();
    table->elementAt(2,1)->addWidget(resultMail);
    
    table->elementAt(3,0)->addWidget(new Wt::WText("mail alias: "));
    resultMailAlias = new Wt::WText();
    table->elementAt(3,1)->addWidget(resultMailAlias);
    
    table->elementAt(4,0)->addWidget(new Wt::WText("wachtwoord: "));
    resultPassword = new Wt::WText();
    table->elementAt(4,1)->addWidget(resultPassword);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i,j)->setPadding(5);
        table->elementAt(i,j)->setVerticalAlignment(Wt::AlignmentFlag::AlignMiddle);
      }
    }

    table->setStyleClass("panel-body");
    
    result->hide();
  }  
}

void newStaff::addAccount() {
  if(firstName->text().empty()) {
    firstName->setStyleClass("form-control danger");
    firstName->setFocus();
    return;
  } else {
    firstName->setStyleClass("form-control");
  }
  
  if(surName->text().empty()) {
    surName->setStyleClass("form-control invalid");
    surName->setFocus();
    return;
  } else {
    surName->setStyleClass("form-control");
  }
  
  if(!dateOfBirth->date().isValid()) {
    dateOfBirth->setStyleClass("form-control Wt-invalid");
    dateOfBirth->setFocus();
    return;
  } else {
    dateOfBirth->setStyleClass("form-control");
  }
  
  if(wisaName->text().empty()) {
    wisaName->setStyleClass("form-control invalid");
    wisaName->setFocus();
    return;
  } else {
    wisaName->setStyleClass("form-control");
  }
  
  // if we get here, add the account
  string password(y::utils::Security().makePassword(8));
  
  ROLE::TYPE schoolRole = ROLE::NONE;
  switch(role->currentIndex()) {
    case 0: schoolRole = ROLE::TEACHER; break;
    case 1: schoolRole = ROLE::SUPPORT; break;
    case 2: schoolRole = ROLE::DIRECTOR; break;
  }
  
  y::admin::userAdmin admin(server);
  /*y::ldap::account & account = admin.add(
            CN(firstName->text())
          , SN(surName->text())
          , ROLE(schoolRole)
          , SCHOOLCLASS(" ")
          , DATE(
              DAY(dateOfBirth->date().day())
            , MONTH(dateOfBirth->date().month())
            , YEAR(dateOfBirth->date().year())
          )
          , WISA_ID(0)
          , PASSWORD(password)
  );*/
  server->commitChanges();
  
  //resultName->setText(account.fullName().get().wt());
  //resultUid->setText(account.uid().get().wt());
  //resultMail->setText(account.mail().get().wt());
  //resultMailAlias->setText(account.mail().get().wt());
  resultPassword->setText(password.wt());
  result->show();
  
  //admin.remove(account);
  server->commitChanges();
}