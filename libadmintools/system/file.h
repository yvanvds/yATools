/* 
 * File:   file.h
 * Author: yvan
 *
 * Created on January 3, 2015, 8:24 PM
 */

#ifndef FILE_H
#define	FILE_H

#include <string>

namespace y {
  namespace sys {
    namespace file {
      
      void append(const std::string & file, const std::string & line);
      bool has(const std::string & file, const std::string & token);
    }
  }
}

#endif	/* FILE_H */

