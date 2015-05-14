/* 
 * File:   yearbookQuestion.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 3:15 PM
 */

#include <string>
#include <Wt/WTextArea>
#include <Wt/WVBoxLayout>
#include "yearbookDB.h"
#include "yearbookQuestion.h"

yearbookQuestion::yearbookQuestion(int ID) : questionID(ID) {
}

void yearbookQuestion::setContent(Wt::WVBoxLayout* box) {
  std::string title("<h3>Stap ");
  title += std::to_string(questionID + 1);
  title += "</h3>";
  box->addWidget(new Wt::WText(title));
  std::wstring question(L"<p>");
  question += YearbookDB().getQuestion(questionID-1);
  question += L"</p>";
  box->addWidget(new Wt::WText(question));
  textArea = new Wt::WTextArea();
  textArea->setColumns(60);
  textArea->setRows(10);
  textArea->changed().connect(this, &yearbookQuestion::contentChanged);
  
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

void yearbookQuestion::onShow() {
  switch(questionID) {
    case 1: textArea->setText(YearbookDB().answer1()); break;
    case 2: textArea->setText(YearbookDB().answer2()); break;
    case 3: textArea->setText(YearbookDB().answer3()); break;
    case 4: textArea->setText(YearbookDB().answer4()); break;  
  }
  textArea->setFocus();
}

void yearbookQuestion::contentChanged() {
  switch(questionID) {
    case 1: YearbookDB().answer1(textArea->text()); break;
    case 2: YearbookDB().answer2(textArea->text()); break;
    case 3: YearbookDB().answer3(textArea->text()); break;
    case 4: YearbookDB().answer4(textArea->text()); break;
  }
}

bool yearbookQuestion::onNext() {
  YearbookDB().saveUser();
  return true;
}