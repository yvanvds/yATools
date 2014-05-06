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

namespace ldp {

  
  class dataset {
  public:
    dataset();
    dataset(const ldp::dataset& orig);

    bool create(const std::string & filter);
    int count();
    data & get(int index = 0);

  private:
    std::string filter;
    std::vector<data> content;
    data dummy;
    
    friend class server;
  };
}


#endif	/* DATASET_H */

