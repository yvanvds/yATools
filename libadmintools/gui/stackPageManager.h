/* 
 * File:   stackPageManager.h
 * Author: yvan
 *
 * Created on February 18, 2015, 12:37 PM
 */

#ifndef STACKPAGEMANAGER_H
#define	STACKPAGEMANAGER_H

#include "stackPage.h"
#include "utils/container.h"
#include <Wt/WStackedWidget>

namespace y {
  namespace gui {
    class stackPageManager : public Wt::WStackedWidget {
    public:
      void addPage(stackPage * page);
      void showPage(int index);
    private:
      container<stackPage*> pages;
    };
  }
}



#endif	/* STACKPAGEMANAGER_H */

