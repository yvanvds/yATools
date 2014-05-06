#pragma once
/* 
 * File:   process.h
 * Author: yvan
 *
 * Created on December 7, 2013, 8:50 PM
 */

#include <string>
#include <vector>
#include <memory>
#include <boost/process.hpp>

namespace y {
  namespace sys {

    class process {
    public:
        process(const std::string & command);
        process & arg(const std::string & arg);
        process & run(void (*write)(const std::string & message));

        bool success();
        std::string error();

    private:
      boost::filesystem::path command;
      std::vector<std::string> args;

      std::shared_ptr<boost::process::posix::child> child;
      boost::system::error_code errorCode;
      std::shared_ptr<boost::process::posix::pipe> pipe; 
    };

    void stdOut(const std::string & message);
    bool Exec(const std::string & command, void (*write)(const std::string & message) = stdOut);
  }
}