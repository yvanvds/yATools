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
: box(nullptr), classUpload(nullptr), studentUpload(nullptr), parentObject(parentObject)
{}

void wisaUpload::setContent(Wt::WVBoxLayout * box) {
  this->box = box;
  
  classContainer = new Wt::WContainerWidget();
  classContainer->addStyleClass("well");
  classContainer->setPadding("1%");
  box->addWidget(classContainer);
  
  classBox = new Wt::WVBoxLayout();
  classContainer->setLayout(classBox);
  
  studentContainer = new Wt::WContainerWidget();
  studentContainer->addStyleClass("well");
  studentContainer->setPadding("1%");
  box->addWidget(studentContainer);
  
  studentBox = new Wt::WVBoxLayout();
  studentContainer->setLayout(studentBox);
  
  classBox->addWidget(new Wt::WText("<h3>Update Klassen</h3>"));
  studentBox->addWidget(new Wt::WText("<h3>Update Leerlingen</h3>"));
  
  cleanClassUpload();
  cleanStudentUpload();
  
  classMessage = new Wt::WText("Kies een wisa export bestand met klassen.");
  classMessage->setStyleClass("alert alert-info");
  classBox->addWidget(classMessage);
  
  studentMessage = new Wt::WText("Kies een wisa export bestand met klassen.");
  studentMessage->setStyleClass("alert alert-info");
  studentBox->addWidget(studentMessage);
  
  #ifdef DEBUG
  Wt::WPushButton * cbutton = new Wt::WPushButton("Parse Classes");
  cbutton->clicked().connect(this, &wisaUpload::classUploadedFunc);
  box->addWidget(cbutton);
  
  Wt::WPushButton * sbutton = new Wt::WPushButton("Parse Students");
  sbutton->clicked().connect(this, &wisaUpload::studentUploadedFunc);
  box->addWidget(sbutton);
#endif
}

void wisaUpload::cleanClassUpload() {
  if(classUpload) {
    classBox->removeWidget(classUpload);
    delete classUpload;
  }
  
  classUpload = new Wt::WFileUpload();
  classUpload->setFileTextSize(1000);
  classUpload->setProgressBar(new Wt::WProgressBar());
  classUpload->changed().connect(this, &wisaUpload::classUploadFunc);
  classUpload->fileTooLarge().connect(this, &wisaUpload::classFileTooLargeFunc);
  classUpload->uploaded().connect(this, &wisaUpload::classUploadedFunc);
  classBox->insertWidget(1, classUpload);
}

void wisaUpload::cleanStudentUpload() {
  if(studentUpload) {
    studentContainer->removeWidget(studentUpload);
    delete studentUpload;
  }
  
  studentUpload = new Wt::WFileUpload();
  studentUpload->setFileTextSize(1000);
  studentUpload->setProgressBar(new Wt::WProgressBar());
  studentUpload->changed().connect(this, &wisaUpload::studentUploadFunc);
  studentUpload->fileTooLarge().connect(this, &wisaUpload::studentFileTooLargeFunc);
  studentUpload->uploaded().connect(this, &wisaUpload::studentUploadedFunc);
  studentBox->insertWidget(1, studentUpload);
}

void wisaUpload::clear() {
  cleanClassUpload();
  cleanStudentUpload();
}


void wisaUpload::classUploadFunc() {
  classUpload->upload();
}

void wisaUpload::studentUploadFunc() {
  studentUpload->upload();
}

void wisaUpload::classFileTooLargeFunc() {
  classMessage->setText("This file is too large");
  classMessage->setStyleClass("alert alert-danger");
  cleanClassUpload();
}

void wisaUpload::studentFileTooLargeFunc() {
  studentMessage->setText("This file is too large");
  studentMessage->setStyleClass("alert alert-danger");
  cleanStudentUpload();
}

void wisaUpload::classUploadedFunc() {
  parentObject->setWisaClassFile(string(classUpload->spoolFileName()));
  parentObject->showNewPage(W_PARSE_CLASS);
  cleanClassUpload();
}

void wisaUpload::studentUploadedFunc() {
  parentObject->setWisaStudentFile(string(studentUpload->spoolFileName()));
  parentObject->showNewPage(W_PARSE_STUDENT);
  cleanStudentUpload();
}

void wisaUpload::onShow() {
  clear();
}