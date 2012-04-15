/*
 *  NullChannel.h
 *  Anathema
 *
 *  Created by Rowan James on 16/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import "Channel.hpp"

namespace phere {
	namespace debug {
		class NullChannel : public phere::debug::Channel {
		public:
			NullChannel(const std::string& strName);
			
		protected:
			void ShowMessage(const std::string&, phere::debug::Channel::EMessageLevel) const;
		};
	}
}
