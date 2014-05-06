/* 
 * File:   ldp_data_test.cpp
 * Author: yvan
 *
 * Created on May 5, 2014, 4:53:54 PM
 */

#include <stdlib.h>
#include <iostream>
#include "data.h"

/*
 * Simple C++ Test Suite
 */

void testAdd() {
  const std::string& name;
  const std::string& value;
  ldp::data _data;
  _data.add(name, value);
  if (true /*check result*/) {
    std::cout << "%TEST_FAILED% time=0 testname=testAdd (ldp_data_test) message=error message sample" << std::endl;
  }
}

void testData() {
  const data& orig;
  ldp::data _data(orig);
  if (true /*check result*/) {
    std::cout << "%TEST_FAILED% time=0 testname=testData (ldp_data_test) message=error message sample" << std::endl;
  }
}

void testGetValue() {
  const std::string& name;
  int index;
  ldp::data _data;
  const std::string& result = _data.getValue(name, index);
  if (true /*check result*/) {
    std::cout << "%TEST_FAILED% time=0 testname=testGetValue (ldp_data_test) message=error message sample" << std::endl;
  }
}

void testNameCount() {
  const std::string& name;
  ldp::data _data;
  int result = _data.nameCount(name);
  if (true /*check result*/) {
    std::cout << "%TEST_FAILED% time=0 testname=testNameCount (ldp_data_test) message=error message sample" << std::endl;
  }
}

void testSize() {
  ldp::data _data;
  int result = _data.size();
  if (true /*check result*/) {
    std::cout << "%TEST_FAILED% time=0 testname=testSize (ldp_data_test) message=error message sample" << std::endl;
  }
}

int main(int argc, char** argv) {
  std::cout << "%SUITE_STARTING% ldp_data_test" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% testAdd (ldp_data_test)" << std::endl;
  testAdd();
  std::cout << "%TEST_FINISHED% time=0 testAdd (ldp_data_test)" << std::endl;

  std::cout << "%TEST_STARTED% testData (ldp_data_test)" << std::endl;
  testData();
  std::cout << "%TEST_FINISHED% time=0 testData (ldp_data_test)" << std::endl;

  std::cout << "%TEST_STARTED% testGetValue (ldp_data_test)" << std::endl;
  testGetValue();
  std::cout << "%TEST_FINISHED% time=0 testGetValue (ldp_data_test)" << std::endl;

  std::cout << "%TEST_STARTED% testNameCount (ldp_data_test)" << std::endl;
  testNameCount();
  std::cout << "%TEST_FINISHED% time=0 testNameCount (ldp_data_test)" << std::endl;

  std::cout << "%TEST_STARTED% testSize (ldp_data_test)" << std::endl;
  testSize();
  std::cout << "%TEST_FINISHED% time=0 testSize (ldp_data_test)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}

