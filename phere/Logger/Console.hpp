//
//  Console.hpp
//  Debug
//
//  Created by Rowan James on 15/04/2012.
//  Copyright 2012 Phere Development Pty. Ltd. All rights reserved.
//

#ifndef PHERE_DEBUG_LOGGER_CONSOLE_HPP
#define PHERE_DEBUG_LOGGER_CONSOLE_HPP

#include "phere/Logger/Logger.hpp"

namespace phere
{
  namespace Debug
  {
	namespace Logger
	{
	  struct Console
	  {
		template < typename Level >
		static void write(std::string const& message);
	  };
	} // namespace Logger
  } // namespace Debug
} // namespace phere

#endif
