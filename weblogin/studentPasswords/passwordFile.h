/* 
 * File:   pdfPasswords.h
 * Author: yvan
 *
 * Created on July 15, 2015, 8:17 PM
 */

#ifndef PDFPASSWORDS_H
#define	PDFPASSWORDS_H

#include <Wt/WResource>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
#include "utils/container.h"
#include "utils/string.h"

class passwordFile : public Wt::WResource {
public:
  passwordFile(Wt::WObject * parent = 0);
 ~passwordFile() { beingDeleted(); }
  
  void clear(const string & name) {
    lines.clear();
    suggestFileName(name.c_str());
  }
 
  virtual void handleRequest(const Wt::Http::Request& request, Wt::Http::Response & response);
  
  passwordFile & addLine(const string & line);  
  passwordFile & addCsv (const string & line);
  
private:
  container<string> lines;
};

#endif	/* PDFPASSWORDS_H */

