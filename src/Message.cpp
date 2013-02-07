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

// system and library headers

//-----------------------------------------------------------------------------
// static code and helpers

//-----------------------------------------------------------------------------
// Console class implementation
namespace phere {
  Message::Message(std::string message_)
	: facility(Facility::user)
	, severity(Severity::debug)
	, message(message)
  {}

  Message::Message(Message::Severity severity_,
				   std::string message_)
	: facility(Facility::user)
	, severity(severity_)
	, message(message_)
  {}

  Message::Message(Message::Facility facility_,
				   Message::Severity severity_,
				   std::string message_)
	: facility(facility_)
	, severity(severity_)
	, message(message_)
  {}

  Message::Facility Message::get_facility() const
  {
	return facility;
  }

  Message::Severity Message::get_severity() const
  {
	return severity;
  }

  std::string Message::get_message() const
  {
	return message;
  }

  uint8_t Message::get_priority() const
  {
	return facility * 8 + severity;
  }
} // namespace phere
