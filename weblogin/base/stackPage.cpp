/* 
 * File:   stackPage.cpp
 * Author: yvan
 * 
 * Created on February 17, 2015, 11:06 AM
 */

#include <Wt/WContainerWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>

#include "stackPage.h"
#include "stackPageManager.h"

void stackPage::create(stackPageManager * parent) {
  this->parent = parent;

  Wt::WVBoxLayout * box = new Wt::WVBoxLayout();
  setLayout(box);
  setContent(box);
  
  // navigation buttons
  Wt::WHBoxLayout * navBox = new Wt::WHBoxLayout();
  
  
  previousButton = new Wt::WPushButton("vorige");
  previousButton->setWidth(150);
  previousButton->setHeight(35);
  previousButton->clicked().connect(this, &stackPage::previousClicked);
  previousButton->setStyleClass("btn btn-primary");
  navBox->addWidget(previousButton);
  
  nextButton = new Wt::WPushButton("volgende");
  nextButton->setWidth(150);
  nextButton->setHeight(35);
  nextButton->clicked().connect(this, &stackPage::nextClicked);
  nextButton->setDefault(true);
  nextButton->setStyleClass("btn btn-primary");
  navBox->addWidget(nextButton);
  
  box->addWidget(new Wt::WText("<p></p>"));
  box->addLayout(navBox);
  
}

void stackPage::showButtons(bool previous, bool next) {
  if (previous) {
    previousButton->show();
  } else {
    previousButton->hide();
  }
  if(next) {
    nextButton->show();
  } else { 
    nextButton->hide();
  }
}

void stackPage::previousClicked() {
  if (onPrevious()) parent->showPage(pageIndex-1);
}

void stackPage::nextClicked() {
  if(onNext()) parent->showPage(pageIndex+1);
}



