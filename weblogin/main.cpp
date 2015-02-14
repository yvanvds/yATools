/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on February 14, 2015, 12:51 PM
 */

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include <cstdlib>
#include <admintools.h>
#include "webLogin.h"

using namespace y;

int main(int argc, char** argv) {
  utils::Config().load();
  gui::application<webLogin> app;
  
  return app.run(argc, argv);
}

