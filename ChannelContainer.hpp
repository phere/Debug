/*
 *  ChannelContainer.h
 *  Anathema
 *
 *  Created by Rowan James on 16/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import <string>
#import <boost/noncopyable.hpp>
#import <boost/ptr_container/ptr_map.hpp>

namespace phere {
	namespace debug {
		class Channel;
		class ChannelContainer : protected boost::noncopyable {
		public:
			static Channel& GetChannel(const std::string& strChannelName);
			
		private:
			ChannelContainer();
			Channel& operator[](const std::string& strChannelName);
			typedef boost::ptr_map<std::string, phere::debug::Channel> channels_map_t;
			channels_map_t m_aChannels;
		};
	}
}
