/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on February 14, 2015, 12:51 PM
 */

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WHBoxLayout>
#include <Wt/WBootstrapTheme>

#include <Wt/WCssTheme>
#include <admintools.h>
#include "webLogin.h"

using namespace y;

Wt::WApplication * createApplication(const Wt::WEnvironment& env) {
  Wt::WApplication * app = new Wt::WApplication(env);
  
  if(app->appRoot().empty()) {
    std::cerr << "!!!!!!!!!!" << std::endl
	      << "!! Warning: read the README.md file for hints on deployment,"
	      << " the approot looks suspect!" << std::endl
	      << "!!!!!!!!!!" << std::endl;
  }
  
  Wt::WBootstrapTheme *bootstrapTheme = new Wt::WBootstrapTheme(app);
  bootstrapTheme->setVersion(Wt::WBootstrapTheme::Version3);
  bootstrapTheme->setResponsive(true);
  app->setTheme(bootstrapTheme);

  // load the default bootstrap3 (sub-)theme
  app->useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
  
  Wt::WHBoxLayout * layout = new Wt::WHBoxLayout(app->root());
  layout->setContentsMargins(0, 0, 0, 0);
  //app->root()->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  app->root()->setPadding("5%");
  layout->addWidget(new webLogin(app));

  app->setTitle("Sancta Maria Apps");

  app->useStyleSheet("style/everywidget.css");
  app->useStyleSheet("style/dragdrop.css");
  app->useStyleSheet("style/combostyle.css");
  app->useStyleSheet("style/pygments.css");
  app->useStyleSheet("style/layout.css");

  return app;
}

int main(int argc, char** argv) {
  utils::Config().load();
  int result = Wt::WRun(argc, argv, & createApplication);
  return result;
}

