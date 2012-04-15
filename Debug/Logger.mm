/*
 *  Logger.mm
 *  Anathema
 *
 *  Created by Rowan James on 14/05/11.
 *  Copyright 2011 Phere Development. All rights reserved.
 *
 */

#import "Logger.hpp"

//#ifdef __OJBC__
#import <Foundation/Foundation.h>

std::ostream& operator<<(std::ostream& os, NSObject* pObjCObject) {
	if (pObjCObject == nil) {
		os << "(nil Objective-C pointer)";
	} else {
		os << [[pObjCObject description] UTF8String];
	}
	return os;
}

//#endif // ifdef __OBJC__
