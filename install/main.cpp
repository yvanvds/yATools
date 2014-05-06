/* 
 * File:   main.cpp
 * Author: yvan
 *
 * Created on December 7, 2013, 8:33 PM
 */

#include <cstdlib>
#include "system.hpp"

using namespace std;
using namespace at;

void write(const string & message) {
  std::cout << message << endl;
}

int main(int argc, char** argv) {
  config Config(argc, argv);

  Exec("ls");
  
  
  
  return 0;
}

