//
//  Assert.cpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Asdeq Labs. All rights reserved.
//

// this class' header
#import "Assert.hpp"

// other headers within the project

// system and library headers
#import "Break.hpp"
#import "Debug.hpp"
#import "Logger.hpp"
#import "ConsoleWriter.hpp"

//-----------------------------------------------------------------------------
// static code and helpers
DefineLogger(ASSERT_FAILED);

namespace boost {
	void assertion_failed(char const*	expr,
						  char const*	function,
						  char const*	file,
						  long 			line)
	{
		logger.Error("%1%:%2% %3% %4%", file, line, function, expr);
		DebugBreak();
	}
	void assertion_failed_msg(char const*	expr,
							  char const*	msg,
							  char const*	function,
							  char const*	file,
							  long 			line)
	{
		logger.Error("%1%:%2% %3% %4% \"%5%\"", file, line, function, expr, msg);
		DebugBreak();
	}
}
