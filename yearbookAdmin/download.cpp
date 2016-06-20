/* 
 * File:   download.cpp
 * Author: yvan
 * 
 * Created on May 28, 2014, 3:53 PM
 */

#include <Wt/WText>
#include <Wt/WPushButton>

#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <Wt/WFileResource>

#include "download.h"
#include "yearbookAdmin.h"
#include "dataconnect.h"

download::download(yearbookAdmin * parent) : parent(parent) {
  {  
    Wt::WText * title = new Wt::WText("<h1>Genereer het jaarboek</h1>");
    title->addStyleClass("page-header");
    this->addWidget(title);
    Wt::WContainerWidget * group = new Wt::WContainerWidget();
    group->addStyleClass("well");
    group->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    this->addWidget(group);
    
    group->addWidget(new Wt::WText("<p>Genereer een nieuwe versie van de PDF.</p> <p><b>Let op:</b>Bij ongeldige invoer kan de PDF onvolledig zijn.</p>"));
    Wt::WPushButton * button = new Wt::WPushButton("Maak PDF");
    group->addWidget(button);
    button->clicked().connect(this, &download::generatePDF);
    
    downloadTitle = new Wt::WText("<h1>Download beschikbaar</h1>");
    downloadTitle->addStyleClass("page-header");
    this->addWidget(downloadTitle);
    downloadContainer = new Wt::WContainerWidget();
    downloadContainer->addStyleClass("well");
    downloadContainer->setContentAlignment(Wt::AlignCenter | Wt::AlignMiddle);
    this->addWidget(downloadContainer);
    
    downloadTitle->hide();
    downloadContainer->hide();
    
    downloadFile = new Wt::WFileResource(this);
    downloadFile->setFileName("yearbook_latex/main.pdf");
    downloadFile->setMimeType("application/pdf");
    
    downloadAnchor = new Wt::WAnchor(Wt::WLink(downloadFile), "Download");
    downloadAnchor->setTarget(Wt::TargetNewWindow);
    downloadContainer->addWidget(downloadAnchor);
  }
}

void download::generatePDF() {
  std::fstream content;
  content.open("yearbook_latex/content.tex", std::ios::out | std::ios::trunc);
  
  parent->db.reloadEntries("classgroup");
  
  Wt::WString currentGroup;
  
  for(int i = 0; i < parent->db.entries.size(); i++) {
    entry & currentEntry = parent->db.entries[i];
    
    if (currentGroup.toUTF8().compare(str8(currentEntry.group)) != 0) {
      // new group
      currentGroup = strWt(currentEntry.group);
      std::string groupName = str8(currentEntry.group);
      for (int i = 0; i < parent->db.replacements.elms(); i++) {
        if(parent->db.replacements[i]["original"].asString().compare(currentEntry.group) == 0) {
          groupName = str8(parent->db.replacements[i]["replacement"].asString());
					for(int i = groupName.size() - 1; i != 0; i--) {
					  if(groupName[i] == '&') {
					    groupName.insert(i, '\\');
					    i--;
					  }
          }
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
      
      for (int j = i; j < parent->db.entries.size(); j++) {
        entry & tempEntry = parent->db.entries[j];
        if(currentGroup.toUTF8().compare(str8(tempEntry.group)) != 0) {
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
    content << std::endl << "\\bday \\Large " << date.asString() << std::endl;
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
    } else {
      picture = "Pictures/placeholder";
    }
    content << std::endl << "\\includegraphics[height=7cm]{" << picture << "}" << std::endl;
    content << std::endl << "\\bigskip" << std::endl;
    
    content << std::endl << "\\justifying" << std::endl;
    
    content << std::endl << parent->db.getQuestion(0).toUTF8() << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << str8(currentEntry.answer1) << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << parent->db.getQuestion(1).toUTF8() << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << str8(currentEntry.answer2) << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << parent->db.getQuestion(2).toUTF8() << std::endl;
    content << std::endl << "\\begin{exercise}" << std::endl;
    content << std::endl << "\\detokenize{" << str8(currentEntry.answer3) << "}" << std::endl;
    content << std::endl << "\\end{exercise}" << std::endl;
    
    content << std::endl << parent->db.getQuestion(3).toUTF8() << std::endl;
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
