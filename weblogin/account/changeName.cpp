/* 
 * File:   changeName.cpp
 * Author: yvan
 * 
 * Created on June 16, 2015, 12:06 PM
 */

#include "changeName.h"
#include "../application.h"
#include "admintools.h"
#include <Wt/WPanel>
#include <Wt/WTable>
#include <Wt/WMessageBox>

void changeName::create(y::ldap::account * account) {
  this->account = account;
  
  Wt::WPanel * panel = new Wt::WPanel(this);
  panel->setStyleClass("panel panel-primary");
  panel->setTitle("<h3>Account Details</h3>");
  panel->setMaximumSize(800, Wt::WLength::Auto);
  panel->setMargin("0 auto");
  
  Wt::WContainerWidget * content = new Wt::WContainerWidget();
  panel->setCentralWidget(content);
  content->setPadding("1%");
  
  {
    Wt::WContainerWidget * c = new Wt::WContainerWidget(content);
    c->addStyleClass("well");
    c->setPadding("1%");
    c->addWidget(new Wt::WText("<h4>Je naam aanpassen?</h4>"));
    
    c->addWidget(new Wt::WText("De administratie werkt steeds met je "
            "echte naam. Als je wil dat de applicaties op school (gmail, "
            "smartschool, ...) een andere naam gebruiken, dan kan je "
            "dat hier instellen. Let op: je wijzigt dan ook je mail alias."));
    
    Wt::WTable * table = new Wt::WTable();
    c->addWidget(table);
    
    table->elementAt(0,0)->addWidget(new Wt::WText("Voornaam: "));
    table->elementAt(1,0)->addWidget(new Wt::WText("Naam:"     ));
    
    firstName = new Wt::WLineEdit();
    firstName->resize(200, 35);
    firstName->setStyleClass("form-control");
    firstName->setText(account->cn().get().wt());
    table->elementAt(0,1)->addWidget(firstName);
    
    lastName = new Wt::WLineEdit();
    lastName->resize(200, 35);
    lastName->setStyleClass("form-control");
    lastName->setText(account->sn().get().wt());
    table->elementAt(1,1)->addWidget(lastName);
    
    saveButton = new Wt::WPushButton("wijzigen");
    saveButton->resize(200, 35);
    saveButton->setStyleClass("btn btn-primary");
    saveButton->clicked().connect(this, &changeName::nameChanged);
    table->elementAt(2,1)->addWidget(saveButton);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i,j)->setPadding(5);
        table->elementAt(i,j)->setVerticalAlignment(Wt::AlignmentFlag::AlignMiddle);
      }
    }

    table->setStyleClass("panel-body");
  }
}

void changeName::nameChanged() {
  string cn = firstName->text();
  string sn = lastName->text();
  cn.trim(); sn.trim();
  
  string fullname(cn);
  fullname += " ";
  fullname += sn;
  
  account->cn(CN(cn));
  account->sn(SN(sn));
  account->fullName(FULL_NAME(fullname));
  account->mail(MAIL("temp@localhost"));
  server->commitChanges();
  account->mail(MAIL(server->createMail(CN(cn),SN(sn))));
  server->commitChanges();
  
  Wt::WMessageBox * message = new Wt::WMessageBox(
          "Info",
          "<p>Je naam werd aangepast</p>",
          Wt::Information,
          Wt::Ok
          );
  
  message->setModal(true);
  message->setWidth(300);
  message->buttonClicked().connect(std::bind([=] () {
    delete message;
  }));
  
  message->show();
  
}