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

y::gui::stackPage::stackPage() : createDone(false) {
  
}

void y::gui::stackPage::create(int index, stackPageManager * parent) {
  if(createDone) return;
  this->pageIndex = index;
  this->parent = parent;
  
  Wt::WContainerWidget * content = new Wt::WContainerWidget(parent);
  Wt::WVBoxLayout * box = new Wt::WVBoxLayout();
  content->setLayout(box);
  
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

void y::gui::stackPage::showButtons(bool previous, bool next) {
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

void y::gui::stackPage::previousClicked() {
  parent->showPage(pageIndex-1);
}

void y::gui::stackPage::nextClicked() {
  parent->showPage(pageIndex+1);
}