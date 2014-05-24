/* 
 * File:   confirmationDialog.h
 * Author: yvan
 *
 * Created on May 24, 2014, 1:20 PM
 */

#ifndef CONFIRMATIONDIALOG_H
#define	CONFIRMATIONDIALOG_H

#include <Wt/WDialog>
#include <Wt/WPushButton>
#include <Wt/WText>

namespace y {
  namespace gui {
    
    class confirmationDialog {
    public:
      confirmationDialog(const Wt::WString & title);
      ~confirmationDialog();
      void setContents(const Wt::WString & text);
      virtual void handleOK() = 0;
      virtual void handleCancel();
      void show();
      
    private:
      void handleResult(Wt::WDialog::DialogCode code);
      Wt::WDialog * dialog;
      Wt::WText * text;
      Wt::WPushButton * ok;
      Wt::WPushButton * cancel;
    };
  }
}


#endif	/* CONFIRMATIONDIALOG_H */

