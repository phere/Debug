//
//  Assert.cpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Asdeq Labs. All rights reserved.
//

// this class' header
#include "phere/Assert.hpp"

// other headers within the project

// system and library headers
#include "phere/Break.hpp"
#include "phere/Debug.hpp"
//#include "phere/Logger/Logger.hpp"
#include "phere/Logger/Console.hpp"

//-----------------------------------------------------------------------------
// static code and helpers
DefineLogger(ASSERT_FAILED);

namespace boost {
	void assertion_failed(char const*	expr,
						  char const*	function,
						  char const*	file,
						  long 			line)
	{
		logger.error("%1%:%2% %3% %4%", file, line, function, expr);
		phere::Debug::debugBreak();
	}
	void assertion_failed_msg(char const*	expr,
							  char const*	msg,
							  char const*	function,
							  char const*	file,
							  long 			line)
	{
		logger.error("%1%:%2% %3% %4% \"%5%\"", file, line, function, expr, msg);
		phere::Debug::debugBreak();
	}
}
