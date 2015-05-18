/* 
 * File:   accountManager.cpp
 * Author: yvan
 * 
 * Created on February 14, 2015, 5:28 PM
 */

#include <Wt/WContainerWidget>
#include <Wt/WPanel>
#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>

#include "accountManager.h"
#include <admintools.h>


Wt::WWidget * accountManager::get(y::ldap::account * account) {
  this->account = account;
  
  Wt::WTable * table = new Wt::WTable();
  
  table->elementAt(0,0)->addWidget(new Wt::WText("Voornaam: "));
  table->elementAt(1,0)->addWidget(new Wt::WText("Familienaam: "));
  table->elementAt(2,0)->addWidget(new Wt::WText("Mail: "));
  table->elementAt(3,0)->addWidget(new Wt::WText("Groep: "));
  table->elementAt(4,0)->addWidget(new Wt::WText("Geboortedatum: "));
  table->elementAt(5,0)->addWidget(new Wt::WText("Huidig wachtwoord: "));
  table->elementAt(6,0)->addWidget(new Wt::WText("Nieuw wachtwoord: "));
  table->elementAt(7,0)->addWidget(new Wt::WText("Herhaal nieuw wachtwoord: "));
  
  firstName = new Wt::WLineEdit();
  firstName->setWidth(400);
  firstName->setHeight(35);
  firstName->disable();
  firstName->setText(account->cn().wt());
  
  lastName = new Wt::WLineEdit();
  lastName->setWidth(400);
  lastName->setHeight(35);
  lastName->disable();
  lastName->setText(account->sn().wt());
  
  mail = new Wt::WLineEdit();
  mail->setWidth(400);
  mail->setHeight(35);
  mail->disable();
  mail->setText(account->mail()().wt());
  
  group = new Wt::WLineEdit();
  group->setWidth(400);
  group->setHeight(35);
  group->disable();
  group->setText(account->group()().wt());
  
  birthday = new Wt::WLineEdit();
  birthday->setWidth(400);
  birthday->setHeight(35);
  birthday->disable();
  birthday->setText(account->birthDay().asString().wt());
  
  currentPassword = new Wt::WLineEdit();
  currentPassword->setWidth(150);
  currentPassword->setHeight(35);
  currentPassword->setStyleClass("form-control");
  currentPassword->setEchoMode(Wt::WLineEdit::Password);
  
  
  newPassword1 = new Wt::WLineEdit();
  newPassword1->setWidth(150);
  newPassword1->setHeight(35);
  newPassword1->setEchoMode(Wt::WLineEdit::Password);
  
  newPassword2 = new Wt::WLineEdit();
  newPassword2->setWidth(150);
  newPassword2->setHeight(35);
  newPassword2->setEchoMode(Wt::WLineEdit::Password);

  saveButton = new Wt::WPushButton("Save");
  saveButton->setWidth(150);

  saveButton->clicked().connect(this, &accountManager::saveButtonClicked);
  saveButton->setStyleClass("btn btn-primary");
  
  feedback = new Wt::WText(" ");
  feedback->setStyleClass("alert");

  
  Wt::WContainerWidget * CPWC = new Wt::WContainerWidget();
  Wt::WHBoxLayout * CPW = new Wt::WHBoxLayout(CPWC);
  CPW->setContentsMargins(0,0,0,0);
  CPW->addWidget(newPassword2);
  CPW->addWidget(saveButton);
  CPW->addWidget(new Wt::WText(), 1);
  
  Wt::WText * aboutPassword = new Wt::WText();
  aboutPassword->setTextFormat(Wt::XHTMLText);
  aboutPassword->setText("Een wachtwoord moet 8 tot 20 characters lang zijn. Er moet minstens een hoofdletter, een kleine letter en een cijfer in voorkomen.");
  //aboutPassword->setStyleClass("jumbotron");
  
  table->elementAt(0,1)->addWidget(firstName);
  table->elementAt(1,1)->addWidget(lastName);
  table->elementAt(2,1)->addWidget(mail);
  table->elementAt(3,1)->addWidget(group);
  table->elementAt(4,1)->addWidget(birthday);
  table->elementAt(5,1)->addWidget(currentPassword);
  table->elementAt(6,1)->addWidget(newPassword1);
  table->elementAt(7,1)->addWidget(CPWC);
  table->elementAt(8,1)->addWidget(feedback);
  table->elementAt(9,1)->addWidget(aboutPassword);
  
  for(int i = 0; i < table->rowCount(); i++) {
    for(int j = 0; j < table->columnCount(); j++) {
      table->elementAt(i,j)->setPadding(5);
      table->elementAt(i,j)->setVerticalAlignment(Wt::AlignmentFlag::AlignMiddle);
    }
  }
  
  table->elementAt(8,0)->setPadding(20);
  table->elementAt(8,1)->setPadding(20);
  
  table->setStyleClass("panel-body");
  
  Wt::WContainerWidget * result = new Wt::WContainerWidget();
  Wt::WPanel * panel = new Wt::WPanel(result);
  panel->setStyleClass("panel panel-primary");
  panel->setTitle("<h3>Mijn Account</h3>");
  panel->setCentralWidget(table);
  panel->setMaximumSize(800, Wt::WLength::Auto);
  
  return result;
}

void accountManager::saveButtonClicked() {
  Wt::WString currentPW = currentPassword->text();
  Wt::WString newPW1 = newPassword1->text();
  Wt::WString newPW2 = newPassword2->text();
  
  currentPassword->setStyleClass("form-control");
  newPassword1->setStyleClass("form-control");
  newPassword2->setStyleClass("form-control");
  feedback->setStyleClass("alert");
  feedback->setText("");
  
  if (!y::ldap::Server().auth(account->dn(), y::ldap::PASSWORD(currentPW))) {
    currentPassword->setStyleClass("form-control invalid");
    currentPassword->setText("");
    currentPassword->setFocus();
    feedback->setText("Je wachtwoord is niet juist.");
    feedback->setStyleClass("alert alert-danger");    
    return;
  }
  
  if(newPW1.empty()) {
    newPassword1->setStyleClass("form-control invalid");
    feedback->setText("Vul een nieuw wachtwoord in.");
    feedback->setStyleClass("alert alert-danger"); 
    newPassword1->setFocus();
    return;
  }
  
  if(newPW1.toUTF8().size() < 8) {
    newPassword1->setStyleClass("form-control invalid");
    feedback->setText("Minstens 8 tekens, graag.");
    feedback->setStyleClass("alert alert-danger"); 
    newPassword1->setFocus();
    return;
  }
  
  if(!y::utils::Security().isGoodPassword(newPW1)) {
    newPassword1->setStyleClass("form-control invalid");
    feedback->setText("Dit wachtwoord voldoet niet aan de voorwaarden.");
    feedback->setStyleClass("alert alert-danger"); 
    newPassword1->setFocus();
  }
  
  if(newPW1 != newPW2) {
    newPassword2->setStyleClass("form-control invalid");
    feedback->setText("Vul twee maal hetzelfde wachtwoord in.");
    feedback->setStyleClass("alert alert-danger"); 
    newPassword2->setFocus();
    return;
  }

  // if we get here, change the user's password
  account->password(y::ldap::PASSWORD(newPW1));
  y::ldap::Server().commitChanges();
  feedback->setText("Je wachtwoord is gewijzigd.");
  feedback->setStyleClass("alert alert-success"); 
  currentPassword->setText("");
  newPassword1->setText("");
  newPassword2->setText("");
}