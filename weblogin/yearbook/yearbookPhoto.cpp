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

void yearbookPhoto::setContent(Wt::WVBoxLayout * box) {
  this->box = box;
  
  box->addWidget(new Wt::WText("<h3>Stap 6</h3>"));
  box->addWidget(new Wt::WText("<p>Voeg tot slot een mooie foto van jezelf toe. Bij voorkeur in landscape formaat, met 900x600 pixels.</p>"));
 
  image = new Wt::WImage();
  image->setImageLink("http://placehold.it/600x400");
  
  hint = new Wt::WText();

  box->addWidget(image, 0, Wt::AlignCenter);
  
  box->addWidget(hint);
  fileUpload = NULL;
  setUpload();
}

void yearbookPhoto::onShow() {
  if(YearbookDB().photo().empty()) {
    image->setImageLink("http://placehold.it/600x400");
  } else {
    std::string s = str8(YearbookDB().photo());

    Wt::WFileResource * r = new Wt::WFileResource(s);
    image->setImageLink(r);
  }
  image->setHeight(200);
  image->setWidth(300);
}


void yearbookPhoto::setUpload() {
  if(fileUpload != NULL) {
    box->removeWidget(fileUpload);
  }
  
  fileUpload = new Wt::WFileUpload();
  fileUpload->setFileTextSize(1000);
  fileUpload->setProgressBar(new Wt::WProgressBar());
  fileUpload->setMargin(10, Wt::Right);
  fileUpload->setFilters("image/*");
  
  fileUpload->changed().connect(std::bind([=] () {
    fileUpload->upload();
  }));
  
  fileUpload->uploaded().connect(std::bind([=] () {
    std::string file = fileUpload->spoolFileName();
    std::string imageName("yearbookImages/");
    imageName += str8(YearbookDB().ID());
    imageName += ".png";
    
    std::string cmd("cp ");
    cmd.append(file);
    cmd.append(" "); cmd.append(imageName);
    system(cmd.c_str());
    
    YearbookDB().photo(strW(imageName));
    hint->setText("Je foto is opgeslagen.");
    
    Wt::WFileResource * r = new Wt::WFileResource(imageName);
    image->setImageLink(r);
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
  YearbookDB().saveUser();
  return true;
}