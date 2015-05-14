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

yearbookDownload & YearbookDownload() {
  static yearbookDownload s;
  return s;
}

Wt::WWidget * yearbookDownload::get() {
  mainWidget = new Wt::WContainerWidget();
  
  mainWidget->addStyleClass("well");
  mainWidget->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);

  mainWidget->addWidget(new Wt::WText("<p>Genereer een nieuwe versie van de PDF.</p> <p><b>Let op: </b>Bij ongeldige invoer kan de PDF onvolledig zijn.</p>"));
  Wt::WPushButton * button = new Wt::WPushButton("Maak PDF");
  mainWidget->addWidget(button);
  button->clicked().connect(this, &yearbookDownload::generatePDF);

  downloadTitle = new Wt::WText("<h1>Download beschikbaar</h1>");
  downloadTitle->addStyleClass("page-header");
  mainWidget->addWidget(downloadTitle);
  downloadContainer = new Wt::WContainerWidget();
  downloadContainer->addStyleClass("well");
  downloadContainer->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
  mainWidget->addWidget(downloadContainer);

  downloadTitle->hide();
  downloadContainer->hide();

  downloadFile = new Wt::WFileResource(this);
  downloadFile->setFileName("yearbook_latex/main.pdf");
  downloadFile->setMimeType("application/pdf");

  downloadAnchor = new Wt::WAnchor(Wt::WLink(downloadFile), "Download");
  downloadAnchor->setTarget(Wt::TargetNewWindow);
  downloadContainer->addWidget(downloadAnchor);
  
  return mainWidget;
}

void yearbookDownload::generatePDF() {
  std::fstream content;
  content.open("yearbook_latex/content.tex", std::ios::out | std::ios::trunc);
  
  YearbookDB().loadAllUsers("classgroup", true);
  
  std::wstring currentGroup;
  
  container<yearbookDB::entry> & entries = YearbookDB().getEntries();
  
  for(int i = 0; i < entries.elms(); i++) {
    yearbookDB::entry & currentEntry = entries[i];
    
    if (currentGroup.compare(currentEntry.group) != 0) {
      // new group
      currentGroup = currentEntry.group;
      std::string groupName = str8(currentEntry.group);
      for (int i = 0; i < YearbookDB().getReplacements().elms(); i++) {
        if(YearbookDB().getReplacements()[i][L"original"].asString().compare(currentEntry.group) == 0) {
          groupName = str8(YearbookDB().getReplacements()[i][L"replacement"].asString());
        }
      }
      content << std::endl << "\\chapterimage{Pictures/chapter_head_2}" << std::endl;
      content << std::endl << "\\chapter*{" << groupName << "}" << std::endl;
      content << std::endl << "\\chaptermark{" << groupName << "}" << std::endl;
      content << std::endl << "\\addcontentsline{toc}{chapter}{" << groupName << "}" << std::endl;
      
      content << std::endl << "\\centering" << std::endl;
      content << "\\begin{varwidth}{\\textwidth}" << std::endl;
      content << "\\begin{itemize}" << std::endl;
      content << "\\Large" << std::endl;
      
      for (int j = i; j < YearbookDB().getEntries().elms(); j++) {
        yearbookDB::entry & tempEntry = YearbookDB().getEntries()[j];
        if(currentGroup.compare(tempEntry.group) != 0) {
          break;
        }
 
        content << "\\item " << str8(tempEntry.name) << " " << str8(tempEntry.surname) << std::endl;
        
      }
      content << "\\end{itemize}" << std::endl;
      content << "\\end{varwidth}" << std::endl;
      content << std::endl << "\\newpage" << std::endl;
    }
    
    content << std::endl << "\\section*{\\sectionformat " << str8(currentEntry.name) << " " << str8(currentEntry.surname) << "}" << std::endl;
    content << "\\hrule\\bigskip" << std::endl;
    
    content << std::endl << "\\centering" << std::endl;
    content << "\\begin{varwidth}{\\textwidth}" << std::endl;
    content << "\\begin{itemize}" << std::endl;
    y::ldap::DATE date = y::ldap::DATE(y::ldap::DAY(currentEntry.birthday.day()), y::ldap::MONTH(currentEntry.birthday.month()), y::ldap::YEAR(currentEntry.birthday.year()));
    content << std::endl << "\\bday \\Large " << str8(date.asString()) << std::endl;
    content << "\\end{itemize}" << std::endl;
    content << "\\end{varwidth}" << std::endl;
    
    content << std::endl << "\\bigskip" << std::endl;
    
    std::string mail = str8(currentEntry.mail);
    std::replace(mail.begin(), mail.end(), '%', ' ');
    
    content << "\\begin{varwidth}{\\textwidth}" << std::endl;
    content << "\\begin{itemize}" << std::endl;
    content << std::endl << "\\mail \\Large \\detokenize{" << mail << "}" << std::endl;
    content << "\\end{itemize}" << std::endl;
    content << "\\end{varwidth}" << std::endl;
    
    content << std::endl << "\\bigskip" << std::endl;
    std::string picture;
    if (currentEntry.photo.size() > 0) {
      
      picture = "../" + str8(currentEntry.photo);
      boost::algorithm::replace_first(picture, "userImages", "yearbookImages");
      boost::algorithm::erase_last(picture, ".png");
    } else {
      picture = "Pictures/placeholder";
    }
    content << std::endl << "\\includegraphics[height=7cm]{" << picture << "}" << std::endl;
    content << std::endl << "\\bigskip" << std::endl;
    
    content << std::endl << "\\justifying" << std::endl;
    
    content << std::endl << str8(YearbookDB().getQuestion(0)) << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << str8(currentEntry.answer1) << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << str8(YearbookDB().getQuestion(1)) << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << str8(currentEntry.answer2) << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << str8(YearbookDB().getQuestion(2)) << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << str8(currentEntry.answer3) << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << str8(YearbookDB().getQuestion(3)) << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << str8(currentEntry.answer4) << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    content << std::endl << "\\newpage" << std::endl;
  }
  
  content.close();
  
  std::string cmd;
	cmd =  "export PATH=\"$PATH:/usr/sbin:/usr/bin:/sbin:/bin\"; "; 
	cmd += "cd yearbook_latex; ";
  cmd += "xelatex main; cd ..;";
  system(cmd.c_str());
  system(cmd.c_str());
  
  downloadFile->setFileName("yearbook_latex/main.pdf");
  downloadFile->setMimeType("application/pdf");
  downloadAnchor->setLink(Wt::WLink(downloadFile));
  downloadTitle->show();
  downloadContainer->show();
  
  
}