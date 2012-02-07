//
//  Assert.hpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Asdeq Labs. All rights reserved.
//

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
#if defined(NDEBUG)
#define BOOST_DISABLE_ASSERTS
#endif
// Explicitly disable BOOST_ASSERT if NDEBUG is defined.
// A side effect in Boost 1.48.0 effectively evaluates the expression if
// BOOST_ENABLE_ASSERT_HANDLER is defined, even if the assertion is not
// to be checked.
// We want BOOST_ASSERT to track `assert()` anyway, so this just ensures that.

#import <boost/assert.hpp>

////////
// Define the 'standard' shorthand macros for ASSERT/VERIFY

// ASSERT(expr);
#define ASSERT BOOST_ASSERT
// ASSERT(expr, msg);
#define ASSERT_MSG	BOOST_ASSERT_MSG
// VERIFY(expr);
#define VERIFY BOOST_VERIFY
