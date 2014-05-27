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
  box->addWidget(new Wt::WText("<p>" + parent->store.getQuestion(2) + "</p>"));
  textArea = new Wt::WTextArea();
  textArea->setColumns(60);
  textArea->setRows(10);
  //textArea->setPlaceholderText("");
  textArea->changed().connect(this, &step4::contentChanged);
  
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

void step4::onShow() {
  textArea->setText(parent->store.answer3());
  textArea->setFocus();

}

void step4::contentChanged() {
  parent->store.answer3(textArea->text());
}