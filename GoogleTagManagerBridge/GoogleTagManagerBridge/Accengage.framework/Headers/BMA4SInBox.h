//
//  BMA4SInBox.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accengage/BMA4SInBoxMessage.h>
@class BMA4SInBox;

FOUNDATION_EXTERN NSString *const BMA4SInBoxDataChanged;

 /** 
  * State of the loading 
  */
typedef NS_ENUM(NSUInteger, BMA4SInBoxLoadingResult) {
    /** 
     * Use this type in the class/instance method call to signify the state of the loading: Cancelled
     */
    BMA4SInBoxLoadingResultCancelled,
    /** 
     * Use this type in the class/instance method call to signify the state of the loading: Failed
     */
    BMA4SInBoxLoadingResultFailed,
    /**
     * Use this type in the class/instance method call to signify the state of the loading: Loaded
     */
    BMA4SInBoxLoadingResultLoaded
};

/**
 *  A block object to be executed when the inbox is loaded
 *
 *  @param result loading result
 *  @param inbox  loaded inbox
 */
typedef void(^BMA4SInBoxLoadedWithResult)(BMA4SInBoxLoadingResult result, BMA4SInBox *inbox);

/**
 *  Success block of loading of an inbox message
 *
 *  @param message        loaded message
 *  @param requestedIndex message index
 */
typedef void(^BMA4SInBoxMessageLoaded)(BMA4SInBoxMessage *message, NSUInteger requestedIndex);

/**
 *  Failure block of loading of an inbox message
 *
 *  @param requestedIndex message index
 */
typedef void(^BMA4SInBoxMessageError)(NSUInteger requestedIndex);


/**
 Inbox feature is made to display some delayed messages to your users. These messages can be text, a webpage, a richpush,.. with or without buttons.
 
 These messages and buttons interact directly with Ad4Push SDK. You can for instance send a message with an event button, trigger a URL scheme, or display a banner/interstitial when the user opens a message. This inbox can be used to store push messages received before but not opened by the user. Indeed, with this feature, the user can browse messages you sent to him before if you choose to use it. Inbox can be used as a reminder or as a lite one-way mail client in order to communicate with your clients.
 
 If you want to use this feature, Accengage servers will send all messages information to your app, but you will need to handle yourself the display part
 */
@interface BMA4SInBox : NSObject

/** Call this class method to retrieve the inbox object from device
 @param completionHandler callback for the download result
 */

+ (void)obtainMessagesWithCompletionHandler:(BMA4SInBoxLoadedWithResult)completionHandler;

/** Call this class to retrieve message from inbox object
 @param index Index of message
 @param loaded Return message
 */
-(void)obtainMessageAtIndex:(NSUInteger)index loaded:(BMA4SInBoxMessageLoaded)loaded onError:(BMA4SInBoxMessageError)onError;

/**
 Call this method to retrieve the number of messages contained in the inbox object
 @return Number of message
 */
-(NSUInteger)size;

/**
 Int value that defines the number of unread messages
 */
-(NSUInteger)unreadMessageCount;

//------------------------------------------------------------------------------
/** @name Deprecated */
//------------------------------------------------------------------------------

/** Call this class method to retrieve the inbox object from members/device
 @param ids Array of ids members for which you want the messages. Can be nil
 @param handler Return object InBox in Callback
 @note Please use `[BMA4SInBox obtainMessagesWithCompletionHandler:]`
 */

+(void)obtainMessagesForMembers:(NSArray*)ids withHandler:(BMA4SInBoxLoadedWithResult)handler __attribute__((deprecated("This method is deprecated starting from version 6.1.0. Use [BMA4SInBox obtainMessagesWithCompletionHandler:] instead")));

@end
