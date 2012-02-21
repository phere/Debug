//
//  Assert.hpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Asdeq Labs. All rights reserved.
//

/*
 Define macros for testing precondition and postcondition violations.
 
 ASSERT( expr )
 ASSERT( expr, message )
 Unless NDEBUG is defined, expr is evaluated.
 
 VERIFY( expr )
 Always evaluate expr.
 
 --
  
 When expr is evaluated; if the result is:
 -	true
 	no action is taken
 
 -	false
 	1. a message is logged with DebugError( )
 	2. if the program is being debugged
 		a) the program is paused in the debugger


 Note that even after a failed ASSERT, the program continues execution.
 This is in voiolation of most expectaitons of ASSERT.  It is common to
 find code such as:
 ASSERT(pointer != NULL);
 return pointer->member;
 
 Using these assert maros in cases such as this will result in a message
 being logged, followed by a segmentation violation or other serious error.
 
 Future development may provide a build-time configuration option to select:
 * continue (as-is)
 * call std::terminate()
 * some some std::exception
 
 Further, a 'less-serious' CHECK( ) macro may be given for the existing
 behaviour.
 
 */

////////
namespace boost {
	void assertion_failed(char const*	expr,
						  char const*	function,
						  char const*	file,
						  long 			line);
	void assertion_failed_msg(char const*	expr,
							  char const*	msg,
							  char const*	function,
							  char const*	file,
							  long 			line);
}

////////
#define BOOST_ENABLE_ASSERT_HANDLER
// This does not enable BOOST_ASSERT et. al., but rather directs it to call
// ::boost::asertion_failed( ... ) declared above instead of `abort()`
// This must be defined before <boost/assert.hpp> is included to take effect.
// Do keep in mind that returning from assertion_failed is likely to result
// in effects like getting SIGSEGV instead of SIGABRT.

////////
// Explicitly disable BOOST_ASSERT if NDEBUG is defined.
// A side effect in Boost 1.48.0 effectively evaluates the expression if
// BOOST_ENABLE_ASSERT_HANDLER is defined, even if the assertion is not
// to be checked
// We want BOOST_ASSERT to track `assert()` anyway, so this just ensures that.
#if defined(NDEBUG)
#define BOOST_DISABLE_ASSERTS
#endif


/////////
// Now that the preprocessor is correctly configured, include the
// library definitions
#import <boost/assert.hpp>
#import <cassert>
// don't use the default 'assert'
#undef assert

////////
// Define the 'standard' shorthand macros for ASSERT/VERIFY

// ASSERT(expr);
#define assert BOOST_ASSERT
#define ASSERT BOOST_ASSERT
// ASSERT(expr, msg);
#define ASSERT_MSG	BOOST_ASSERT_MSG
// VERIFY(expr);
#define VERIFY BOOST_VERIFY
