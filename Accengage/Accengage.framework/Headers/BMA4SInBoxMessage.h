//
//  BMA4SInBoxMessage.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accengage/BMA4SInBoxMessageContent.h>

FOUNDATION_EXTERN NSString *const BMA4SInBoxMessageWillDisplay;
FOUNDATION_EXTERN NSString *const BMA4SInBoxMessageWillInteract;

@class BMA4SInBoxMessageContent;
@class BMA4SInBoxMessage;

/**
 *  A block object to be executed as a result of an interaction with message
 *
 *  @param message the message
 *  @param content message content
 */
typedef void (^BMA4SInBoxDisplayHandler)(BMA4SInBoxMessage *message, BMA4SInBoxMessageContent *content);

/**
 Define a BMA4SInBoxMessage object with her properties and method instance
 */
@interface BMA4SInBoxMessage : NSObject

/**
 This property defines the title of BMA4SInBoxMessage object
 */
@property (weak, nonatomic, readonly) NSString *title;

/**
 This property defines the text of BMA4SInBoxMessage object
 */
@property (weak, nonatomic, readonly) NSString *text;

/**
 This property defines the sender of BMA4SInBoxMessage object
 */
@property (weak, nonatomic, readonly) NSString *from;

/**
 This property defines the category of BMA4SInBoxMessage object
 */
@property (weak, nonatomic, readonly) NSString *category;

/**
 This property defines the date when the BMA4SInBoxMessage object was sent
 */
@property (weak, nonatomic, readonly) NSDate *date;

/**
 This property defines the url of the icon who appear in BMA4SInBoxMessage object
 */
@property (weak, nonatomic, readonly) NSString *iconUrl;

/**
 This property defines the custom params of BMA4SInBoxMessage object
 */
@property (weak, nonatomic, readonly) NSDictionary *customParams;

/**
 This property defines if the BMA4SInBoxMessage object is read by the user
 */
@property (nonatomic, readonly) BOOL isRead;

/**
 This property defines if the BMA4SInBoxMessage object is expired
 */
@property (nonatomic, readonly) BOOL isExpired;

/**
 This property defines if the BMA4SInBoxMessage object has been displayed
 */
@property (nonatomic, readonly) BOOL isDisplayed;

/**
 Call message 'interactWithDisplayHandler' method to hand the message to the SDK
 */
-(void)interactWithDisplayHandler:(BMA4SInBoxDisplayHandler)handler;


/**
 Call this method if you want to mark a BMA4SInBoxMessage object as read
 */
-(void)markAsRead;

/**
 Call this method if you want to mark a BMA4SInBoxMessage object as unread
 */
-(void)markAsUnread;

/**
 Call this method if you want to mark a BMA4SInBoxMessage object as displayed
 */

- (void)markAsDisplayed;

/**
 Call this method if you want to mark a BMA4SInBoxMessage object as undisplayed
 */

- (void)markAsUndisplayed;

/**
 Call this method if you want to know if a BMA4SInBoxMessage object was archived
 */
-(BOOL)isArchived;

/**
  Call this method if you want to archive a BMA4SInBoxMessage object. A message archived will be deleted
 */
-(void)archive;

/**
  Call this method if you want to unarchive a BMA4SInBoxMessage object.
 
 A BMA4SInBoxMessage object can't be unarchive if was deleted
 */
-(void)unarchive;

/**
 Call this method to track the display of a BMA4SInBoxMessage object
 */

- (void)trackDisplay;

/**
 Call this method to track the opening of a BMA4SInBoxMessage object
 */

- (void)trackOpening;

@end
