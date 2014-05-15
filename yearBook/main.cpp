/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on May 12, 2014, 5:58 PM
 */

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include <admintools.h>
#include "yearBook.h"

using namespace y;

int main(int argc, char **argv)
{
  utils::Config().load();
  gui::application<yearBook> app; 
  return app.run(argc, argv);
}