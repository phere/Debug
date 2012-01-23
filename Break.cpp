//
//  Break.cpp
//  OTR Client
//
//  Created by Rowan James on 23/01/12.
//  Copyright 2012 Phere Development. All rights reserved.
//

// this class' header
#import "Break.hpp"


#if _DEBUG_BREAK_PTHREAD
#import <pthread.h>
#endif // _DEBUG_BREAK_PTHREAD

namespace phere {
	namespace debug {
#if _DEBUG_BREAK_PTHREAD
		void DebugBreak() {
			// Stop in the debugger, if we are running under it.
			pthread_kill( pthread_self(), SIGINT );
		}
#elif _DEBUG_BREAK_SIGNAL
		void DebugBreak() {
			raise(SIGINT);
		}
#endif
	}
}
