/*
 *  Logger.h
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import <string>
#import <iostream>
#import <boost/noncopyable.hpp>
#import <boost/move/move.hpp>
#import <boost/smart_ptr/shared_ptr.hpp>
#import <boost/format.hpp>
#import <boost/exception/diagnostic_information.hpp>

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
				static const int value = INT_MAX;
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
				static void ApplyArgs(Formatter&)
				{} // no args, no-op.
				
				template <typename Formatter, typename FirstArg>
				static void ApplyArgs(Formatter& formatter, BOOST_FWD_REF(FirstArg) firstArg)
				{
					formatter % firstArg;
				}

				template <typename Formatter, typename FirstArg, typename ... OtherArgs>
				static void ApplyArgs(Formatter& formatter, BOOST_FWD_REF(FirstArg) firstArg, BOOST_FWD_REF(OtherArgs) ... otherArgs)
				{
					formatter % firstArg;
					ApplyArgs(formatter, boost::forward<OtherArgs>(otherArgs)...);
				}
			};
		public:
			template <typename FormatType, typename ... Args>
			static std::string Format(BOOST_FWD_REF(FormatType) messageFormat, BOOST_FWD_REF(Args) ... args)
			{
				try
				{
					boost::format formatter(boost::forward<FormatType>(messageFormat));
					detail::ApplyArgs(formatter, boost::forward<Args>(args)...);
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
				const int PREFIX_LENGTH = 13;
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
			void Traces(BOOST_FWD_REF(FormatType) messageFormat, Args ... args)
			{
				Log<MessageLevel::Trace>(boost::forward<FormatType>(messageFormat), boost::forward<Args>(args)...);
			}
			
			template <typename FormatType, typename ... Args>
			void Message(BOOST_FWD_REF(FormatType) messageFormat, Args ... args)
			{
				Log<MessageLevel::Message>(boost::forward<FormatType>(messageFormat), boost::forward<Args>(args)...);
			}
			
			template <typename FormatType, typename ... Args>
			void Warning(BOOST_FWD_REF(FormatType) messageFormat, Args ... args)
			{
				Log<MessageLevel::Warning>(boost::forward<FormatType>(messageFormat), boost::forward<Args>(args)...);
			}
			
			template <typename FormatType, typename ... Args>
			void Error(BOOST_FWD_REF(FormatType) messageFormat, Args ... args)
			{
				Log<MessageLevel::Error>(boost::forward<FormatType>(messageFormat), boost::forward<Args>(args)...);
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
			void Log(BOOST_FWD_REF(FormatType) messageFormat, Args ... args)
			{
				if (ShouldShowLevel<Level>())
				{
					std::string message(Formatter::Format(boost::forward<FormatType>(messageFormat), boost::forward<Args>(args)...));
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
