//
//  Message.cpp
//  Debug
//
//  Created by Rowan James on 7/2/2013.
//  Copyright 2013 Phere Development Pty. Ltd. All rights reserved.
//

// this class' header
#include "phere/Message.hpp"

// other headers within the project
#include "phere/Logger.hpp"

// system and library headers

//-----------------------------------------------------------------------------
// static code and helpers

//-----------------------------------------------------------------------------
// Console class implementation
namespace phere {
  Message::Message(Logger const& logger,
				   Message::Severity severity_,
				   std::string message_)
	: logger_name(logger.get_name())
	, severity(severity_)
	, message(message_)
  {}

  std::string Message::get_logger_name() const
  {
	return logger_name;
  }

  Message::Severity Message::get_severity() const
  {
	return severity;
  }

  std::string Message::get_message() const
  {
	return message;
  }
} // namespace phere
