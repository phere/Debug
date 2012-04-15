/*
 *  Logger.h
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import <string>
#import <boost/noncopyable.hpp>
#import <boost/smart_ptr/shared_ptr.hpp>
#import <boost/format.hpp>

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
				static void ApplyArgs(Formatter& formatter, FirstArg firstArg)
				{
					formatter % firstArg;
				}

				template <typename Formatter, typename FirstArg, typename ... OtherArgs>
				static void ApplyArgs(Formatter& formatter, FirstArg firstArg, OtherArgs ... otherArgs)
				{
					formatter % firstArg;
					ApplyArgs(formatter, otherArgs...);
				}
			};
		public:
			template < typename ... Args >
			static std::string Format(const char* messageFormat, Args ... args)
			{
				boost::format formatter(messageFormat);
				detail::ApplyArgs(formatter, args...);
				return str(formatter);
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
			
			template <typename ... Args>
			void Trace(const char* messageFormat, Args ... args)
			{
				Log<MessageLevel::Trace>(messageFormat, args...);
			}
			
			template <typename ... Args>
			void Message(const char* messageFormat, Args ... args)
			{
				Log<MessageLevel::Message>(messageFormat, args...);
			}
			
			template <typename ... Args>
			void Warning(const char* messageFormat, Args ... args)
			{
				Log<MessageLevel::Warning>(messageFormat, args...);
			}
			
			template <typename ... Args>
			void Error(const char* messageFormat, Args ... args)
			{
				Log<MessageLevel::Error>(messageFormat, args...);
			}
			
		private:
			template <typename Level>
			static bool ShouldShowLevel()
			{
				return Level::value >= Threshold::value;
			}
			
			template
			< typename Level
			, typename ... Args >
			void Log(const char* messageFormat, Args ... args)
			{
				if (ShouldShowLevel<Level>())
				{
					std::string message(Formatter::Format(messageFormat, args...));
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
