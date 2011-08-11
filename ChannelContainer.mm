/*
 *  ChannelContainer.mm
 *  Anathema
 *
 *  Created by Rowan James on 16/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#include "ChannelContainer.hpp"

#import "Channel.hpp"
#import "Debug.hpp"

namespace phere {
	namespace debug {
		Channel& ChannelContainer::GetChannel(const std::string& strChannelName) {
			static ChannelContainer* s_pInstance(NULL);
			if (s_pInstance == NULL) {
				s_pInstance = new ChannelContainer();
			}
			return (*s_pInstance)[strChannelName];
		}
		
		ChannelContainer::ChannelContainer() {}
		
		Channel& ChannelContainer::operator[](const std::string& strChannelName) {
			size_t iCount(m_aChannels.count(strChannelName));
			if (iCount > 0) {
				return m_aChannels.at(strChannelName);
			} else {
				// Create a new log channel to fill the requested slot
				std::auto_ptr<phere::debug::DefaultChannel_t> pNew(new phere::debug::DefaultChannel_t(strChannelName));

#ifndef NDEBUG
				pNew->SetThreshold(phere::debug::Channel::eWarning);
#endif

				// Insert the new channel into the map
				channels_map_t::iterator it(m_aChannels.insert(strChannelName, pNew).first);

				DebugMessage(Channels, "Created logging channel\t\"%1%\"", strChannelName);

				return *(it->second);
			}
		}
	}
}
