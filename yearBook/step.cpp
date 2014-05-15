/* 
 * File:   step.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 2:36 PM
 */

#include "step.h"

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

step::step() : createDone(false), showPrevious(false), showNext(false), showSave(false) {}

void step::create(yearBook * parent) {
  if(createDone) return;
  
  this->parent = parent;
  mainPanel = new Wt::WPanel(parent->root());
  
  mainPanel->setTitleBar(true);
  mainPanel->setTitle("<h1>Jaarboek App</h1>");
  mainPanel->setStyleClass("panel panel-primary");
  mainPanel->titleBarWidget()->addStyleClass("panel-heading");
  
  
  mainPanel->setMinimumSize(400, 400);
  mainPanel->setMaximumSize(700, 700);
  mainContent = new Wt::WContainerWidget();
  
  Wt::WVBoxLayout * box = new Wt::WVBoxLayout();
  mainContent->setLayout(box);
  
  setContent(box);
  
  Wt::WHBoxLayout * buttonBox = new Wt::WHBoxLayout();
  
  logOutButton = new Wt::WPushButton("uitloggen");
  logOutButton->setWidth(150);
  logOutButton->setHeight(35);
  logOutButton->clicked().connect(this, &step::logoutClicked);
  logOutButton->setStyleClass("btn btn-danger");
  buttonBox->addWidget(logOutButton);
  
  if(showPrevious) {
    previousButton = new Wt::WPushButton("vorige");
    previousButton->setWidth(150);
    previousButton->setHeight(35);
    previousButton->clicked().connect(this, &step::previousClicked);
    previousButton->setStyleClass("btn btn-primary");
    buttonBox->addWidget(previousButton);
  }
  
  if(showNext) {
    nextButton = new Wt::WPushButton("volgende");
    nextButton->setWidth(150);
    nextButton->setHeight(35);
    nextButton->clicked().connect(this, &step::nextClicked);
    nextButton->setStyleClass("btn btn-primary");
    nextButton->setDefault(true);
    buttonBox->addWidget(nextButton);
  }
  
  if(showSave) {
    saveButton = new Wt::WPushButton("opslaan");
    saveButton->setWidth(150);
    saveButton->setHeight(35);
    saveButton->clicked().connect(this, &step::saveClicked);
    saveButton->setStyleClass("btn btn-success");
    saveButton->setDefault(true);
    buttonBox->addWidget(saveButton);
  }
  
  box->addWidget(new Wt::WText("<p></p>"));
  box->addLayout(buttonBox);
  
  mainPanel->setCentralWidget(mainContent);
  mainPanel->hide();
  mainContent->addStyleClass("panel-body");
  createDone = true;
}

void step::hide() {
  mainPanel->hide();
}

void step::show() {
  onShow();
  mainPanel->show();
}

bool step::visible() {
  return mainPanel->isVisible();
}

void step::logoutClicked() {
  parent->setAction(A_LOGOUT);
}

void step::previousClicked() {
  parent->setAction(A_PREVIOUS);
}

void step::nextClicked() {
  parent->setAction(A_NEXT);
}

void step::saveClicked() {
  parent->setAction(A_SAVE);
}

void step::showPreviousButton(bool value) {
  showPrevious = value;
}

void step::showNextButton(bool value) {
  showNext = value;
}

void step::showSaveButton(bool value) {
  showSave = value;
}