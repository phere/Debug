#ifndef PHERE_DEBUG_LOG_WRITERS_HPP
#define PHERE_DEBUG_LOG_WRITERS_HPP

#include <memory>

namespace phere
{
  class LogWriter;
  typedef std::shared_ptr<LogWriter> LogWriterPtr;

  class Message;

  class LogWriters
  {
  public:
	static void write_all(Message const& message);

	static void add(LogWriterPtr writer);
	static void remove(LogWriterPtr writer);
  };
} // namespace phere

#endif
