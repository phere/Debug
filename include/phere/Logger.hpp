/*
 *  Logger.h
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#ifndef PHERE_DEBUG_LOGGER_HPP
#define PHERE_DEBUG_LOGGER_HPP

#include <string>

#include <boost/noncopyable.hpp>

#include <phere/Format.hpp>
#include <phere/Message.hpp>
#include <phere/LogWriter.hpp>

namespace phere {
  class Logger
  {
  public:
	Logger();
	Logger(std::string name_);

	std::string get_name() const;

#define DefineSeverityLogger(severity)\
	template <typename Format,\
			  typename ... Args>\
	void severity(Format&& format, Args&& ... args) const\
	{\
	  write<Message::Severity::severity>(std::forward<Format>(format),\
										 std::forward<Args>(args)...);\
	}

	DefineSeverityLogger(debug);
	DefineSeverityLogger(info);
	DefineSeverityLogger(notice);
	DefineSeverityLogger(warning);
	DefineSeverityLogger(error);
	DefineSeverityLogger(critical);
	DefineSeverityLogger(alert);
	DefineSeverityLogger(emergency);

#undef DefineSeverityLogger

  private:
	template <Message::Severity severity,
			  typename Format,
			  typename ... Args>
	void write(Format&& format, Args&& ... args) const
	{
	  phere::Message message(severity,
							 phere::format(std::forward<Format>(format),
										   std::forward<Args>(args)...));

	  LogWriter::get().write(*this, message);
	}

	std::string name;
  };
} // namespace phere

#endif
