/* 
 * File:   application.h
 * Author: yvan
 *
 * Created on May 12, 2014, 7:01 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

namespace y {
  namespace gui {
    
    template<class T>
    class application {
    private:
    
      static Wt::WApplication * createApplication(const Wt::WEnvironment& env) {
        return new T(env);
      }
      
    public:
      int run(int argc, char **argv) {
        return Wt::WRun(argc, argv, &createApplication);
      }
    
    private:
 
    };
  }
}

#endif	/* APPLICATION_H */

