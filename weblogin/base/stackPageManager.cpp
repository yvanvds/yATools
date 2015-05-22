/* 
 * File:   stackPageManager.cpp
 * Author: yvan
 * 
 * Created on February 18, 2015, 12:37 PM
 */

#include <Wt/WStackedWidget>

#include "stackPageManager.h"
#include "stackPage.h"
#include "utils/container.h"

void stackPageManager::addPage(stackPage* page) {
  page->setIndex(pages.elms());
  pages.New() = page;
  page->create(this);
  addWidget(page);
}

void stackPageManager::showPage(int index) {
  if (index < pages.elms()) {
    pages[index]->onShow();
    this->setCurrentIndex(index);
  }
}