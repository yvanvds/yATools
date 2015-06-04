/* 
 * File:   yearbookConfig.cpp
 * Author: yvan
 * 
 * Created on May 12, 2015, 7:16 PM
 */

#include <Wt/WWidget>
#include <Wt/WContainerWidget>
#include <Wt/WTabWidget>
#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WDateEdit>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WImage>
#include <Wt/WToolBar>
#include <Wt/WFileResource>
#include <Wt/WFileUpload>
#include <Wt/WProgressBar>

#include "yearbookConfig.h"
#include "yearbookDB.h"


void yearbookConfig::loadContent() {
  openDate->setDate(db->getOpenDate());
  closeDate->setDate(db->getCloseDate());
  calculateStatus();
  
  question1->setText(db->getQuestion(0).wt());
  question2->setText(db->getQuestion(1).wt());
  question3->setText(db->getQuestion(2).wt());
  question4->setText(db->getQuestion(3).wt());
}

yearbookConfig::yearbookConfig(yearbookDB* ptr) 
  : db(ptr)
  , imageResource(nullptr)
  , defaultResource(nullptr)
  , imageUpload(nullptr) { 
  tabs = new Wt::WTabWidget(this);
  db->loadAllUsers("name", true);
  
  /***************************************************************
   Activation
   ***************************************************************/
  {
    Wt::WContainerWidget * activation = new Wt::WContainerWidget();
    tabs->addTab(activation, "Activatie");
    
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    group->setHeight(300);
    activation->addWidget(group);
    
    group->addWidget(new Wt::WText("<p>Tijdens deze periode zijn nieuwe inzendingen mogelijk. Een inzending kan gewijzigd worden tot de einddatum.</p>"));
    
    Wt::WTable * table = new Wt::WTable();

    table->elementAt(0,0)->addWidget(new Wt::WText("Open jaarboek op"));
    table->elementAt(1,0)->addWidget(new Wt::WText("Sluit jaarboek op"));

    openDate = new Wt::WDateEdit();
    table->elementAt(0,1)->addWidget(openDate);
    openDate->changed().connect(this, &yearbookConfig::openDateChanged);

    closeDate = new Wt::WDateEdit();
    table->elementAt(1,1)->addWidget(closeDate);
    closeDate->changed().connect(this, &yearbookConfig::closeDateChanged);

    currentDate = new Wt::WText("current status is unknown");
    currentDate->setStyleClass("alert alert-danger");

    table->elementAt(2,1)->addWidget(currentDate);
    table->rowAt(2)->setHeight("60px");
    table->rowAt(2)->elementAt(1)->setVerticalAlignment(Wt::AlignmentFlag::AlignBottom);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    } 

    group->addWidget(table); 
  }
  
  /****************************************************************
   Questions
   ***************************************************************/
  {
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    tabs->addTab(group, "Vragen");
    
    group->addWidget(new Wt::WText("Deze vragen worden gesteld aan de leerlingen."));
    Wt::WTable * table = new Wt::WTable();

    table->elementAt(0,0)->addWidget(new Wt::WText("Vraag 1"));
    table->elementAt(1,0)->addWidget(new Wt::WText("Vraag 2"));
    table->elementAt(2,0)->addWidget(new Wt::WText("Vraag 3"));
    table->elementAt(3,0)->addWidget(new Wt::WText("Vraag 4"));
    
    question1 = new Wt::WLineEdit();
    question1->setTextSize(70);
    question1->changed().connect(this, &yearbookConfig::question1Changed);
    table->elementAt(0,1)->addWidget(question1);

    question2 = new Wt::WLineEdit();
    question2->setTextSize(70);
    question2->changed().connect(this, &yearbookConfig::question2Changed);
    table->elementAt(1,1)->addWidget(question2);
    
    question3 = new Wt::WLineEdit();
    question3->setTextSize(70);
    question3->changed().connect(this, &yearbookConfig::question3Changed);
    table->elementAt(2,1)->addWidget(question3);
    
    question4 = new Wt::WLineEdit();
    question4->setTextSize(70);
    question4->changed().connect(this, &yearbookConfig::question4Changed);
    table->elementAt(3,1)->addWidget(question4);

    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    } 

    group->addWidget(table);
  }
  
  /***************************************************************
   Classes
   ****************************************************************/
  {  
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    tabs->addTab(group, "Klassen");
    
    group->addWidget(new Wt::WText("<p>Geef hier de volledige naam voor elke klascode in.</p>"));
    
    
    container<yearbookDB::entry> & entries = db->getEntries();
    
    for (int i = 0; i < entries.elms(); i++) {
      string group = entries[i].group;
      bool inList = false;
      
      // see if we have this group in our list
      for (int j = 0; j < replacements.elms(); j++) {
        if (replacements[j].key == group) {
          inList = true;
        }
      }
      
      // if not, add it
      if(!inList) {
        replacement & r = replacements.New();
        r.key = group;
        r.value = new Wt::WLineEdit();
        r.value->setWidth("150px");
        
        // see if this exists in the database
        for(int j = 0; j < db->getReplacements().elms(); j++) {
          if(db->getReplacements()[j]["original"].asString() == r.key) {
            r.value->setText(
              db->getReplacements()[j]["replacement"].asString().wt()
            );
            break;
          }
        }
      }
    }
    
    Wt::WTable * table = new Wt::WTable(group);
    int tableIndex = 0;
    bool secondRow = false;
    
    for(int i = 0; i < replacements.elms(); i++) {
      table->elementAt(tableIndex, secondRow?2:0)->addWidget(new Wt::WText(replacements[i].key.wt()));
      table->elementAt(tableIndex, secondRow?3:1)->addWidget(replacements[i].value);      
      tableIndex++;
      if(!secondRow && tableIndex + 1 > replacements.elms() / 2) {
        tableIndex = 0;
        secondRow = true;
      }
    }
    
    Wt::WPushButton * button = new Wt::WPushButton("bewaren");
    button->clicked().connect(this, &yearbookConfig::replacementChange);
    button->setStyleClass("btn btn-success");
    button->setWidth("150px");
    table->elementAt(table->rowCount(), 3)->addWidget(button);
    
    for(int i = 0; i < table->rowCount(); i++) {
      for(int j = 0; j < table->columnCount(); j++) {
        table->elementAt(i, j)->setPadding(5);
      }
    }
  }
  
  /****************************************************************
   Pictures
   ***************************************************************/
  {
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    tabs->addTab(group, "Klasfoto's");
    
    Wt::WTable * layout = new Wt::WTable(group);   
    
    classes = new Wt::WToolBar();
    classes->setCompact(true);
    classes->setOrientation(Wt::Orientation::Vertical);
    classes->setAttributeValue("class", "btn-group-vertical");
    layout->elementAt(0,0)->addWidget(classes);
    
    for(int i = 0; i < replacements.elms(); i++) {
      Wt::WPushButton * button = new Wt::WPushButton(replacements[i].key.wt());
      button->clicked().connect(boost::bind(&yearbookConfig::setImage, this, i));
      classes->addButton(button);
      container<y::data::row> & images = db->getGroupImages();
      for(int j =0; j < images.elms(); j++) {
        if(replacements[i].key == images[j]["groupName"].asString()) {          
          replacements[i].image = images[j]["imageName"].asString();
          break;
        }
      }
    }
    
    contentContainer = new Wt::WContainerWidget();
    contentContainer->setPadding(Wt::WLength(10));
    layout->elementAt(0,1)->addWidget(contentContainer);
    contentContainer->addWidget(new Wt::WText("Voor elke klas kan je een groepsfoto uploaden. Voor een goede layout is het belangrijk dat de foto dubbel zo breed dan hoog is (bijvoorbeeld 1000x500 pixels)."));
    groupImage = new Wt::WImage();
    defaultResource = new Wt::WFileResource("yearbook_latex/Pictures/chapter_head_2.png");
    groupImage->setImageLink(defaultResource);
    groupImage->resize("600px", "300px");
    contentContainer->addWidget(groupImage);
    imageHint = new Wt::WText();
    contentContainer->addWidget(imageHint);
    createUpload();
    setImage(0);    
  }
  
  loadContent();
}

yearbookConfig::~yearbookConfig() {
  if(imageResource != nullptr) {
    delete imageResource;
  }
  if(defaultResource != nullptr) {
    delete defaultResource;
  }
}

void yearbookConfig::openDateChanged() {
  db->setOpenDate(openDate->date());
  calculateStatus();
}

void yearbookConfig::closeDateChanged() {
  db->setCloseDate(closeDate->date());
  calculateStatus();
}

void yearbookConfig::calculateStatus() {
  Wt::WDate begin =  openDate->date();
  Wt::WDate end = closeDate->date();
  Wt::WDate current;
  current = Wt::WDate::currentServerDate();
  
  if(current >= begin && current <= end) {
    currentDate->setText("De client interface is open.");
    currentDate->setStyleClass("alert alert-success");
  } else {
    currentDate->setText("De client interface is gesloten.");
    currentDate->setStyleClass("alert alert-danger");
  }
}

void yearbookConfig::question1Changed() {
  db->setQuestion(0, question1->text());
}

void yearbookConfig::question2Changed() {
  db->setQuestion(1, question2->text());
}

void yearbookConfig::question3Changed() {
  db->setQuestion(2, question3->text());
}

void yearbookConfig::question4Changed() {
  db->setQuestion(3, question4->text());
}

void yearbookConfig::replacementChange() {
  for (int i = 0; i < replacements.elms(); i++) {
    db->replace(replacements[i].key, (replacements[i].value->text()));
  }
}

void yearbookConfig::setImage(int group) {
  for(int i = 0; i < classes->count(); i++) {
    classes->widget(i)->setStyleClass("btn btn-default");
  }
  classes->widget(group)->setStyleClass("btn btn-primary");
  
  if(replacements[group].image.empty()) {
    groupImage->setImageLink(defaultResource);
    groupImage->resize("600px", "300px");
  } else {
    if(imageResource != nullptr) delete imageResource;    
    imageResource = new Wt::WFileResource(replacements[group].image.utf8());
    groupImage->setImageLink(imageResource);
    groupImage->resize("600px", "300px");
  }
  currentGroup = group;
}

void yearbookConfig::createUpload() {
  if(imageUpload != nullptr) {
    contentContainer->removeWidget(imageUpload);
    delete imageUpload;
  }
  
  imageUpload = new Wt::WFileUpload();
  imageUpload->setFileTextSize(10);
  imageUpload->setProgressBar(new Wt::WProgressBar());
  imageUpload->setMargin(10, Wt::Right);
  imageUpload->setFilters("image/*");
  
  imageUpload->changed().connect(std::bind([=] () {
    imageUpload->upload();
  }));
  
  imageUpload->uploaded().connect(std::bind([=] () {
    string file = string(imageUpload->spoolFileName());
    string imageName("yearbookImages/");
    imageName += replacements[currentGroup].key;
    imageName += ".png";
    
    string cmd("cp ");
    cmd += file + " "; 
    cmd += imageName;
    cmd.execute();
    
    replacements[currentGroup].image = imageName;
    db->saveGroupImage(replacements[currentGroup].key, replacements[currentGroup].image);
    imageHint->setText("<p>Je foto is opgeslagen.</p>");
    
    if(imageResource != nullptr) delete imageResource;
    
    imageResource = new Wt::WFileResource(imageName.utf8());
    groupImage->setImageLink(imageResource);
    groupImage->resize("600px", "300px");
    createUpload();
  }));
  
  imageUpload->fileTooLarge().connect(std::bind([=] () {
    imageHint->setText("<p>Dit bestand is te groot. (Maximum 1MB)</p>");
    createUpload();
  }));
  
  contentContainer->insertWidget(3, imageUpload);
}