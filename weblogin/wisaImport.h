/* 
 * File:   wisaImport.h
 * Author: yvan
 *
 * Created on February 17, 2015, 10:46 AM
 */

#ifndef WISAIMPORT_H
#define	WISAIMPORT_H

class wisaImport : public Wt::WObject {
public:
  Wt::WWidget * get();
  
private:
  Wt::WPanel * panel;
};

wisaImport & WisaImport();

#endif	/* WISAIMPORT_H */

