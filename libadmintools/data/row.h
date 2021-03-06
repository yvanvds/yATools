/* 
 * File:   row.h
 * Author: yvan
 *
 * Created on May 8, 2014, 8:45 PM
 */

#ifndef ROW_H
#define	ROW_H

#include "field.h"
#include "../utils/container.h"

namespace y {
  namespace data {
    class row {
    public:
      
      row & addBool   (const string & name, bool value = false);
      row & addChar   (const string & name, char value = 0);
      row & addShort  (const string & name, short value = 0);
      row & addInt    (const string & name, int value = 0);
      row & addLong   (const string & name, long value = 0);
      row & addFloat  (const string & name, float value = 0);
      row & addDouble (const string & name, double value = 0);
      row & addString8(const string & name, const string & value = string(""));
      row & addString (const string & name, const string & value = string(""));
      row & addDate   (const string & name, const dateTime & value = dateTime(string("0000-00-00 00:00:00")));
      
      int elms() const;
      row & clear();
      
      // request element by index
      field & operator[](int i);
      // request element by name
      field & operator[](const string & name);
      
      // simple printout of contents for debugging
      void print();
    
    private:
      container<field> fields;
    };
  }
}

#endif	/* ROW_H */

