/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on May 18, 2014, 8:02 PM
 */

#include <cstdlib>
#include <admintools.h>
#include "yearbookAdmin.h"

using namespace y;

int main(int argc, char** argv) {
  utils::Config().load();
  y::utils::Log().add("start of yearbookadmin main 1");
  gui::application<yearbookAdmin> app;
  y::utils::Log().add("start of yearbookadmin main 2");
  return app.run(argc, argv);
}

