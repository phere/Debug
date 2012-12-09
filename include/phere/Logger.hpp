/*
 *  Logger.h
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#ifndef PHERE_DEBUG_LOGGER_LOGGER_HPP
#define PHERE_DEBUG_LOGGER_LOGGER_HPP

#include <string>
#include <iostream>
#include <utility>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <phere/Format.hpp>

namespace phere {
  namespace Debug {
    struct MessageLevel
    {
	  struct Trace { static const int value = -1; };
	  struct Message { static const int value = 0; };
	  struct Warning { static const int value = 1; };
	  struct Error { static const int value = 2; };
    };

    struct NullWriter
    {
      template < typename Level >
      static void write(std::string const& message) {}
    };

	template
	< typename Writer = NullWriter
	  , typename Threshold = MessageLevel::Trace >
	class Logger
	  : protected boost::noncopyable
	{
	public:
	  Logger(const std::string& _name)
		: messagePrefix(_name)
	  {
		const size_t PREFIX_LENGTH = 13;
		// too short, add spaces
		if (messagePrefix.length() < PREFIX_LENGTH)
		  {
			messagePrefix = messagePrefix +
			  std::string(PREFIX_LENGTH - messagePrefix.length(), ' ');
		  }
		// too long, truncate
		if (messagePrefix.length() > PREFIX_LENGTH - 1)
		  {
			messagePrefix = messagePrefix.substr(0, PREFIX_LENGTH);
		  }
		messagePrefix = messagePrefix + ": ";
	  }
			
	  template <typename FormatType, typename ... Args>
	  void trace(FormatType&& messageFormat, Args&& ... args)
	  {
		Log<MessageLevel::Trace>(std::forward<FormatType>(messageFormat),
								 std::forward<Args>(args)...);
	  }
			
	  template <typename FormatType, typename ... Args>
	  void message(FormatType&& messageFormat, Args&& ... args)
	  {
		Log<MessageLevel::Message>(std::forward<FormatType>(messageFormat),
								   std::forward<Args>(args)...);
	  }
			
	  template <typename FormatType, typename ... Args>
	  void warning(FormatType&& messageFormat, Args&& ... args)
	  {
		Log<MessageLevel::Warning>(std::forward<FormatType>(messageFormat),
								   std::forward<Args>(args)...);
	  }
			
	  template <typename FormatType, typename ... Args>
	  void error(FormatType&& messageFormat, Args&& ... args)
	  {
		Log<MessageLevel::Error>(std::forward<FormatType>(messageFormat),
								 std::forward<Args>(args)...);
	  }
			
	private:
	  template <typename Level>
	  static bool ShouldShowLevel()
	  {
		return Level::value >= Threshold::value;
	  }
			
	  template
	  < typename Level
		, typename FormatType
		, typename ... Args >
	  void Log(FormatType&& messageFormat, Args&& ... args)
	  {
		if (ShouldShowLevel<Level>())
		  {
			std::string message(phere::Format::format(std::forward<FormatType>(messageFormat),
													  std::forward<Args>(args)...));
			Writer::template write<Level>(messagePrefix + message);
		  }
	  }
			
	  std::string messagePrefix;
	};
  } // namespace Debug
} // namespace phere

#endif
