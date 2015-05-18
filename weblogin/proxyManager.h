/* 
 * File:   proxyManager.h
 * Author: yvan
 *
 * Created on February 15, 2015, 7:38 PM
 */

#ifndef PROXYMANAGER_H
#define	PROXYMANAGER_H

#include <Wt/WObject>
#include <string>
#include <Wt/WLabel>
#include <Wt/WButtonGroup>
#include <Wt/WRadioButton>
#include <vector>
#include "utils/proxy.h"

class room {
public:
  
  room(const string & name);
  void create(Wt::WTableRow * row);
  void buttonClicked(Wt::WRadioButton * selected);
  
  void setStatus(y::utils::proxy::STATUS status, bool silent = false);
  Wt::WButtonGroup * getGroup();
  
private:
  int ID;
  string name;
  Wt::WText * label;
  Wt::WButtonGroup * bgroup;
  Wt::WRadioButton * button1;
  Wt::WRadioButton * button2;
  Wt::WRadioButton * button3;
};

class proxyManager : public Wt::WObject {
public:
  Wt::WWidget * get();
  
  room * getRoom(Wt::WButtonGroup * group);
private:
  std::vector<room> rooms;
  
};

proxyManager & ProxyManager();

#endif	/* PROXYMANAGER_H */

