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
	void write(Logger const& source,
			   Message const& message) const;

	static LogWriter& get();

  protected:
	LogWriter();

	virtual void write_message(Message const& message) const;
  };
} // namespace phere

#endif
