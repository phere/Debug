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
#include "phere/Logger.hpp"
#include "phere/Message.hpp"

// system and library headers
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <iostream>

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

  void ConsoleWriter::write_message(Message const& message) const
  {
	  boost::unique_lock<boost::mutex> consoleLock(consoleMutex);
	  std::cerr << message.get_message() << std::endl;
  }
} // namespace phere
