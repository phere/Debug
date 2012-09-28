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
#include <iostream>
#include <utility>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/format.hpp>
#include <boost/exception/diagnostic_information.hpp>

#ifdef __OBJC__
@class NSObject;
std::ostream& operator<<(std::ostream& os, NSObject* pObjCObject);
#endif // ifdef __OBJC__

namespace phere {
	namespace debug {
		struct MessageLevel
		{
			template <const int _value> struct MessageLevel_type
			{
				static const int value = _value;
			};
			typedef MessageLevel_type<-1> Trace;
			typedef MessageLevel_type< 0> Message;
			typedef MessageLevel_type< 1> Warning;
			typedef MessageLevel_type< 2> Error;

			// maximum possible level, the threshold for null loggers
			struct MAX
			{
			  static const int value = std::numeric_limits<int>::max();
			};
		};
		
		struct ChannelWriter
		{
			template < typename Level >
			static void write(std::string const& message) {}
		};
		
		class Formatter : protected boost::noncopyable {
		private:
			struct detail
			{
				template <typename Formatter>
				static void ApplyArgs(Formatter&&)
				{} // no args, no-op.
				
				template <typename Formatter, typename FirstArg>
				static void ApplyArgs(Formatter&& formatter,
									  FirstArg&& firstArg)
				{
					formatter % firstArg;
				}

				template <typename Formatter, typename FirstArg, typename ... OtherArgs>
				static void ApplyArgs(Formatter& formatter,
									  FirstArg&& firstArg,
									  OtherArgs&& ... otherArgs)
				{
					formatter % firstArg;
					ApplyArgs(formatter, std::forward<OtherArgs>(otherArgs)...);
				}
			};
		public:
			template <typename FormatType, typename ... Args>
			static std::string Format(FormatType&& messageFormat, Args&& ... args)
			{
				try
				{
					boost::format formatter(std::forward<FormatType>(messageFormat));
					detail::ApplyArgs(formatter, std::forward<Args>(args)...);
					return str(formatter);
				}
				catch (boost::io::format_error& ex)
				{
					std::cerr << ">>>> Error encountered while formatting string for phere::debug::Logger : ";
					std::cerr << boost::current_exception_diagnostic_information() << std::endl;
				}
				return "";
			}
		};
		
		template
		< typename Writer = ChannelWriter
		, typename Threshold = MessageLevel::Warning >
		class Logger
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
			void Trace(FormatType&& messageFormat, Args&& ... args)
			{
				Log<MessageLevel::Trace>(std::forward<FormatType>(messageFormat),
										 std::forward<Args>(args)...);
			}
			
			template <typename FormatType, typename ... Args>
			void Message(FormatType&& messageFormat, Args&& ... args)
			{
				Log<MessageLevel::Message>(std::forward<FormatType>(messageFormat),
										   std::forward<Args>(args)...);
			}
			
			template <typename FormatType, typename ... Args>
			void Warning(FormatType&& messageFormat, Args&& ... args)
			{
				Log<MessageLevel::Warning>(std::forward<FormatType>(messageFormat),
										   std::forward<Args>(args)...);
			}
			
			template <typename FormatType, typename ... Args>
			void Error(FormatType&& messageFormat, Args&& ... args)
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
					std::string message(Formatter::Format(std::forward<FormatType>(messageFormat),
														  std::forward<Args>(args)...));
					Writer::template write<Level>(messagePrefix + message);
				}
			}
			
			std::string messagePrefix;
		};
	}
}

#define DefineNullLogger(logger_name) \
namespace { \
	struct logger_name##_tag{}; \
	phere::debug::Logger< phere::debug::ChannelWriter, phere::debug::MessageLevel::MAX > logger(#logger_name); \
}

#endif