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
  gui::application<yearbookAdmin> app;
  return app.run(argc, argv);
}

