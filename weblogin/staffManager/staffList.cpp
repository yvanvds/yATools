/* 
 * File:   staffList.cpp
 * Author: yvan
 * 
 * Created on June 16, 2015, 5:57 PM
 */

#include <Wt/WTable>
#include <Wt/WLineEdit>
#include <Wt/WCheckBox>
#include <Wt/WMessageBox>

#include "admintools.h"
#include "staffList.h"

staffList::staffList(y::ldap::server * server, y::data::adminRights * rights) 
  : server(server)
  , rights(rights) 
{
  setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  setOverflow(Wt::WContainerWidget::OverflowScroll, Wt::Orientation::Vertical);
  setHeight(600);
  
  table = new Wt::WTable();
  addWidget(table);
  loadTableContent();
  createDialog();
}

void staffList::createDialog() {
  dialog = new Wt::WDialog(this);
  //dialog->resize(450, 400);
  dialogContainer = new Wt::WContainerWidget(dialog->contents());
  Wt::WContainerWidget * personInfo = new Wt::WContainerWidget();
  personInfo->setStyleClass("well");
  dialogContainer->addWidget(personInfo);
  
  infoTable = new Wt::WTable();
  infoTable->columnAt(0)->setWidth(200);
  infoTable->columnAt(1)->setWidth(200);
  personInfo->addWidget(infoTable);
  
  infoTable->elementAt(0,0)->addWidget(new Wt::WText("Wisa Naam"));
  wisaName = new Wt::WLineEdit();
  wisaName->setWidth(190);
  infoTable->elementAt(0,1)->addWidget(wisaName);
  
  infoTable->elementAt(1,0)->addWidget(new Wt::WText("Groep"));
  group = new Wt::WComboBox();
  group->setWidth(190);
  infoTable->elementAt(1,1)->addWidget(group);
  group->addItem("Leraar");
  group->addItem("Directie");
  group->addItem("Ondersteuning");
  group->addItem("Admin");
  
  for(int i = 0; i < infoTable->rowCount(); i++) {
    for(int j = 0; j < infoTable->columnCount(); j++) {
      infoTable->elementAt(i, j)->setPadding(5);
      infoTable->elementAt(i, j)->setVerticalAlignment(Wt::AlignMiddle);
    }
  }
  
  Wt::WContainerWidget * adminRights = new Wt::WContainerWidget();
  adminRights->setStyleClass("well");
  dialogContainer->addWidget(adminRights);
  adminRights->addWidget(new Wt::WText("<b>Administratieve rechten</b>"));
  adminTable = new Wt::WTable();
  adminTable->columnAt(0)->setWidth(200);
  adminTable->columnAt(1)->setWidth(100);
  adminRights->addWidget(adminTable);
  
  adminTable->elementAt(0,0)->addWidget(new Wt::WText("Personeel"));
  adminTable->elementAt(1,0)->addWidget(new Wt::WText("Wachtwoorden"));
  adminTable->elementAt(2,0)->addWidget(new Wt::WText("Wisa"));
  adminTable->elementAt(3,0)->addWidget(new Wt::WText("Jaarboek"));
  personeel = new Wt::WCheckBox();
  adminTable->elementAt(0,1)->addWidget(personeel);
  passwords = new Wt::WCheckBox();
  adminTable->elementAt(1,1)->addWidget(passwords);
  wisa = new Wt::WCheckBox();
  adminTable->elementAt(2,1)->addWidget(wisa);
  yearbook = new Wt::WCheckBox();
  adminTable->elementAt(3,1)->addWidget(yearbook);
  
  for(int i = 0; i < adminTable->rowCount(); i++) {
    for(int j = 0; j < adminTable->columnCount(); j++) {
      adminTable->elementAt(i, j)->setPadding(5);
      adminTable->elementAt(i, j)->setVerticalAlignment(Wt::AlignMiddle);
    }
  }
  
  Wt::WPushButton * ok = new Wt::WPushButton("Save", dialog->footer());
  ok->setDefault(true);
  ok->setStyleClass("btn btn-primary");
  ok->clicked().connect(dialog, &Wt::WDialog::accept);
  
  Wt::WPushButton * cancel = new Wt::WPushButton("Cancel", dialog->footer());
  cancel->clicked().connect(dialog, &Wt::WDialog::reject);
  
  dialog->finished().connect(std::bind([=] () {
    if(dialog->result() == Wt::WDialog::Accepted) {
      saveEdit();
    }
  }));
  
  dialog->rejectWhenEscapePressed(true);
  dialog->hide();
}

void staffList::loadTableContent() {
  ACCOUNTS & accounts = server->getAccounts();
  table->clear();
  
  table->setHeaderCount(1);
  table->elementAt(0,0)->addWidget(new Wt::WText("naam"));
  table->elementAt(0,1)->addWidget(new Wt::WText("gebruikersnaam"));
  table->elementAt(0,2)->addWidget(new Wt::WText("wisa Naam"));
  table->columnAt(0)->setWidth(200);
  table->columnAt(1)->setWidth(100);
  table->columnAt(2)->setWidth(100);
  table->columnAt(3)->setWidth(100);
  table->columnAt(4)->setWidth(100);
  
  int entry = 1;
  
  for (int i = 0; i < accounts.elms(); i++) {
    if(accounts[i].isStaff()) {
      table->elementAt(entry, 0)->addWidget(new Wt::WText(accounts[i].fullName()().wt()));
      table->elementAt(entry, 1)->addWidget(new Wt::WText(accounts[i].uid()().wt()));
      table->elementAt(entry, 2)->addWidget(new Wt::WText(accounts[i].wisaName().wt()));
      
      Wt::WPushButton * view = new Wt::WPushButton("edit");
      view->setWidth(90);
      view->clicked().connect(boost::bind(&staffList::openDialog, this, i));
      view->setStyleClass("btn btn-success");
      table->elementAt(entry, 3)->addWidget(view);
      
      Wt::WPushButton * remove = new Wt::WPushButton("X");
      remove->setWidth(35);
      remove->clicked().connect(boost::bind(&staffList::deleteUser, this, i));
      remove->setStyleClass("btn btn-danger");
      table->elementAt(entry, 4)->addWidget(remove);
      entry++;
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

void staffList::loadDialogContent() {
  
}

void staffList::openDialog(int withEntry) {
  ACCOUNTS & accounts = server->getAccounts();
  dialog->setWindowTitle(accounts[withEntry].fullName()().wt());
  wisaName->setText(accounts[withEntry].wisaName().wt());  
  TODO(Make an enum out of this)
  if(accounts[withEntry].group()() == "teacher") {
    group->setCurrentIndex(0);
  } else if(accounts[withEntry].group()() == "director") {
    group->setCurrentIndex(1);
  } else if(accounts[withEntry].group()() == "support") {
    group->setCurrentIndex(2);
  } else if(accounts[withEntry].group()() == "admin") {
    group->setCurrentIndex(3);
  } else {
    group->setCurrentIndex(-1);
  }
  
  if(rights->has(accounts[withEntry].uid()(), y::data::ADMIN_STAFF)) {
    personeel->setChecked(true);
  } else {
    personeel->setChecked(false);
  }
  
  if(rights->has(accounts[withEntry].uid()(), y::data::ADMIN_WISA)) {
    wisa->setChecked(true);
  } else {
    wisa->setChecked(false);
  }
  
  if(rights->has(accounts[withEntry].uid()(), y::data::ADMIN_YEARBOOK)) {
    yearbook->setChecked(true);
  } else {
    yearbook->setChecked(false);
  }
  
  if(rights->has(accounts[withEntry].uid()(), y::data::ADMIN_PASSWORD)) {
    passwords->setChecked(true);
  } else {
    passwords->setChecked(false);
  }
  currentEntry = withEntry;
  dialog->show();
}

void staffList::deleteUser(int entry) {
  ACCOUNTS & accounts = server->getAccounts();
  string s("Wil je ");
  s += accounts[entry].fullName()();
  s += " verwijderen?";
  Wt::WMessageBox * message = new Wt::WMessageBox(
          "Let op!",
          s.c_str(),
          Wt::Warning,
          Wt::Yes | Wt::No
          );
  message->setModal(true);
  message->setWidth(400);
  message->buttonClicked().connect(std::bind([=] () {
    if(message->buttonResult() == Wt::Yes) {
      ACCOUNTS & accounts = server->getAccounts();
      accounts[entry].flagForRemoval();
      server->commitChanges();
      loadTableContent();
    }  
    delete message;
  }));
  message->show();
}


void staffList::saveEdit() {
  ACCOUNTS & accounts = server->getAccounts();
  
  TODO(This is not very efficient: database is rewritten four times!)
  if(passwords->isChecked()) {
    rights->add(accounts[currentEntry].uid()(), y::data::ADMIN_PASSWORD);
  } else {
    rights->remove(accounts[currentEntry].uid()(), y::data::ADMIN_PASSWORD);
  }
  
  if(personeel->isChecked()) {
    rights->add(accounts[currentEntry].uid()(), y::data::ADMIN_STAFF);
  } else {
    rights->remove(accounts[currentEntry].uid()(), y::data::ADMIN_STAFF);
  }
  
  if(wisa->isChecked()) {
    rights->add(accounts[currentEntry].uid()(), y::data::ADMIN_WISA);
  } else {
    rights->remove(accounts[currentEntry].uid()(), y::data::ADMIN_WISA);
  }
  
  if(yearbook->isChecked()) {
    rights->add(accounts[currentEntry].uid()(), y::data::ADMIN_YEARBOOK);
  } else {
    rights->remove(accounts[currentEntry].uid()(), y::data::ADMIN_YEARBOOK);
  }
  
  switch(group->currentIndex()) {
    case 0: accounts[currentEntry].group(y::ldap::GID("teacher")); break;
    case 1: accounts[currentEntry].group(y::ldap::GID("director")); break;
    case 2: accounts[currentEntry].group(y::ldap::GID("support")); break;
    case 3: accounts[currentEntry].group(y::ldap::GID("admin")); break;
  }
  
  accounts[currentEntry].wisaName(string(wisaName->text()));
  
  server->commitChanges();
  
  loadTableContent();
}