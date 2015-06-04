/* 
 * File:   yearbookDownload.cpp
 * Author: yvan
 * 
 * Created on May 13, 2015, 7:36 PM
 */

#include <Wt/WWidget>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WFileResource>

#include "yearbookDownload.h"
#include "yearbookDB.h"

yearbookDownload::yearbookDownload(yearbookDB * ptr) : db(ptr), downloadFile(nullptr) {
  addStyleClass("well");
  setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);

  addWidget(new Wt::WText("<p>Genereer een nieuwe versie van de PDF.</p> <p><b>Let op: </b>Bij ongeldige invoer kan de PDF onvolledig zijn.</p>"));
  Wt::WPushButton * button = new Wt::WPushButton("Maak PDF");
  addWidget(button);
  button->clicked().connect(this, &yearbookDownload::generatePDF);

  downloadTitle = new Wt::WText("<h1>Download beschikbaar</h1>");
  downloadTitle->addStyleClass("page-header");
  addWidget(downloadTitle);
  downloadContainer = new Wt::WContainerWidget();
  downloadContainer->addStyleClass("well");
  downloadContainer->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  addWidget(downloadContainer);

  downloadTitle->hide();
  downloadContainer->hide();

  downloadFile = new Wt::WFileResource(this);
  downloadFile->setFileName("yearbook_latex/main.pdf");
  downloadFile->setMimeType("application/pdf");

  downloadAnchor = new Wt::WAnchor(Wt::WLink(downloadFile), "Download");
  downloadAnchor->setTarget(Wt::TargetNewWindow);
  downloadContainer->addWidget(downloadAnchor);
}

yearbookDownload::~yearbookDownload() {
  if(downloadFile != nullptr) delete downloadFile;
}

void yearbookDownload::generatePDF() {
  std::fstream content;
  content.open("yearbook_latex/content.tex", std::ios::out | std::ios::trunc);
  
  db->loadAllUsers("classgroup", true);
  
  string currentGroup;
  
  container<yearbookDB::entry> & entries = db->getEntries();
  
  for(int i = 0; i < entries.elms(); i++) {
    yearbookDB::entry & currentEntry = entries[i];
    
    if (currentGroup != currentEntry.group) {
      // new group
      currentGroup = currentEntry.group;
      string groupName = currentEntry.group;
      for (int i = 0; i < db->getReplacements().elms(); i++) {
        if(db->getReplacements()[i]["original"].asString() == currentEntry.group) {
          groupName = db->getReplacements()[i]["replacement"].asString();
        }
      }
      
      std::string groupImage = "Pictures/chapter_head_2";
      for(int i = 0; i < db->getGroupImages().elms(); i++) {
        if(db->getGroupImages()[i]["groupName"].asString() == currentGroup) {
          groupImage = "../" + db->getGroupImages()[i]["imageName"].asString().utf8();
          boost::algorithm::erase_last(groupImage, ".png");
          break;
        }
      }
      content << std::endl << "\\chapterimage{" << groupImage << "}" << std::endl;
      content << std::endl << "\\chapter*{" << groupName << "}" << std::endl;
      content << std::endl << "\\chaptermark{" << groupName << "}" << std::endl;
      content << std::endl << "\\addcontentsline{toc}{chapter}{" << groupName << "}" << std::endl;
      
      content << std::endl << "\\centering" << std::endl;
      content << "\\begin{varwidth}{\\textwidth}" << std::endl;
      content << "\\begin{itemize}" << std::endl;
      content << "\\Large" << std::endl;
      
      for (int j = i; j < db->getEntries().elms(); j++) {
        yearbookDB::entry & tempEntry = db->getEntries()[j];
        if(currentGroup != tempEntry.group) {
          break;
        }
 
        content << "\\item " << tempEntry.name << " " << tempEntry.surname << std::endl;
        
      }
      content << "\\end{itemize}" << std::endl;
      content << "\\end{varwidth}" << std::endl;
      content << std::endl << "\\newpage" << std::endl;
    }
    
    content << std::endl << "\\section*{\\sectionformat " << currentEntry.name << " " << currentEntry.surname << "}" << std::endl;
    content << "\\hrule\\bigskip" << std::endl;
    
    content << std::endl << "\\centering" << std::endl;
    content << "\\begin{varwidth}{\\textwidth}" << std::endl;
    content << "\\begin{itemize}" << std::endl;
    y::ldap::DATE date = y::ldap::DATE(y::ldap::DAY(currentEntry.birthday.day()), y::ldap::MONTH(currentEntry.birthday.month()), y::ldap::YEAR(currentEntry.birthday.year()));
    content << std::endl << "\\bday \\Large " << date.asString() << std::endl;
    content << "\\end{itemize}" << std::endl;
    content << "\\end{varwidth}" << std::endl;
    
    content << std::endl << "\\bigskip" << std::endl;
    
    std::string mail = currentEntry.mail.utf8();
    std::replace(mail.begin(), mail.end(), '%', ' ');
    
    content << "\\begin{varwidth}{\\textwidth}" << std::endl;
    content << "\\begin{itemize}" << std::endl;
    content << std::endl << "\\mail \\Large \\detokenize{" << mail << "}" << std::endl;
    content << "\\end{itemize}" << std::endl;
    content << "\\end{varwidth}" << std::endl;
    
    content << std::endl << "\\bigskip" << std::endl;
    std::string picture;
    if (currentEntry.photo.size() > 0) {
      
      picture = "../" + currentEntry.photo.utf8();
      boost::algorithm::replace_first(picture, "userImages", "yearbookImages");
      boost::algorithm::erase_last(picture, ".png");
    } else {
      picture = "Pictures/placeholder";
    }
    content << std::endl << "\\includegraphics[height=7cm]{" << picture << "}" << std::endl;
    content << std::endl << "\\bigskip" << std::endl;
    
    content << std::endl << "\\justifying" << std::endl;
    
    content << std::endl << db->getQuestion(0) << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << currentEntry.answer1 << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << db->getQuestion(1) << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << currentEntry.answer2 << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << db->getQuestion(2) << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << currentEntry.answer3 << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << db->getQuestion(3) << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << currentEntry.answer4 << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    content << std::endl << "\\newpage" << std::endl;
  }
  
  content.close();
  
  string cmd;
	cmd =  "export PATH=\"$PATH:/usr/sbin:/usr/bin:/sbin:/bin\"; "; 
	cmd += "cd yearbook_latex; ";
  cmd += "xelatex main; cd ..;";
  cmd.execute();
  cmd.execute();
  
  downloadFile->setFileName("yearbook_latex/main.pdf");
  downloadFile->setMimeType("application/pdf");
  downloadAnchor->setLink(Wt::WLink(downloadFile));
  downloadTitle->show();
  downloadContainer->show(); 
}