/*
 *  ConsoleChannel.mm
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#include "ConsoleChannel.hpp"

#import <iostream>
#import <boost/thread/locks.hpp>
#import <boost/format.hpp>


namespace {
	boost::format* s_MessageFormatters[4] = {NULL};
	void __attribute__((constructor)) SetupFormatters() {
		s_MessageFormatters[0] = new boost::format("(--) %1%: %|20t|%2%");
		s_MessageFormatters[1] = new boost::format("(II) %1%: %|20t|%2%");
		s_MessageFormatters[2] = new boost::format("(WW) %1%: %|20t|%2%");
		s_MessageFormatters[3] = new boost::format("(EE) %1%: %|20t|%2%");
	}
}

namespace phere {
	namespace debug {
		boost::mutex ConsoleChannel::s_WriteMutex;
		
		ConsoleChannel::ConsoleChannel(const std::string& strName) :
			phere::debug::Channel(strName)
		{}
		
		void ConsoleChannel::ShowMessage(const std::string& strMessage, phere::debug::Channel::EMessageLevel eLevel) const {
			boost::unique_lock<boost::mutex> oWriteLock(s_WriteMutex);
			assert(eLevel >= 0);
			assert(eLevel < sizeof(s_MessageFormatters) / sizeof(s_MessageFormatters[0]));
			std::cerr << *s_MessageFormatters[eLevel] % GetName() % strMessage << std::endl;
		}
	}
}