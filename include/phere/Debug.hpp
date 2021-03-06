/*
 *  Debug.hpp
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#ifndef PHERE_DEBUG_DEBUG_HPP
#define PHERE_DEBUG_DEBUG_HPP

#include <string>
#include <ostream>
#include <cxxabi.h>

namespace phere {
	namespace Debug {
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
		
		namespace detail {
			bool IsDebugging();
		}
		bool IsDebugging(); // caches result of first call to detail::IsDebugging()
	}
}

#endif
