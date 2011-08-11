/*
 *  Debug.hpp
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import "ChannelContainer.hpp"
#import "ConsoleChannel.hpp"

#import <string>
#import <ostream>
#import <cxxabi.h>

namespace phere {
	namespace debug {
		typedef ConsoleChannel DefaultChannel_t;
		
		template<typename T>
		std::string PrettyTypeName() {
			char* pszName;
			int iStatus;
			const std::type_info& oInfo(typeid(T));

			pszName = abi::__cxa_demangle(oInfo.name(), 0, 0, &iStatus);
			std::string strResult(pszName);
			free(pszName);

			return strResult;
		}
	}
}

@class NSObject;
std::ostream& operator<<(std::ostream& os, NSObject* pObjCObject);

#import <boost/format.hpp>
#ifdef INTERNAL
// DebugTrace elements are compiled out completely in release builds
#define DebugTrace(channel, format_str, format_args) \
	if (phere::debug::ChannelContainer::GetChannel(#channel).GetThreshold() >= \
		phere::debug::Channel::eTrace) { \
		phere::debug::ChannelContainer::GetChannel(#channel).Message(phere::debug::Channel::eTrace, \
																	 str(boost::format(format_str) % format_args)); \
	}

#define ShowDebugTraces(channel) \
	phere::debug::ChannelContainer::GetChannel(#channel).SetThreshold(phere::debug::Channel::eTrace);

#else

#define DebugTrace(channel, format_str, format_args)
#define ShowDebugTraces(channel)

#endif

#define DebugMessage(channel, format_str, format_args) \
	if (phere::debug::ChannelContainer::GetChannel(#channel).GetThreshold() >= \
		phere::debug::Channel::eMessage) { \
		phere::debug::ChannelContainer::GetChannel(#channel).Message(phere::debug::Channel::eMessage, \
																	 str(boost::format(format_str) % format_args)); \
	}

#define DebugWarning(channel, format_str, format_args) \
	phere::debug::ChannelContainer::GetChannel(#channel).Message(phere::debug::Channel::eWarning, \
																 str(boost::format(format_str) % format_args));
#define DebugError(channel, format_str, format_args) \
	phere::debug::ChannelContainer::GetChannel(#channel).Message(phere::debug::Channel::eError, \
																 str(boost::format(format_str) % format_args));

#define ShowDebugMessages(channel) \
	phere::debug::ChannelContainer::GetChannel(#channel).SetThreshold(phere::debug::Channel::eMessage);

#define TypeName(x) phere::debug::PrettyTypeName<x>()
