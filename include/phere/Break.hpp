//
//  Break.hpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Phere Development. All rights reserved.
//

#ifndef PHERE_DEBUG_BREAK_HPP
#define PHERE_DEBUG_BREAK_HPP

// -------------------
// Define DebugBreak()
//
// This should create a re-usable way to break into the debugger from software
// the option given provides a trade-off between being generally reliable and
// reasonably portable.
namespace phere { namespace Debug {
	void debugBreak();
}}

#endif
