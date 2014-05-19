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
#include "passwordDialog.h"

namespace y {
  namespace gui {
    
    class session : public Wt::WApplication {
    public:
      session(const Wt::WEnvironment & env);
      passwordDialog & login();
      
      virtual bool validate() = 0;
      virtual void onLogin () = 0;
      
    protected:
      Wt::WBootstrapTheme * theme;
      passwordDialog loginDialog;
    };
    
  }
}

#endif	/* SESSION_H */

