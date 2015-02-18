/* 
 * File:   wisaImport.cpp
 * Author: yvan
 * 
 * Created on February 17, 2015, 10:46 AM
 */

#include <Wt/WWidget>
#include <Wt/WStackedWidget>
#include <Wt/WCompositeWidget>
#include <Wt/WPanel>

#include "wisaImport.h"

wisaImport & WisaImport() {
  static wisaImport w;
  return w;
}

Wt::WWidget * wisaImport::get() {
  Wt::WStackedWidget * stack = new Wt::WStackedWidget();
  
  Wt::WContainerWidget * result = new Wt::WContainerWidget();
  panel = new Wt::WPanel(result);
  panel->setStyleClass("panel panel-primary");
  panel->setCentralWidget(stack);
  panel->setTitle("<h3>Wisa Import</h3>");
  panel->setMaximumSize(800, Wt::WLength::Auto);
  return result;
}

