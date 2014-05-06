#pragma once
/* 
 * File:   workDir.h
 * Author: yvan
 *
 * Created on December 8, 2013, 2:09 PM
 */

#include <string>
#include <boost/filesystem.hpp>

namespace y {
  namespace sys {
    class workDir {
    public:
      const std::string & get();
      void set(const std::string & path);
    private:
      boost::filesystem::path dir;
    };

    extern workDir WorkDir;
  }
}

