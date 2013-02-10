//
//  Console.cpp
//  Debug
//
//  Created by Rowan James on 15/04/2012.
//  Copyright 2012 Phere Development Pty. Ltd. All rights reserved.
//

// this class' header
#include "phere/ConsoleWriter.hpp"

// other headers within the project
#include "phere/Message.hpp"

// system and library headers
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <iostream>
#include <sstream>

//-----------------------------------------------------------------------------
// static code and helpers
namespace {
  boost::mutex consoleMutex;
}

//-----------------------------------------------------------------------------
// Console class implementation
namespace phere {
  ConsoleWriter::ConsoleWriter()
  {}

  void ConsoleWriter::write(Message const& message) const
  {
	std::ostringstream os;
	os << message.get_severity();
	os << "\t";
	os << message.get_logger_name();
	os << "\t";
	os << message.get_message();
	{
	  boost::unique_lock<boost::mutex> consoleLock(consoleMutex);
	  std::cerr << os.str() << std::endl;
	}
  }
} // namespace phere
