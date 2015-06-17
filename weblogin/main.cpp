/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on February 14, 2015, 12:51 PM
 */

#include <Wt/WEnvironment>
#include <Wt/WHBoxLayout>
#include <Wt/WBootstrapTheme>

#include <Wt/WCssTheme>
#include <admintools.h>
#include <Wt/WServer>
#include "../weblogin/application.h"
#include "auth/session.h"


Wt::WApplication * createApplication(const Wt::WEnvironment & env) {
  return new application(env);
}

int main(int argc, char** argv) {
  y::utils::Config().load();
  
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
    server.addEntryPoint(Wt::Application, createApplication);
    userSession::configureAuth();
    server.run();
  } catch (Wt::WServer::Exception & e) {
    y::utils::Log().add(e.what());
  } catch (std::exception & e) {
    string message("exception at application start: ");
    message += e.what();
    y::utils::Log().add(message);
  }   
}

