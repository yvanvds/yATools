/* 
 * File:   step6.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 4:35 PM
 */

#include "step6.h"
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

void step6::setContent(Wt::WVBoxLayout * box) {
  box->addWidget(new Wt::WText("<h1>Bedankt!</h1>"));
  box->addWidget(new Wt::WText("<p>Je antwoorden zijn opgeslagen, maar hebt nog 3 dagen om ze aan te passen. Daarna maken we er een mooi jaarboek van.</p>"));
}

void step6::onShow() {
  
}

void step6::contentChanged() {
  
}