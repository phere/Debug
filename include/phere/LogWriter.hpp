#ifndef PHERE_DEBUG_LOG_WRITER_HPP
#define PHERE_DEBUG_LOG_WRITER_HPP

namespace phere
{
  class Message;
  class Logger;

  class LogWriter
  {
  public:
	virtual ~LogWriter();
	virtual void write(Message const& message) const;
  };
} // namespace phere

#endif
