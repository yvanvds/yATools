/* 
 * File:   session.cpp
 * Author: yvan
 * 
 * Created on May 18, 2014, 9:33 PM
 */

#include "session.h"
#include <Wt/WHBoxLayout>
#include <Wt/WContainerWidget>

y::gui::session::session(const Wt::WEnvironment & env) : Wt::WApplication(env) {
  theme = new Wt::WBootstrapTheme();
  theme->setVersion(Wt::WBootstrapTheme::Version3);
  this->setTheme(theme);
  
  root()->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  
  loginDialog.create(this);
  loginDialog.show();
  
  // create stacked widget for content
  content = new Wt::WStackedWidget();
  content->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  content->setMargin("50px", Wt::Side::Top);
  content->setPadding("10px");
  content->setWidth("800px");
  
  // create top menu structure
  Wt::WContainerWidget * topMenu = new Wt::WContainerWidget(root());
  topMenu->setStyleClass("navbar navbar-inverse navbar-fixed-top");
  
  Wt::WContainerWidget * topMenuContainer = new Wt::WContainerWidget();
  topMenuContainer->setStyleClass("container");
  topMenuContainer->setHeight(50);
  topMenu->addWidget(topMenuContainer);
  
  Wt::WHBoxLayout * topMenuBox = new Wt::WHBoxLayout(topMenuContainer);
  Wt::WContainerWidget * titleContainer = new Wt::WContainerWidget();
  topMenuBox->addWidget(titleContainer);
  titleContainer->setStyleClass("navbar_header");
  
  title = new Wt::WText();
  titleContainer->addWidget(title);
  
  Wt::WContainerWidget * menuContainer = new Wt::WContainerWidget();
  topMenuBox->addWidget(menuContainer);
  topMenuBox->setContentsMargins(9,0,9,0);
  menuContainer->setStyleClass("navbar-collapse collapse");
  
  menu = new Wt::WMenu(content, menuContainer);
  //menuContainer->addWidget(menu);
  menu->setStyleClass("nav navbar-nav");
  
  root()->addWidget(content); 
  
}

void y::gui::session::setTitle(const std::string & title) {
  std::string s;
  s = "<a class=\"navbar-brand\" href=\"#\">";
  s.append(title);
  s.append("</a>");
  this->title->setText(s);
  Wt::WApplication::setTitle(title);
}

y::gui::passwordDialog & y::gui::session::login() {
  return loginDialog;
}