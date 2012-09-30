//
//  ConsoleWriter.cpp
//  Debug
//
//  Created by Rowan James on 15/04/2012.
//  Copyright 2012 Phere Development Pty. Ltd. All rights reserved.
//

// this class' header
#include "phere/ConsoleWriter.hpp"

// other headers within the project
#include "phere/Logger.hpp"

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
// ConsoleWriter class implementation
template <>
void ConsoleWriter::write<phere::debug::MessageLevel::Trace>(std::string const& message)
{
	lockedWrite(message);
}
template <>
void ConsoleWriter::write<phere::debug::MessageLevel::Message>(std::string const& message)
{
	lockedWrite(message);
}
template <>
void ConsoleWriter::write<phere::debug::MessageLevel::Warning>(std::string const& message)
{
	lockedWrite(message);
}
template <>
void ConsoleWriter::write<phere::debug::MessageLevel::Error>(std::string const& message)
{
	lockedWrite(message);
}
