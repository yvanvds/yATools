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
      
      row & addBool   (const std::string & name, bool value = false);
      row & addChar   (const std::string & name, char value = 0);
      row & addShort  (const std::string & name, short value = 0);
      row & addInt    (const std::string & name, int value = 0);
      row & addLong   (const std::string & name, long value = 0);
      row & addFloat  (const std::string & name, float value = 0);
      row & addDouble (const std::string & name, double value = 0);
      row & addString8(const std::string & name, const std::string & value = "");
      row & addString (const std::string & name, const std::u16string & value = u"");
      row & addDate   (const std::string & name, const dateTime & value = dateTime("0000-00-00 00:00:00"));
      
      int elms() const;
      row & clear();
      
      // request element by index
      field & operator[](int i);
      // request element by name
      field & operator[](const std::string & name);
    
    private:
      container<field> fields;
    };
  }
}

#endif	/* ROW_H */

