#include "phere/LogWriter.hpp"

#include "phere/LogWriters.hpp"

namespace phere
{
  LogWriter::~LogWriter()
  {
	LogWriters::remove(this);
  }

  void LogWriter::write(Message const& message) const
  {}
}
