/* 
 * File:   stepPhoto.cpp
 * Author: yvan
 * 
 * Created on May 14, 2014, 4:46 PM
 */

#include "stepPhoto.h"
#include "yearBook.h"

#include <gui/application.h>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WPanel>
#include <Wt/WDialog>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WBootstrapTheme>
#include <Wt/WTable>
#include <Wt/WTextArea>
#include <Wt/WProgressBar>
#include <Wt/WFileResource>

#include <stdlib.h>

void consOut(const std::string & message) {
  std::cout << message << std::endl;
}

void stepPhoto::setContent(Wt::WVBoxLayout * box) {
  this->box = box;
  
  box->addWidget(new Wt::WText("<h1>De Foto</h1>"));
  box->addWidget(new Wt::WText("<p>Voeg tot slot een mooie foto van jezelf toe. Bij voorkeur in landscape formaat, met de verhouding 3 breed en 2 hoog.</p>"));
 
  image = new Wt::WImage();
  image->setImageLink("http://placekitten.com/600/400");
  
  //image->setWidth(150);
          
  
  
  hint = new Wt::WText();

  box->addWidget(image, 0, Wt::AlignCenter);
  
  box->addWidget(hint);
  fileUpload = NULL;
  setUpload();
}

void stepPhoto::onShow() {
  if(parent->store.photo().empty()) {
    image->setImageLink("http://placekitten.com/600/400");
  } else {
    std::string s = parent->store.photo().toUTF8();
    s += ".png";
    Wt::WFileResource * r = new Wt::WFileResource(s);image->setImageLink(r);
  }
  image->setHeight(300);
}

void stepPhoto::setUpload() {
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
    /*y::utils::Log().add("step 0");
    y::sys::process p("cp");
    p.arg(file);
    std::string out ="userImages/";
    out += parent->store.ID().toUTF8();
    p.arg(out);
    p.run(consOut);*/
    if (!system(NULL)) {
      y::utils::Log().add("command not available");
    } else {
      std::string cmd;
      cmd = "cp ";
      cmd.append(file);
      cmd.append(" userImages/");
      cmd.append(parent->store.ID().toUTF8());
      cmd.append(".png");
      int i = system(cmd.c_str());
      std::string result = "system returned ";
      result.append(std::to_string(i));
      y::utils::Log().add(result);
    }
    std::string out ="userImages/";
    out += parent->store.ID().toUTF8();
    parent->store.photo(out);
    hint->setText("Je foto is opgeslagen.");
    out += ".png";
    Wt::WFileResource * r = new Wt::WFileResource(out);
    image->setImageLink(r);
    image->setHeight(300);
  }));
  
  fileUpload->fileTooLarge().connect(std::bind([=] () {
    hint->setText("Dit bestand is te groot.");
    setUpload();
  }));
  
  box->insertWidget(3, fileUpload, 0, Wt::AlignCenter);
}