//
//  ConsoleWriter.hpp
//  Debug
//
//  Created by Rowan James on 15/04/2012.
//  Copyright 2012 Phere Development Pty. Ltd. All rights reserved.
//

#import <string>

struct ConsoleWriter
{
	template < typename Level >
	static void write(std::string const& message);
};

#define DefineLogger(logger_name) \
namespace { \
struct logger_name##_tag{}; \
phere::debug::Logger< ConsoleWriter > logger(#logger_name);\
}
