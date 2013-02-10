#ifndef PHERE_DEBUG_MESSAGE_HPP
#define PHERE_DEBUG_MESSAGE_HPP

#include <string>

namespace phere
{
  class Logger;
  class Message
  {
  public:
	enum Severity
	  {
		debug,
		info,
		notice,
		warning,
		error,
		critical,
		alert,
		emergency,
	  };

	Message(Logger const& logger,
			Severity severity_,
			std::string message_);

	std::string get_logger_name() const;
	Severity get_severity() const;
	std::string get_message() const;

  private:
	std::string logger_name;
	Severity severity;
	std::string message;
  };
} // namespace phere

#endif
