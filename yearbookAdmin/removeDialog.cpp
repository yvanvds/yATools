/* 
 * File:   removeDialog.cpp
 * Author: yvan
 * 
 * Created on May 24, 2014, 2:50 PM
 */


#include "review.h"
#include "removeDialog.h"
#include "yearbookAdmin.h"

removeDialog::removeDialog(review * parent)
: parent(parent), y::gui::confirmationDialog("Ben je zeker?") {
  setContents("OK klikken verwijdert deze inzending!");
}

void removeDialog::handleOK() {
  parent->removeCurrentEntry();
}

