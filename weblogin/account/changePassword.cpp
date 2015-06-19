/* 
 * File:   changePassword.cpp
 * Author: yvan
 * 
 * Created on June 15, 2015, 11:29 AM
 */

#include <Wt/WPanel>
#include <Wt/WTable>
#include <Wt/WRegExpValidator>
#include "../application.h"
#include "changePassword.h"
#include "admintools.h"

void changePassword::create(y::ldap::account* account, application * app) {
  this->account = account;
  this->app = app;
  
  Wt::WPanel * panel = new Wt::WPanel(this);
  panel->setStyleClass("panel panel-primary");
  panel->setTitle("<h3>Wachtwoord Instellingen</h3>");
  panel->setMargin("0 auto");
  panel->setMaximumSize(800, Wt::WLength::Auto);
  
  Wt::WContainerWidget * content = new Wt::WContainerWidget();
  panel->setCentralWidget(content);
  
  content->setPadding("1%");
  
  {
    Wt::WContainerWidget * pw = new Wt::WContainerWidget(content);
    pw->addStyleClass("well");
    pw->setPadding("1%");
    pw->addWidget(new Wt::WText("<h4>Wachtwoord Aanpassen</h4>"));

    pw->addWidget(new Wt::WText("Je wachtwoord zal aangepast worden voor "
    "alle services op school: de computers, smartschool, moodle, gmail en "
    "deze applicatie. Een wachtwoord moet minstens 8 tekens lang zijn, een "
    "hoofdletter, een kleine letter en een cijfer bevaten."));
    
    Wt::WTable * table = new Wt::WTable();
    pw->addWidget(table);

    table->elementAt(0,0)->addWidget(new Wt::WText("Huidig wachtwoord: "));
    table->elementAt(1,0)->addWidget(new Wt::WText("Nieuw wachtwoord: "));
    table->elementAt(2,0)->addWidget(new Wt::WText("Herhaal nieuw wachtwoord: "));

    curPW = new Wt::WLineEdit();
    curPW->setWidth(150);
    curPW->setHeight(50);
    curPW->setStyleClass("form-control");
    curPW->setEchoMode(Wt::WLineEdit::Password);
    table->elementAt(0,1)->addWidget(curPW);

    newPW1 = new Wt::WLineEdit();
    newPW1->setWidth(150);
    newPW1->setHeight(50);
    newPW1->setStyleClass("form-control");
    newPW1->setEchoMode(Wt::WLineEdit::Password);
    table->elementAt(1,1)->addWidget(newPW1);

    newPW2 = new Wt::WLineEdit();
    newPW2->setWidth(150);
    newPW2->setHeight(50);
    newPW2->setStyleClass("form-control");
    newPW2->setEchoMode(Wt::WLineEdit::Password);
    table->elementAt(2,1)->addWidget(newPW2);

    feedback1 = new Wt::WText(" ");
    feedback1->setStyleClass("alert");
    table->elementAt(0,2)->addWidget(feedback1);
    feedback2 = new Wt::WText(" ");
    feedback2->setStyleClass("alert");
    table->elementAt(1,2)->addWidget(feedback2);
    feedback3 = new Wt::WText(" ");
    feedback3->setStyleClass("alert");
    table->elementAt(2,2)->addWidget(feedback3);
    feedback4 = new Wt::WText(" ");
    feedback4->setStyleClass("alert");
    table->elementAt(3,2)->addWidget(feedback4);

    savePW = new Wt::WPushButton("Opslaan");
    savePW->setWidth(150);
    savePW->setStyleClass("btn btn-primary");
    savePW->clicked().connect(this, &changePassword::passwordChanged);
    table->elementAt(3,1)->addWidget(savePW);

    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i,j)->setPadding(5);
        table->elementAt(i,j)->setVerticalAlignment(Wt::AlignmentFlag::AlignMiddle);
      }
    }

    table->setStyleClass("panel-body");
  }
  
  content->addWidget(new Wt::WText(" "));
  
  {
    Wt::WContainerWidget * pw = new Wt::WContainerWidget(content);
    pw->addStyleClass("well");
    pw->setPadding("1%");
    pw->addWidget(new Wt::WText("<h4>Persoonlijk Mailadres</h4>"));

    pw->addWidget(new Wt::WText(
            "Je zal via dit adres nooit mails van de school ontvangen. "
            "Het wordt enkel gebruikt om je wachtwoord te wijzigen in "
            "het geval je dit vergeten bent."));
    
    Wt::WTable * table = new Wt::WTable();
    pw->addWidget(table);

    table->elementAt(0,0)->addWidget(new Wt::WText("Email: "));
   
    saveMail = new Wt::WPushButton("Opslaan");
    saveMail->setWidth(150);
    saveMail->setHeight(50);
    saveMail->setStyleClass("btn btn-primary");
    saveMail->clicked().connect(this, &changePassword::mailChanged);
    table->elementAt(0,2)->addWidget(saveMail);
    
    email = new Wt::WLineEdit();
    email->setWidth(300);
    email->setHeight(50);
    email->setStyleClass("form-control");
    email->setText(app->getAccountMail().wt());
    table->elementAt(0,1)->addWidget(email);

    feedbackMail = new Wt::WText(" ");
    feedbackMail->setStyleClass("alert");
    feedbackMail->setHeight(50);
    table->elementAt(0,3)->addWidget(feedbackMail);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i,j)->setPadding(5);
        table->elementAt(i,j)->setVerticalAlignment(Wt::AlignmentFlag::AlignMiddle);
      }
    }

    table->setStyleClass("panel-body");
  }
}

void changePassword::passwordChanged() {
  Wt::WString sCurPW = curPW->text();
  Wt::WString sNewPW1 = newPW1->text();
  Wt::WString sNewPW2 = newPW2->text();
  
  curPW->setStyleClass("form-control");
  newPW1->setStyleClass("form-control");
  newPW2->setStyleClass("form-control");
  feedback1->setStyleClass("alert");
  feedback1->setText("");
  feedback2->setStyleClass("alert");
  feedback2->setText("");
  feedback3->setStyleClass("alert");
  feedback3->setText("");
  feedback4->setStyleClass("alert");
  feedback4->setText("");
  
  if (!server->auth(account->dn(), PASSWORD(sCurPW))) {
    curPW->setStyleClass("form-control invalid");
    curPW->setText("");
    curPW->setFocus();
    feedback1->setText("Je wachtwoord is niet juist.");
    feedback1->setStyleClass("alert alert-danger");    
    return;
  }
  
  if(sNewPW1.empty()) {
    newPW1->setStyleClass("form-control invalid");
    feedback2->setText("Vul een nieuw wachtwoord in.");
    feedback2->setStyleClass("alert alert-danger"); 
    newPW1->setFocus();
    return;
  }
  
  if(sNewPW1.toUTF8().size() < 8) {
    newPW1->setStyleClass("form-control invalid");
    feedback2->setText("Minstens 8 tekens, graag.");
    feedback2->setStyleClass("alert alert-danger"); 
    newPW1->setFocus();
    return;
  }
  
  if(!y::utils::Security().isGoodPassword(sNewPW1)) {
    newPW1->setStyleClass("form-control invalid");
    feedback2->setText("Dit wachtwoord voldoet niet aan de voorwaarden.");
    feedback2->setStyleClass("alert alert-danger"); 
    newPW1->setFocus();
    return;
  }
  
  if(sNewPW1 != sNewPW2) {
    newPW2->setStyleClass("form-control invalid");
    feedback3->setText("Vul twee maal hetzelfde wachtwoord in.");
    feedback3->setStyleClass("alert alert-danger"); 
    newPW2->setFocus();
    return;
  }
  
  // if we get here, change the user's password
  account->password(PASSWORD(sNewPW1));
  server->commitChanges();
  feedback4->setText("Je wachtwoord is gewijzigd.");
  feedback4->setStyleClass("alert alert-success"); 
  curPW->setText("");
  newPW1->setText("");
  newPW2->setText("");
}

void changePassword::mailChanged() {
  Wt::WRegExpValidator mailValidator(".+\\@.+\\..+");
  if (mailValidator.validate(email->text()).state() == Wt::WValidator::Valid) {
    email->setStyleClass("form-control succes");
    feedbackMail->setText("Je adres is opgeslagen.");
    feedbackMail->setStyleClass("alert alert-success");
    app->setAccountMail(string(email->text()));
  } else {
    email->setStyleClass("form-control invalid");
    feedbackMail->setText("Je adres is niet correct.");
    feedbackMail->setStyleClass("alert alert-danger");
  }
}


