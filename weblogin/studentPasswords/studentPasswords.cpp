/* 
 * File:   studentPasswords.cpp
 * Author: yvan
 * 
 * Created on July 15, 2015, 4:28 PM
 */

#include "studentPasswords.h"
#include <Wt/WPanel>
#include <Wt/WContainerWidget>
#include <Wt/WPopupMenu>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WCheckBox>
#include <Wt/WHBoxLayout>
#include "utils/string.h"
#include "ldap/account.h"
#include "utils/security.h"
#include "smartschool/smartschool.h"



void studentPasswords::create() {
  Wt::WPanel * panel = new Wt::WPanel(this);
  
  panel->setStyleClass("panel panel-primary");
  panel->setTitle("<h3>Wachtwoorden Administratie</h3>");
  panel->setMinimumSize(800, 800);
  panel->setMaximumSize(800, Wt::WLength::Auto);
  panel->setMargin("0 auto");
  
  Wt::WContainerWidget * content = new Wt::WContainerWidget();
  panel->setCentralWidget(content);
  content->setPadding("1%");
  
  buttons = new Wt::WContainerWidget(content);
  Wt::WHBoxLayout * buttonLayout = new Wt::WHBoxLayout();
  buttons->setLayout(buttonLayout);
  
  Wt::WPopupMenu * popup = new Wt::WPopupMenu();
  Wt::WPushButton * button = new Wt::WPushButton();
  button->setMenu(popup);
  button->setText("Selecteer een klas");
  buttonLayout->addWidget(button);
  
  Wt::WPushButton * button2 = new Wt::WPushButton();
  button2->setText("Selectie Aanpassen");
  button2->setStyleClass("btn btn-success");
  buttonLayout->addWidget(button2);
  button2->clicked().connect(this, &studentPasswords::changePasswords);
  
  Wt::WContainerWidget * tableContent = new Wt::WContainerWidget(content);
  table = new Wt::WTable(tableContent);
  
  // add classes
  Wt::WPopupMenu * subMenu[7];
  
  for(int i = 0; i < 7; i++) {
    subMenu[i] = new Wt::WPopupMenu();
    if(i == 0) {
      popup->addMenu("1ste jaar", subMenu[i]);
    } else {
      string s = string(i+1) + "de jaar";
      popup->addMenu(s.wt(), subMenu[i]);
    }
  }
  
  CLASSES & classes = server->getClasses();
  
  for(int i = 0; i < classes.elms(); i++) {
    string name = classes[i].cn().get();
    if(name.empty()) continue;
    
    int year = -1;
    switch(name[0]) {
      case '1': year = 0; break;
      case '2': year = 1; break;
      case '3': year = 2; break;
      case '4': year = 3; break;
      case '5': year = 4; break;
      case '6': year = 5; break;
      case '7': year = 6; break;
    }
    if(year < 0) continue;
    
    subMenu[year]->addItem(name.wt())->triggered().connect(std::bind([=] () {
      showClass(name);
    }));
  }
  
  progress = new Wt::WProgressBar(content);
  progress->hide();
  
  anchor = new Wt::WAnchor(Wt::WLink(&pfile), "Download passwords", content);
  anchor->setTarget(Wt::TargetNewWindow);
  anchor->clicked().connect(this, &studentPasswords::reset);
  anchor->hide();
}

void studentPasswords::showClass(string schoolClass) {
  currentClass = schoolClass;
  
  table->clear();
  table->elementAt(0,0)->addWidget(new Wt::WText("Naam"));
  table->elementAt(0,1)->addWidget(new Wt::WText("HoofdAccount"));
  table->elementAt(0,2)->addWidget(new Wt::WText("CoAccount 1"));
  table->elementAt(0,3)->addWidget(new Wt::WText("CoAccount 2"));
  table->elementAt(1,0)->addWidget(new Wt::WText("Select all"));
  
  Wt::WCheckBox * checkMain = new Wt::WCheckBox();
  table->elementAt(1,1)->addWidget(checkMain);
  checkMain->clicked().connect(std::bind([=] () {
    for(int i = 2; i < table->rowCount(); i++) {
      ((Wt::WCheckBox*)(table->elementAt(i, 1)->widget(0)))->setChecked(checkMain->isChecked());
    }
  }));
  
  Wt::WCheckBox * checkCo1 = new Wt::WCheckBox();
  table->elementAt(1,2)->addWidget(checkCo1);
  checkCo1->clicked().connect(std::bind([=] () {
    for(int i = 2; i < table->rowCount(); i++) {
      ((Wt::WCheckBox*)(table->elementAt(i, 2)->widget(0)))->setChecked(checkCo1->isChecked());
    }
  }));
  
  Wt::WCheckBox * checkCo2 = new Wt::WCheckBox();
  table->elementAt(1,3)->addWidget(checkCo2);
  checkCo2->clicked().connect(std::bind([=] () {
    for(int i = 2; i < table->rowCount(); i++) {
      ((Wt::WCheckBox*)(table->elementAt(i, 3)->widget(0)))->setChecked(checkCo2->isChecked());
    }
  }));
  
  table->setHeaderCount(2, Wt::Orientation::Horizontal);
  
  y::ldap::schoolClass & sc = server->getClass(CN(schoolClass));
  for(int i = 0; i < sc.students().elms(); i++) {
    y::ldap::account & student = server->getAccount(DN(sc.students()[i]));
    table->elementAt(2+i,0)->addWidget(new Wt::WText(student.fullName().get().wt()));
    table->elementAt(2+i,1)->addWidget(new Wt::WCheckBox());
    table->elementAt(2+i,2)->addWidget(new Wt::WCheckBox());
    table->elementAt(2+i,3)->addWidget(new Wt::WCheckBox());
  }
  
  for(int i = 0; i < table->rowCount(); i++) {
    for(int j = 0; j < table->columnCount(); j++) {
      table->elementAt(i, j)->setPadding(5);
      table->elementAt(i, j)->setVerticalAlignment(Wt::AlignMiddle);
    }
  }
}

void studentPasswords::changePasswords() {
  buttons->hide();
  table->hide();
 
  
  
  pfile.clear(string("wachtwoorden ") + currentClass);
  
  y::ldap::schoolClass & sc = server->getClass(CN(currentClass));
  
  progress->setRange(0, sc.students().elms());
  progress->show();
  
  for(int i = 0; i < sc.students().elms(); i++) {
    y::ldap::account & a = server->getAccount(DN(sc.students()[i]));
    
    // check main account
    if(((Wt::WCheckBox*)(table->elementAt(i+2, 1)->widget(0)))->isChecked()) {
      pfile.addLine(a.fullName().get());
      {
        string s("Klas: ");
        s += a.schoolClass().get();
        pfile.addLine(s);
      }
      {
        string s("Login: ");
        s += a.uid().get();
        pfile.addLine(s);
      }
      {
        string s("Nieuw wachtwoord: ");
        s += a.getPasswordText();
        pfile.addLine(s);
      }
      pfile.addLine(" ");
      pfile.addLine("Laat je wachtwoord niet rondslingeren! Je bent verantwoordelijk voor je account. Indien je dit wachtwoord niet kan onthouden, pas dan je wachtwoord zelf aan via http://apps.sanctamaria-aarschot.be");
      pfile.addLine(" ");
    }
    
    // check co-account 1
    if(((Wt::WCheckBox*)(table->elementAt(i+2, 2)->widget(0)))->isChecked()) {
      {
        string s("Wachtwoord voor ");
        s += a.fullName().get();
        pfile.addLine(s);
      }
      
      {
        string s(a.street().get());
        s += " ";
        s += string(a.houseNumber().get());
        s += " ";
        s += a.houseNumberAdd().get();
        pfile.addLine(s);
      }
      
      {
        string s(a.postalCode().get());
        s += " ";
        s += string(a.city().get());
        pfile.addLine(s);
      }
      
      {
        string s("Klas: ");
        s += a.schoolClass().get();
        pfile.addLine(s);
      }
      {
        string s("Login: ");
        s += a.uid().get();
        pfile.addLine(s);
      }
      {
        string password = y::utils::Security().makePassword(8);
        string s("Wachtwoord 1ste Co-account: ");
        s += password;
        y::Smartschool().setCoAccount(a, password, true);
        pfile.addLine(s);
      }
      pfile.addLine(" ");
      pfile.addLine("Met dit wachtwoord kan je als ouder inloggen op http://sanctamaria-aarschot.smartschool.be");
      pfile.addLine(" ");
    }
    
    // check co-account 2
    if(((Wt::WCheckBox*)(table->elementAt(i+2, 3)->widget(0)))->isChecked()) {
      {
        string s("Wachtwoord voor ");
        s += a.fullName().get();
        pfile.addLine(s);
      }
      
      {
        string s(a.street().get());
        s += " ";
        s += string(a.houseNumber().get());
        s += " ";
        s += a.houseNumberAdd().get();
        pfile.addLine(s);
      }
      
      {
        string s(a.postalCode().get());
        s += " ";
        s += string(a.city().get());
        pfile.addLine(s);
      }
      
      {
        string s("Klas: ");
        s += a.schoolClass().get();
        pfile.addLine(s);
      }
      {
        string s("Login: ");
        s += a.uid().get();
        pfile.addLine(s);
      }
      {
        string password = y::utils::Security().makePassword(8);
        string s("Wachtwoord 2de Co-account: ");
        s += password;
        y::Smartschool().setCoAccount(a, password, true);
        pfile.addLine(s);
      }
      pfile.addLine(" ");
      pfile.addLine("Met dit wachtwoord kan je als ouder inloggen op http://sanctamaria-aarschot.smartschool.be");
      pfile.addLine(" ");
    }
    
    progress->setValue(i);
  }
  
  progress->hide();
  
  
  anchor->show();
}

void studentPasswords::reset() {
  buttons->show();
  table->clear();
  table->show();
  anchor->hide();
}