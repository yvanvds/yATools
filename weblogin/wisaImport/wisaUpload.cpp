/* 
 * File:   wisaUpload.cpp
 * Author: yvan
 * 
 * Created on May 6, 2015, 4:18 PM
 */

#include "wisaUpload.h"
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WTable>
#include <Wt/WApplication>
#include <Wt/WVBoxLayout>
#include <Wt/WFileUpload>
#include <Wt/WProgressBar>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"


wisaUpload::wisaUpload(wisaImport * parentObject)
: box(nullptr), fileUpload(nullptr), parentObject(parentObject)
{}

void wisaUpload::setContent(Wt::WVBoxLayout * box) {
  this->box = box;
  cleanUpload();
  message = new Wt::WText("Kies een wisa export bestand.");
  message->setStyleClass("alert alert-info");
  box->addWidget(message);
  #ifdef DEBUG
  Wt::WPushButton * button = new Wt::WPushButton("Parse");
  button->clicked().connect(this, &wisaUpload::uploadedFunc);
  box->addWidget(button);
#endif
}

void wisaUpload::cleanUpload() {
  if(fileUpload) {
    box->removeWidget(fileUpload);
    delete fileUpload;
  }
  
  fileUpload = new Wt::WFileUpload();
  fileUpload->setFileTextSize(1000);
  fileUpload->setProgressBar(new Wt::WProgressBar());
  fileUpload->changed().connect(this, &wisaUpload::uploadFunc);
  fileUpload->fileTooLarge().connect(this, &wisaUpload::fileTooLargeFunc);
  fileUpload->uploaded().connect(this, &wisaUpload::uploadedFunc);
  box->insertWidget(0, fileUpload);
  

}

void wisaUpload::clear() {
  cleanUpload();
}


void wisaUpload::uploadFunc() {
  fileUpload->upload();
  
}

void wisaUpload::fileTooLargeFunc() {
  message->setText("This file is too large");
  message->setStyleClass("alert alert-danger");
  cleanUpload();
}

void wisaUpload::uploadedFunc() {
  parentObject->setWisaFile(string(fileUpload->spoolFileName()));
  parent->showPage(pageIndex + 1);
  cleanUpload();
}

void wisaUpload::onShow() {
  cleanUpload();
}