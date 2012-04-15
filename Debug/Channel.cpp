/*
 *  Channel.mm
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#include "Channel.hpp"

namespace phere {
	namespace debug {
		Channel::Channel(const std::string& strName) :
			m_eThreshold(phere::debug::Channel::eError),
			m_strName(strName)
		{}
		
		Channel::~Channel() {}
		
		std::string Channel::GetName() const {
			return m_strName;
		}

		phere::debug::Channel::EMessageLevel Channel::GetThreshold() const {
			return m_eThreshold;
		}
		void Channel::SetThreshold(EMessageLevel eThreshold) {
			m_eThreshold = eThreshold;
		}
		
		void Channel::Message(EMessageLevel eLevel, const char* pszMessage) const {
			if (eLevel >= m_eThreshold)
				ShowMessage(pszMessage, eLevel);
		}
		void Channel::Message(EMessageLevel eLevel, const std::string& strMessage) const {
			if (eLevel >= m_eThreshold)
				ShowMessage(strMessage, eLevel);
		}
	}
}