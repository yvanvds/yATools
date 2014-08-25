/* 
 * File:   random.cpp
 * Author: yvan
 * 
 * Created on August 20, 2014, 1:22 PM
 */

#include "random.h"

y::utils::random & y::utils::Random() {
  static random r;
  return r;
}

y::utils::random::random()  {
  gen.seed(rd());
}

int y::utils::random::get(int max) {
  std::uniform_int_distribution<> dis(0, max);
  return dis(gen);
}

int y::utils::random::get(int min, int max) {
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}