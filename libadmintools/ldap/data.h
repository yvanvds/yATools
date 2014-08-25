/* 
 * File:   data.h
 * Author: yvan
 *
 * Created on January 30, 2014, 11:00 AM
 */

#include <map>
#include <string>

#ifndef DATA_H
#define	DATA_H

namespace y {
  namespace ldap {
    class server;
    
      // type of data
    enum data_type {
      NONE,
      RESULT,
      NEW,
      ADD,
      MODIFY,
      DELETE,
    };

    class data {
    public:
      data() : type(NONE) {}
      data(data_type type) : type(type) {}
      data(const data& orig);

      void setType(data_type type);
      data_type getType();
      void add(const std::string & name, const std::string & value);
      int elms();
      int elms(const std::string & name) const;
      const std::string & getValue(const std::string & name, int index = 0) const;

    private:
      data_type type;
      std::multimap<std::string, std::string> attributes;
      std::string dummy; // to return when asked for non existant value
      
      friend class server;
    };
  }
}

#endif	/* DATA_H */

