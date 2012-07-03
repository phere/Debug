//
//  Break.cpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Phere Development. All rights reserved.
//

// this class' header
#import "Break.hpp"

// other headers in this library
#import "Debug.hpp"


//#define _DEBUG_BREAK_PTHREAD
#ifdef _DEBUG_BREAK_PTHREAD
#import <pthread.h>
#endif
#import <unistd.h>

#if !defined(__x86_64__) && !defined(__i386__) && !defined(__ppc__) && \
	!defined(_DEBUG_BREAK_PTHREAD) && !(defined(__GNUC__) && !defined(__STDC__))
#import <signal.h>
#endif

#define _DEBUG_BREAK_ARM_SWI_IMPL \
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

namespace phere {
	namespace debug {
		void _DebugBreak() {
			if (phere::debug::IsDebugging()) {
#if defined(__x86_64__) || defined(__i386__)
				// resumable x86 interrupt (doesn't show in stack)
				asm volatile("int $3\nnop");
#elif defined(__ppc__)
				// resumable PPC interrupt (untested)
				asm volatile("trap");
#elif defined(__arm__)
				// Resumable ARM software interrupt breakpoint
				_DEBUG_BREAK_ARM_SWI_IMPL;
				
				// arm BKPT instruction (below) is not resumable without special handling
				// so don't use it if you can use the software interupt ASM above or STDC signals.
				// handler must call:
				// SUBS PC,R14_abt,#4
				/*	asm volatile("bkpt 0x0000") */
#elif defined(__STDC__)
				// C SIGTRAP signal
				// very portable and quite reliable, but the assembler implementations leave the
				// stack cleaner (ends with this _DebugBreak() function, not some system kill() handler)
				// and don't collide with by other debug code as much (library signal handlers)
				raise(SIGTRAP);
#elif defined(_DEBUG_BREAK_PTHREAD)
				pthread_kill( pthread_self(), SIGINT );
#elif defined(__GNUC__)
#warn "__GNUC__ __builtin_trap() isn't resumable"
				// ... and has been reported to stop code generation on the current path.
				// i.e. *VERY* not resumable.
				// Shouldn't need this, but is included for completeness
				// ( __GNUC__ -> __STDC__, which will use the SIGTRAP impl instead )
				__builtin_trap();
#else
#error "Don't know how to generate a debug break"
#endif
			} // if IsDebugging()
		} // _DebugBreak()
	} // namespace debug
} // namespace phere

#undef _DEBUG_BREAK_ARM_SWI_IMPL
