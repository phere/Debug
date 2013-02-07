#include "phere/LogWriter.hpp"

#include "phere/Logger.hpp"
#include "phere/ConsoleWriter.hpp"

namespace
{
  phere::LogWriter* s_writer = 0;
}
namespace phere
{
  LogWriter& LogWriter::get()
  {
	if (!s_writer)
	  {
		s_writer = new ConsoleWriter();
	  }
	return *s_writer;
  }

  LogWriter::LogWriter()
  {}

  LogWriter::~LogWriter()
  {}

  void LogWriter::write(Logger const& logger,
						Message const& message) const
  {
	write_message(message);
  }

  void LogWriter::write_message(Message const& message) const
  {
  }
}
