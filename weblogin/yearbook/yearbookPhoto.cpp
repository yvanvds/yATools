/* 
 * File:   yearbookPhoto.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 3:42 PM
 */

#include "yearbookPhoto.h"
#include "yearbookDB.h"
#include <Wt/WVBoxLayout>
#include <Wt/WText>
#include <Wt/WFileResource>
#include <Wt/WProgressBar>

yearbookPhoto::~yearbookPhoto() {
  if(imageResource != nullptr) {
    delete imageResource;
  }
}

void yearbookPhoto::setContent(Wt::WVBoxLayout * box) {
  this->box = box;
  
  box->addWidget(new Wt::WText("<h3>Stap 6</h3>"));
  box->addWidget(new Wt::WText("<p>Voeg tot slot een mooie foto van jezelf toe. Bij voorkeur in landscape formaat, met 900x600 pixels.</p>"));
 
  image = new Wt::WImage();
  image->setImageLink("http://placehold.it/600x400");
  
  hint = new Wt::WText();

  box->addWidget(image, 0, Wt::AlignCenter);
  
  box->addWidget(hint);
  setUpload();
}

void yearbookPhoto::onShow() {
  if(db->photo().empty()) {
    image->setImageLink("http://placehold.it/600x400");
  } else {
    string s = db->photo();
    if(imageResource != nullptr) delete imageResource;
    imageResource = new Wt::WFileResource(s.utf8());
    image->setImageLink(imageResource);
  }
  image->setHeight(200);
  image->setWidth(300);
}


void yearbookPhoto::setUpload() {
  if(fileUpload != nullptr) {
    box->removeWidget(fileUpload);
    delete fileUpload;
  }
  
  fileUpload = new Wt::WFileUpload();
  fileUpload->setFileTextSize(10);
  fileUpload->setProgressBar(new Wt::WProgressBar());
  fileUpload->setMargin(10, Wt::Right);
  fileUpload->setFilters("image/*");
  
  fileUpload->changed().connect(std::bind([=] () {
    fileUpload->upload();
  }));
  
  fileUpload->uploaded().connect(std::bind([=] () {
    string file = string(fileUpload->spoolFileName());
    string imageName("yearbookImages/");
    imageName += db->ID();
    imageName += ".png";
    
    string cmd("cp ");
    cmd += file + " "; 
    cmd += imageName;
    cmd.execute();
    
    db->photo(imageName);
    hint->setText("Je foto is opgeslagen.");
    
    if(imageResource != nullptr) delete imageResource;
    
    imageResource = new Wt::WFileResource(imageName.utf8());
    image->setImageLink(imageResource);
    image->setHeight(200);
    image->setWidth(300);
  }));
  
  fileUpload->fileTooLarge().connect(std::bind([=] () {
    hint->setText("Dit bestand is te groot. (Maximum 1MB)");
    setUpload();
  }));
  
  box->insertWidget(3, fileUpload, 0, Wt::AlignCenter);
}

bool yearbookPhoto::onNext() {
  db->saveUser();
  return true;
}