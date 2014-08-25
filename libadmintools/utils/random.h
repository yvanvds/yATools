/* 
 * File:   random.h
 * Author: yvan
 *
 * Created on August 20, 2014, 1:22 PM
 */

#ifndef RANDOM_H
#define	RANDOM_H
#include <random>

namespace y {
  namespace utils {
    
    class random {
    public:
      random();
      
      int get(int max); // random value from 0 to max (inclusive)
      int get(int min, int max); // random value from min to max (inclusive)
      
    private:
      std::random_device rd;
      std::mt19937 gen;
    };
    
    random & Random();
  }
}


#endif	/* RANDOM_H */

