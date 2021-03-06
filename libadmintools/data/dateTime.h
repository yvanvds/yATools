/* 
 * File:   dateTime.h
 * Author: yvan
 *
 * Created on May 14, 2014, 9:01 PM
 */

#ifndef DATETIME_H
#define	DATETIME_H

#include "utils/string.h"

namespace y {
  namespace data {
    
    class dateTime {
    public:
      dateTime();
      dateTime(const string & dbFormat);
      
      dateTime & day    (int value);
      dateTime & month  (int value);
      dateTime & year   (int value);
      dateTime & hours  (int value);
      dateTime & minutes(int value);
      dateTime & seconds(int value);
      
      int day    () const;
      int month  () const;
      int year   () const;
      int hours  () const;
      int minutes() const;
      int seconds() const;
      
      string dbFormat(                    ) const;
      void   dbFormat(const string & value)      ;
      
      int _day    ;
      int _month  ;
      int _year   ;
      int _hours  ;
      int _minutes;
      int _seconds;
    };
    
  }
}

#endif	/* DATETIME_H */

