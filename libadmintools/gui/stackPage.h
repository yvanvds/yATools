/* 
 * File:   stackPage.h
 * Author: yvan
 *
 * Created on February 17, 2015, 11:06 AM
 */

#ifndef STACKPAGE_H
#define	STACKPAGE_H



namespace y {
  namespace gui {
    class stackPageManager;
    
    class stackPage : public Wt::WObject {
    public:
      stackPage();

      void create(int index, stackPageManager * parent);
      void showButtons(bool previous, bool next);

      virtual void setContent(Wt::WVBoxLayout * box) = 0;
      virtual void onShow() = 0;
      //virtual void validateAll();

      //void showPreviousButton(bool value);
      //void showNextButton(bool value);
      //void showSaveButton(bool value);

      //void hide();
      //void show();
      //bool visible();

    protected:
      void previousClicked();
      void nextClicked();
     // void saveClicked();

      Wt::WContainerWidget * mainContent;
      Wt::WPushButton * previousButton;
      Wt::WPushButton * nextButton;
      Wt::WPushButton * saveButton;

      int pageIndex;
      stackPageManager * parent;
      
      bool createDone;
    };
  }
}

#endif	/* STACKPAGE_H */

