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
#include <phere/LogWriters.hpp>

namespace phere {
  class Logger
  {
  public:
	Logger();
	Logger(std::string name_);

	std::string get_name() const;

#define DefineSeverityLogger(severity)									\
	template <typename Format,											\
			  typename ... Args>										\
	void severity(Format&& format, Args&& ... args) const				\
	{																	\
	  phere::Message::Severity s = phere::Message::severity;			\
	  phere::Message message(*this,										\
							 s,											\
							 phere::format(std::forward<Format>(format), \
										   std::forward<Args>(args)...)); \
	  LogWriters::write_all(message);									\
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
	std::string name;
  };
} // namespace phere

#endif
