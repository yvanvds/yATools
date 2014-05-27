/* 
 * File:   step2.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 2:01 PM
 */

#include "step2.h"
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
#include <Wt/WLengthValidator>
#include <Wt/WEvent>

void step2::setContent(Wt::WVBoxLayout * box) {
  box->addWidget(new Wt::WText("<h1>Stap 2</h1>"));
  box->addWidget(new Wt::WText("<p>" + parent->store.getQuestion(0) + "</p>"));
  textArea = new Wt::WTextArea();
  textArea->setColumns(60);
  textArea->setRows(10);
  textArea->changed().connect(this, &step2::contentChanged);
  
  hint = new Wt::WText();
  hint->setText("256 characters remaining");
  hint->addStyleClass("help-block");
  
  
  textArea->keyPressed().connect(std::bind([=] (const Wt::WKeyEvent & e) {
    int count = 256 - textArea->text().toUTF8().length();
    Wt::WString out;
    out = std::to_string(count);
    out += " characters remaining";
    hint->setText(out);
    if (count < 1) {
      out = textArea->text();
      std::string in = out.toUTF8();
      in.resize(256);
      textArea->setText(in);
    }
  }, std::placeholders::_1));
  
  box->addWidget(textArea);
  box->addWidget(hint);
}

void step2::onShow() {
  textArea->setText(parent->store.answer1());
  textArea->setFocus();
}

void step2::contentChanged() {
  parent->store.answer1(textArea->text());
}