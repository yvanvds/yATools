/* 
 * File:   yearbookMailinglist.h
 * Author: yvan
 *
 * Created on August 23, 2016, 5:01 PM
 */

#ifndef YEARBOOKMAILINGLIST_H
#define	YEARBOOKMAILINGLIST_H

#include "yearbookDB.h"

class yearbookMailinglist : public Wt::WContainerWidget {
public:
  yearbookMailinglist(yearbookDB * ptr);
  ~yearbookMailinglist();
private:
  yearbookDB * db;
  
};

#endif	/* YEARBOOKMAILINGLIST_H */

