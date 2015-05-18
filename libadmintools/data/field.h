/* 
 * File:   field.h
 * Author: yvan
 *
 * Created on May 8, 2014, 9:07 PM
 */

#ifndef FIELD_H
#define	FIELD_H

#include <string>
#include "dateTime.h"

namespace y {
  namespace data {
    
    enum FIELD_TYPE {
      UNKNOWN,
      BOOL,
      CHAR,     // 8  bit int
      SHORT,    // 16 bit int
      INT,      // 32 bit int
      LONG,     // 64 bit int
      FLOAT,    // 32 bit real
      DOUBLE,   // 64 bit real
      STRING8,   // 8  bit string
      STRING,  // 16 bit string
      UID,      // unique ID
      DATE_TIME,// 
      BINARY,
    };
    
    class field {
    public:
      field();
      explicit field(const string & name, bool   value);
      explicit field(const string & name, char   value);
      explicit field(const string & name, short  value);
      explicit field(const string & name, int    value);
      explicit field(const string & name, long   value);
      explicit field(const string & name, float  value);
      explicit field(const string & name, double value);
      explicit field(const string & name, const string   & value);
      explicit field(const string & name, const dateTime & value);
      
      FIELD_TYPE getType();
      
      bool    asBool  ();
      char    asChar  ();
      short   asShort ();
      int     asInt   ();
      long    asLong  ();
      float   asFloat ();
      double  asDouble();
      const string   & asString();
      const dateTime & asDate  ();
      
      field & setBool  (bool   value);
      field & setChar  (char   value);
      field & setShort (short  value);
      field & setInt   (int    value);
      field & setLong  (long   value);
      field & setFloat (float  value);
      field & setDouble(double value);
      field & setString(const  string   & value);
      field & setDate  (const  dateTime & value);
      
      const string & name();
      field & name(const string & fieldName);
      
      // these are used when you supply fields to create
      // a new table
      field & stringLength (int length);
      field & required     (bool value);
      field & autoIncrement(bool value);
      field & primaryKey   (bool value);
      
      int  stringLength ();
      bool required     ();
      bool autoIncrement();
      bool primaryKey   ();
      
      // for debugging
      void print();
      
    private:
      
      string fieldName;
      FIELD_TYPE type;
      
      union storage_t {
        bool   t_bool  ; 
        char   t_char  ; //  8 bit int
        short  t_short ; // 16 bit int
        int    t_int   ; // 32 bit int
        long   t_long  ; // 64 bit int
        float  t_float ; // 32 bit real
        double t_double; // 64 bit real
      } storage;
      
      string   t_str8 ;
      string   t_str16;
      dateTime date   ;
      
      int str_length;
      bool _required;
      bool _auto    ;
      bool _primary ;
    };
  }
}


#endif	/* FIELD_H */

