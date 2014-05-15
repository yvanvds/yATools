/* 
 * File:   step5.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 4:17 PM
 */

#include "step5.h"
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
#include <Wt/WTextArea>

void step5::setContent(Wt::WVBoxLayout * box) {
  box->addWidget(new Wt::WText("<h1>Stap 5</h1>"));
  box->addWidget(new Wt::WText("<p>Had je 10 miljoen, wat zou jij dan doen...</p>"));
  textArea = new Wt::WTextArea();
  textArea->setColumns(60);
  textArea->setRows(10);
  //textArea->setPlaceholderText("");
  textArea->changed().connect(this, &step5::contentChanged);
  box->addWidget(textArea);
}

void step5::onShow() {
  textArea->setText(parent->store.answer4());
}

void step5::contentChanged() {
  parent->store.answer4(textArea->text());
}