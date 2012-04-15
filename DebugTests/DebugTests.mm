//
//  DebugTests.m
//  DebugTests
//
//  Created by Rowan James on 15/04/2012.
//  Copyright (c) 2012 Phere Development Pty. Ltd. All rights reserved.
//

#import "DebugTests.h"

#import "Logger.hpp"
#import "ConsoleWriter.hpp"

DefineLogger(DebugTests)

@implementation DebugTests

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testExample
{
	std::string message(phere::debug::Formatter::Format("%1%", "message"));
	std::string expected("message");
	/*STAssertEquals([NSString stringWithUTF8String:expected.c_str()],
				   [NSString stringWithUTF8String:message.c_str()],
				   @"simple message format");*/
	
	logger.Error("whut?");
}

@end
