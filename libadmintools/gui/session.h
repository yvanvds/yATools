/* 
 * File:   session.h
 * Author: yvan
 *
 * Created on May 18, 2014, 9:33 PM
 */

#ifndef SESSION_H
#define	SESSION_H

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WBootstrapTheme>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/WStackedWidget>
#include <string>
#include "passwordDialog.h"

namespace y {
  namespace gui {
    
    class session : public Wt::WApplication {
    public:
      session(const Wt::WEnvironment & env);
      void setTitle(const std::string & title);
      passwordDialog & login();
      
      virtual bool validate() = 0;
      virtual void onLogin () = 0;
      
    protected:
      Wt::WBootstrapTheme * theme;
      Wt::WStackedWidget * content;
      Wt::WMenu * menu;
      Wt::WText * title;
      
      passwordDialog loginDialog;
    };
    
  }
}

#endif	/* SESSION_H */

