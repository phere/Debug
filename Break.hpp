//
//  Break.hpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Phere Development. All rights reserved.
//


// -------------------
// Define DebugBreak()
//
// This should create a re-usable way to break into the debugger from software
// the option given provides a trade-off between being generally reliable and
// reasonably portable; and not showing up in the stack trace itself.

#if __x86_64__ || __i386__
// resumable x86 interrupt (doesn't show in stack)
#define DebugBreak() asm volatile("int $3\nnop")
#elif __ppc__
// resumable PPC interrupt (untested)
#define DebugBreak() asm volatile("trap")
#elif __arm__ // && !defined(__STDC__)
// arm BKPT instruction is not resumable without special handling
// so don't use it if we can fall back to STDC signals

// arm interrupt; not resumable, handler must call
// SUBS PC,R14_abt,#4
// which I haven't figured out how to get Xcode gdb to do
//	#define DebugBreak() asm volatile("bkpt 0x0000")

#define DebugBreak() \
	do { \
		int signal=SIGINT; \
		int blah=37; \
		asm volatile( \
			"mov r0,%0\n" \
			"mov r1,%1\n" \
			"mov r12,%2\n" \
			"swi 128\n" \
			"nop\n" \
			: \
			:"r"(getpid()),"r"(signal),"r"(blah) \
			:"r12","r0","r1","cc"); \
	} while(0)

#elif __STDC__
// Generic signal-based breakpoint trigger, should be very portable
#define _DEBUG_BREAK_SIGNAL 1
#elif __GNUC__
// generic gcc debug interrupt, never resumable
// has been reported to stop code generation in the current code path
#define DebugBreak() __builtin_trap()
#else
// don't know what to do... please adjust the conditions above
// for your compiler/platform, or pick one of
// #define _DEBUG_BREAK_PTHREAD 1
// #define _DEBUG_BREAK_SIGNAL 1
#error "DebugBreak() is not configured properly"
#endif //

#if _DEBUG_BREAK_PTHREAD || _DEBUG_BREAK_SIGNAL
// The definition of the implementation also uses
namespace phere { namespace debug {
	void DebugBreak();
}}
#define DebugBreak() phere::debug::DebugBreak();
#endif
