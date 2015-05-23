/* 
 * File:   yearbookDone.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 4:35 PM
 */

#include "yearbookDone.h"
#include "yearbookDB.h"
#include <Wt/WDate>
#include <Wt/WVBoxLayout>
#include <Wt/WText>

void yearbookDone::setContent(Wt::WVBoxLayout* box) {
  box->addWidget(new Wt::WText("<h1>Bedankt!</h1>"));
  Wt::WDate date;
  date = date.currentServerDate();
  string s;
  s = "<p>Je antwoorden zijn opgeslagen, maar hebt nog ";
  s += date.daysTo(db->getCloseDate());
  s += " dagen om ze aan te passen. Daarna maken we er een mooi jaarboek van.</p>"; 
  box->addWidget(new Wt::WText(s.wt()));  

  
}

void yearbookDone::onShow() {

}