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
#include "utils/container.h" 
#include "ldap/server.h"
#include "../wisaImport.h"

wisaUpload::wisaUpload() : box(nullptr), fileUpload(nullptr) {}

void wisaUpload::setContent(Wt::WVBoxLayout* box) {
  this->box = box;
  
  cleanUpload();

  message = new Wt::WText("Kies een wisa export bestand.");
  message->setStyleClass("alert alert-info");
  box->addWidget(message);
}

void wisaUpload::cleanUpload() {
  if(fileUpload && box) {
    box->removeWidget(fileUpload);
  }
  
  fileUpload = new Wt::WFileUpload();
  fileUpload->setFileTextSize(1000);
  fileUpload->setProgressBar(new Wt::WProgressBar());
  fileUpload->changed().connect(this, &wisaUpload::uploadFunc);
  fileUpload->fileTooLarge().connect(this, &wisaUpload::fileTooLargeFunc);
  fileUpload->uploaded().connect(this, &wisaUpload::uploadedFunc);
  if(box) box->insertWidget(0, fileUpload);
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
}

void wisaUpload::uploadedFunc() {
  WisaImport().setWisaFile(fileUpload->spoolFileName());
  parent->showPage(pageIndex + 1);
}

void wisaUpload::onShow() {
  cleanUpload();
}