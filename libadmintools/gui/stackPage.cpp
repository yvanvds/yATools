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

stackPage::stackPage() : createDone(false), showPrevious(false), showNext(false) {
  
}

void stackPage::create() {
  if(createDone) return;
  
  Wt::WContainerWidget * content = new Wt::WContainerWidget();
  Wt::WVBoxLayout * box = new Wt::WVBoxLayout();
  content->setLayout(box);
  
  setContent(box);
  
  // navigation buttons
  Wt::WHBoxLayout * navBox = new Wt::WHBoxLayout();
  
  if(showPrevious) {
    previousButton = new Wt::WPushButton("vorige");
    previousButton->setWidth(150);
    previousButton->setHeight(35);
    previousButton->clicked().connect(this, &stackPage::previousClicked);
    previousButton->setStyleClass("btn btn-primary");
    navBox->addWidget(previousButton);
  }
  
  if(showNext) {
    nextButton = new Wt::WPushButton("volgende");
    nextButton->setWidth(150);
    nextButton->setHeight(35);
    nextButton->clicked().connect(this, &stackPage::nextClicked);
    nextButton->setDefault(true);
    nextButton->setStyleClass("btn btn-primary");
    navBox->addWidget(nextButton);
  }
  
  box->addWidget(new Wt::WText("<p></p>"));
  box->addLayout(navBox);
  
}

void stackPage::previousClicked() {
  
}

void stackPage::nextClicked() {
  
}