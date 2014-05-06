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
#include "data.h"

namespace ldp {

  
  class dataset {
  public:
    dataset(const dataset& orig);

    bool create(const std::string & filter);
    int count();
    result & get(int index = 0);

  private:
    std::string filter;
    std::vector<data> datamap;
    static data dummy;
    
    friend class server;
  };
}


#endif	/* DATASET_H */

