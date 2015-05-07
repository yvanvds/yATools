/* 
 * File:   log.h
 * Author: yvan
 *
 * Created on January 16, 2014, 2:11 PM
 */

#pragma once
#include <string>
#include <fstream>

namespace y {
  namespace utils {

    class log {
    public:
      /**
       * Add a message to the log. This can be console and/or
       * a file.
       * @param message : The message to add
       * @return 
       */
      log & add(const std::wstring & message);

      /**
       * Enable the use of the console for logging
       * @param enable : enable or disable
       * @return 
       */
      log & useConsole(bool enable);

      /**
       * Enable the use of a logfile
       * @param enable : enable or disable
       * @param file   : absolute path to the file used for logging
       * @return 
       */
      log & useFile   (bool enable, const std::string & file = "/var/log/admintools");

      log & useFunction(void (*logFunction)(const std::wstring & message) = nullptr);
      
      log(); 
    private:
      bool _useConsole;
      bool _useFile   ;
      std::string _file;
      std::wofstream _stream;
      void (*_logFunction)(const std::wstring & message);
    };

    // global object (functor)
    log & Log();
  }
}