//
//  Console.cpp
//  Debug
//
//  Created by Rowan James on 15/04/2012.
//  Copyright 2012 Phere Development Pty. Ltd. All rights reserved.
//

// this class' header
#include "phere/Logger/Console.hpp"

// other headers within the project
#include "phere/Logger/Logger.hpp"

// system and library headers
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <iostream>

//-----------------------------------------------------------------------------
// static code and helpers
namespace {
  boost::mutex consoleMutex;
	
  void lockedWrite(const std::string& message)
  {
	boost::unique_lock<boost::mutex> consoleLock(consoleMutex);
	std::cerr << message << std::endl;
  }
}

//-----------------------------------------------------------------------------
// Console class implementation
namespace phere {
  namespace Debug {
	namespace Logger {
	  template <>
	  void Console::write
	  <phere::Debug::MessageLevel::Trace>(std::string const& message)
	  {
		lockedWrite(message);
	  }
	  template <>
	  void Console::write
	  <phere::Debug::MessageLevel::Message>(std::string const& message)
	  {
		lockedWrite(message);
	  }
	  template <>
	  void Console::write
	  <phere::Debug::MessageLevel::Warning>(std::string const& message)
	  {
		lockedWrite(message);
	  }
	  template <>
	  void Console::write
	  <phere::Debug::MessageLevel::Error>(std::string const& message)
	  {
		lockedWrite(message);
	  }
	} // namespace Logger
  } // namespace Debug
} // namespace phere
