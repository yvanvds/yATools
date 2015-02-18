/* 
 * File:   stackPageManager.cpp
 * Author: yvan
 * 
 * Created on February 18, 2015, 12:37 PM
 */

#include <Wt/WStackedWidget>

#include "stackPageManager.h"
#include "utils/container.h"

void y::gui::stackPageManager::addPage(stackPage* page) {
  page->create(pages.elms(), this);
  pages.New() = page; 
}

void y::gui::stackPageManager::showPage(int index) {
  if (index < pages.elms()) {
    pages[index]->onShow();
    this->setCurrentIndex(index);
  }
}