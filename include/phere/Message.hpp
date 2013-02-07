#ifndef PHERE_DEBUG_MESSAGE_HPP
#define PHERE_DEBUG_MESSAGE_HPP

#include <string>

namespace phere
{
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

	enum Facility
	  {
		kern,
		user,
		mail,
		daemon,
		auth,
		syslog,
		lpr,
		news,
		uucp,
		_9,
		authpriv,
		ftp,
		_12,
		_13,
		_14,
		cron,
		local0,
		local1,
		local2,
		local3,
		local4,
		local5,
		local6,
		local7,
	  };

	Message(std::string message_);

	Message(Severity severity_,
			std::string message_);

	Message(Facility facility_,
			Severity severity_,
			std::string message_);

	Facility get_facility() const;
	Severity get_severity() const;
	std::string get_message() const;

	uint8_t get_priority() const;

  private:
	Facility facility;
	Severity severity;
	std::string message;
  };
} // namespace phere

#endif
