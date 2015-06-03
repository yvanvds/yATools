/* 
 * File:   yearbookQuestion.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 3:15 PM
 */

#include "utils/string.h"
#include <Wt/WTextArea>
#include <Wt/WVBoxLayout>
#include "yearbookDB.h"
#include "yearbookQuestion.h"

yearbookQuestion::yearbookQuestion(int ID, yearbookDB * ptr) : questionID(ID), db(ptr) {}

void yearbookQuestion::setContent(Wt::WVBoxLayout* box) {
  string title("<h3>Stap ");
  title += (questionID + 1);
  title += "</h3>";
  box->addWidget(new Wt::WText(title.wt()));
  string question("<p>");
  question += db->getQuestion(questionID-1);
  question += "</p>";
  box->addWidget(new Wt::WText(question.wt()));
  textArea = new Wt::WTextArea();
  textArea->setColumns(60);
  textArea->setRows(10);
  textArea->changed().connect(this, &yearbookQuestion::contentChanged);
  
  hint = new Wt::WText();
  hint->setText("256 characters remaining");
  hint->addStyleClass("help-block");
  
  
  textArea->keyPressed().connect(std::bind([=] (const Wt::WKeyEvent & e) {
    int count = 256 - textArea->text().toUTF8().length();
    string out(count);
    out += " characters remaining";
    hint->setText(out.wt());
    if (count < 1) {
      out = string(textArea->text());
      std::string in = out.utf8();
      in.resize(256);
      textArea->setText(in);
    }
  }, std::placeholders::_1));
  
  box->addWidget(textArea);
  box->addWidget(hint);  
  
}

void yearbookQuestion::onShow() {
  switch(questionID) {
    case 1: textArea->setText(db->answer1().wt()); break;
    case 2: textArea->setText(db->answer2().wt()); break;
    case 3: textArea->setText(db->answer3().wt()); break;
    case 4: textArea->setText(db->answer4().wt()); break;  
  }
  textArea->setFocus();
}

void yearbookQuestion::contentChanged() {
  string answer(textArea->text());
  answer.removeNewLine();
  
  switch(questionID) {
    case 1: db->answer1(answer); break;
    case 2: db->answer2(answer); break;
    case 3: db->answer3(answer); break;
    case 4: db->answer4(answer); break;
  }
}

bool yearbookQuestion::onNext() {
  db->saveUser();
  return true;
}