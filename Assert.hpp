//
//  Assert.hpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Asdeq Labs. All rights reserved.
//


#define BOOST_ENABLE_ASSERT_HANDLER
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
#import <boost/assert.hpp>

// ASSERT(expr);
#define ASSERT BOOST_ASSERT
// ASSERT(expr, msg);
#define ASSERT_MSG	BOOST_ASSERT_MSG
// VERIFY(expr);
#define VERIFY BOOST_VERIFY
