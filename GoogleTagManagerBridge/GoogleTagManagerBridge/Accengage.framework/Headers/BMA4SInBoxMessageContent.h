//
//  BMA4SInBoxMessageContent.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 Define the type of message
 */
typedef NS_ENUM (NSUInteger, BMA4SMessageContentType){
    /**
     Define the type of message: Text
     */
    BMA4SMessageContentTypeText,
    /**
     Define the type of message: Web
     */
    BMA4SMessageContentTypeWeb
};

/**
 This object represents the content of an InBox message
 */
@interface BMA4SInBoxMessageContent : NSObject

/**
 This property define the type of message (web/text)
 */
@property (nonatomic, assign, readonly) BMA4SMessageContentType type;

/**
 This is the body of the message text
 */
@property (nonatomic, strong, readonly) NSString *body;

/**
 NSArray of buttons who appears on the message
 */
@property (nonatomic, strong, readonly) NSArray *buttons;

@end
