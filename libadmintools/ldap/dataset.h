/* 
 * File:   dataset.h
 * Author: yvan
 *
 * Created on January 30, 2014, 10:39 AM
 */

#ifndef DATASET_H
#define	DATASET_H
#include <string>
#include <map>
#include <vector>
#include "data.h"
#include "utils/string.h"

namespace y {
  namespace ldap {


    class dataset {
    public:
      dataset() {}
      dataset(const dataset& orig);

      bool create(const string & filter, const string & directory = string(""));
      bool createFromDN(const string & dn);
      
      int elms();
      data & get(int index = 0);
      data & New(data_type type);

    private:
      string filter;
      string directory;
      std::vector<data> content;
      data dummy;

      friend class server;
    };
  }
}


#endif	/* DATASET_H */

