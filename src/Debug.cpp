/*
 *  Debug.mm
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#include "phere/Debug.hpp"

#ifdef __APPLE__
#include <sys/sysctl.h>
#include <unistd.h>
#endif

namespace phere {
  namespace Debug {
    bool IsDebugging() {
      static bool result(detail::IsDebugging());
      return result;
    }
		
    namespace detail {
#ifdef __APPLE__
      bool IsDebugging() {
	int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, getpid () };
	struct kinfo_proc info;
	memset(&info, 0, sizeof(info));
	size_t size = sizeof (info);
	sysctl (mib, sizeof (mib) / sizeof (*mib), &info, &size, NULL, 0);
				
	// We're being debugged if the P_TRACED flag is set.
	return (info.kp_proc.p_flag & P_TRACED) != 0;
      }
#else
      bool IsDebugging() {
	return false;
      }
#endif
    }
  } // namespace Debug
} // namespace phere
