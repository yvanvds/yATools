/* 
 * File:   yearbookConfirmRemove.cpp
 * Author: yvan
 * 
 * Created on May 13, 2015, 5:11 PM
 */

#include "yearbookConfirmRemove.h"
#include "yearbookReview.h"


yearbookConfirmRemove::yearbookConfirmRemove() : 
y::gui::confirmationDialog("Ben je zeker?") {
  setContents("Je staat op het punt deze inzending te verwijderen!");
}

void yearbookConfirmRemove::handleOK() {
  parent->removeCurrentEntry();
}