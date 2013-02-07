//
//  ConsoleWriter.hpp
//  Debug
//
//  Created by Rowan James on 15/04/2012.
//  Copyright 2012 Phere Development Pty. Ltd. All rights reserved.
//

#ifndef PHERE_DEBUG_LOG_WRITER_CONSOLE_HPP
#define PHERE_DEBUG_LOG_WRITER_CONSOLE_HPP

#include "phere/LogWriter.hpp"

namespace phere
{
  class ConsoleWriter
	: public phere::LogWriter
  {
  public:
	ConsoleWriter();

  private:
	void write_message(Message const& message) const;
  };
} // namespace phere

#endif
