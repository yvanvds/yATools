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

namespace ldp {
    // type of data
  enum data_type {
    NONE,
    RESULT,
    ADD,
    MODIFY,
    DELETE,
  };
  
  class data {
  public:
    data() : type(NONE) {}
    data(const data& orig);
    
    void setType(data_type type);
    void add(const std::string & name, const std::string & value);
    int size();
    int nameCount(const std::string & name);
    const std::string & getValue(const std::string & name, int index = 0);
    
  private:
    data_type type;
    std::multimap<std::string, std::string> attributes;
    static std::string dummy; // to return when asked for non existant value
  };
}

#endif	/* DATA_H */

