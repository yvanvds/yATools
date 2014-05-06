#pragma once
/* 
 * File:   config.h
 * Author: yvan
 *
 * Created on December 8, 2013, 9:45 PM
 */

#include <boost/program_options.hpp>

namespace y {
  namespace sys {
    class config {
    public:
      config(int argc, char** argv);

    private:
      boost::program_options::options_description general;
      boost::program_options::variables_map map;
    };

  }
}



