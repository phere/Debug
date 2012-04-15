/*
 *  ConsoleChannel.h
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import "Channel.hpp"

#import <boost/thread/mutex.hpp>

namespace phere {
	namespace debug {
		class ConsoleChannel : public phere::debug::Channel {
		public:
			ConsoleChannel(const std::string& strName);

		protected:
			void ShowMessage(const std::string& strMessage, phere::debug::Channel::EMessageLevel eLevel) const;

		private:
			static boost::mutex s_WriteMutex;
		};
	}
}
