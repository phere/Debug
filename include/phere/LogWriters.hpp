#ifndef PHERE_DEBUG_LOG_WRITERS_HPP
#define PHERE_DEBUG_LOG_WRITERS_HPP

namespace phere
{
  class LogWriter;
  class Message;

  class LogWriters
  {
  public:
	static void write_all(Message const& message);

	static void add(LogWriter* writer);
	static void remove(LogWriter* writer);
  };
} // namespace phere

#endif
