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
      
      row & addBool   (const std::string & name, bool value);
      row & addChar   (const std::string & name, char value);
      row & addShort  (const std::string & name, short value);
      row & addInt    (const std::string & name, int value);
      row & addLong   (const std::string & name, long value);
      row & addFloat  (const std::string & name, float value);
      row & addDouble (const std::string & name, double value);
      row & addString8(const std::string & name, const std::string & value);
      row & addString (const std::string & name, const std::u16string & value);
      
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

