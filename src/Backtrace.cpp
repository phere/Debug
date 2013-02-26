#include "phere/Backtrace.hpp"

#include <execinfo.h> // backtrace
#include <dlfcn.h> // dladdr
#include <cxxabi.h> // __cxa_demangle

#include <sstream>

namespace phere
{
  std::string backtrace()
  {
	void* callstack[128];
	const int MAX_FRAMES = sizeof(callstack) / sizeof(callstack[0]);

	int frames = ::backtrace(callstack, MAX_FRAMES);
	char** symbols = backtrace_symbols(callstack, frames);
	char buf[1024];
	const int BUF_SIZE = sizeof(buf) / sizeof(buf[0]);

	std::ostringstream trace_buf;
	for (int i = 1; // skip this function
		 i < frames;
		 ++i) {
	  Dl_info info;
	  if (dladdr(callstack[i], &info) && info.dli_sname) {
		char* demangled = nullptr;
		int status = -1;
		if (info.dli_sname[0] == '_') {
		  demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
		}
		snprintf(buf, BUF_SIZE, "%-3d %*p %s + %zd\n",
				 i, int(2 + sizeof(void*) * 2), callstack[i],
				 status == 0 ? demangled :
				 info.dli_sname == 0 ? symbols[i] : info.dli_sname,
				 (char*)callstack[i] - (char*)info.dli_saddr);
		free(demangled);
	  } else {
		snprintf(buf, BUF_SIZE, "%-3d %*p %s\n",
				 i, int(2 + sizeof(void*) * 2), callstack[i], symbols[i]);
	  }
	  trace_buf << buf;
	}
	free(symbols);
	if (frames == MAX_FRAMES) {
	  trace_buf << "[truncated]\n";
	}
	return trace_buf.str();
  }
}
