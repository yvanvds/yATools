/* 
 * File:   staffList.h
 * Author: yvan
 *
 * Created on June 16, 2015, 5:57 PM
 */

#ifndef STAFFLIST_H
#define	STAFFLIST_H

#include <Wt/WContainerWidget>
#include <Wt/WComboBox>

class staffList : public Wt::WContainerWidget {
public:
  staffList(y::ldap::server * server, y::data::adminRights * rights);
  
private:
  void openDialog(int withEntry);
  void loadTableContent();
  void createDialog();
  void loadDialogContent();
  
  void saveEdit();
  void deleteUser(int entry);
  
  int currentEntry;
  
  y::ldap::server * server;
  
  Wt::WTable * table;
  
  Wt::WDialog * dialog;
  Wt::WContainerWidget * dialogContainer;
  
  Wt::WTable * infoTable;
  Wt::WLineEdit * wisaName;
  Wt::WComboBox * group;
  
  Wt::WTable * adminTable;
  Wt::WCheckBox * personeel;
  Wt::WCheckBox * passwords;
  Wt::WCheckBox * wisa;
  Wt::WCheckBox * yearbook;
  
  y::data::adminRights * rights;
};

#endif	/* STAFFLIST_H */

