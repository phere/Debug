/*
 *  NullChannel.mm
 *  Anathema
 *
 *  Created by Rowan James on 16/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#include "NullChannel.hpp"

namespace phere {
	namespace debug {
		NullChannel::NullChannel(const std::string& strName) :
		phere::debug::Channel(strName)
		{}
		
		void NullChannel::ShowMessage(const std::string&, phere::debug::Channel::EMessageLevel) const {
		}
	}
}
