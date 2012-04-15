/*
 *  Debug.hpp
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import <string>
#import <ostream>
#import <cxxabi.h>

namespace phere {
	namespace debug {
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

#define TypeName(x) phere::debug::PrettyTypeName<x>()
