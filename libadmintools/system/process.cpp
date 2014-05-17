/* 
 * File:   process.cpp
 * Author: yvan
 * 
 * Created on December 7, 2013, 8:50 PM
 */

#include "process.h"
#include "workDir.h"
#include <boost/process.hpp>
#include <boost/process/execute.hpp>
#include <boost/asio.hpp>
#include <ios>
#include <boost/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/tokenizer.hpp>
#include "../utils/log.h"

y::sys::process::process(const std::string & command) {
  this->command = boost::process::posix::search_path(command);
  // it looks like the first argument doesn count, so we double the
  // command in there
  args.push_back(this->command.string());
  pipe.reset(new boost::process::posix::pipe(
            boost::process::posix::create_pipe())
  );
}

y::sys::process & y::sys::process::arg(const std::string & arg) {
  args.push_back(arg);
  return *this;
}

y::sys::process & y::sys::process::run(void (*write)(const std::string & message)) { 
  {
    boost::iostreams::file_descriptor_sink sink(pipe->sink, boost::iostreams::close_handle);
    child.reset(
      new boost::process::posix::child(
        boost::process::posix::execute(
          boost::process::initializers::run_exe(command),
          boost::process::initializers::set_args(args),
          boost::process::initializers::set_on_error(errorCode),
          boost::process::initializers::start_in_dir(WorkDir.get()),
          boost::process::initializers::inherit_env(),
          boost::process::initializers::bind_stdout(sink)
        )
      )
    );
  }
  
  boost::iostreams::file_descriptor_source source(pipe->source, boost::iostreams::close_handle);
  boost::iostreams::stream<boost::iostreams::file_descriptor_source> is(source);
  std::string s;
  
  while(std::getline(is, s)) {
    write(s);
  }
  boost::process::posix::wait_for_exit(*child);
  
  return *this;
}

bool y::sys::process::success() {
  return errorCode.value() == 0 ? true : false;
}

std::string y::sys::process::error() {
  return errorCode.message();
}

void y::sys::stdOut(const std::string & message) {
  std::cout << message << std::endl;
}

bool y::sys::Exec(const std::string& command, void (*write)(const std::string & message)) {
  boost::char_separator<char> sep(" ", "", boost::keep_empty_tokens);
  boost::tokenizer<boost::char_separator<char> > tok(command, sep);
  auto i = tok.begin();
  
  process p = process(*i);
  ++i;
  for(; i != tok.end(); ++i) {
    p.arg(*i);
  }
  p.run(write);
  
  if(!p.success()) {
    write(p.error());
    return false;
  }
  
  return true;
}
