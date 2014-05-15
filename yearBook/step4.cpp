/* 
 * File:   step4.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 4:11 PM
 */

#include "step4.h"
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

void step4::setContent(Wt::WVBoxLayout * box) {
  box->addWidget(new Wt::WText("<h1>Stap 4</h1>"));
  box->addWidget(new Wt::WText("<p>Born to be wild! Wat is je wildste droom?</p>"));
  textArea = new Wt::WTextArea();
  textArea->setColumns(60);
  textArea->setRows(10);
  //textArea->setPlaceholderText("");
  textArea->changed().connect(this, &step4::contentChanged);
  box->addWidget(textArea);
}

void step4::onShow() {
  textArea->setText(parent->store.answer3());
}

void step4::contentChanged() {
  parent->store.answer3(textArea->text());
}