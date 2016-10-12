//
//  BMA4STracker+Lists.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//
#import <Accengage/BMA4STracker.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Subscription status options
 */
typedef NS_ENUM(NSInteger, BMA4SListSubscriptionStatus) {
  /**
   *  Unknown status
   */
  BMA4SListSubscriptionStatusUnknown,
  /**
   *  Device is subscribed to the list
   */
  BMA4SListSubscriptionStatusSubscribed,
  /**
   *  Device is unsubscripted from the list
   */
  BMA4SListSubscriptionStatusUnsubscribed
};

/**
 *  The BMA4SList class declares the programmatic interface for an object 
 *  that manages static list.
 *
 *  @since Available in SDK 5.4.0 and later
 */
__attribute__((deprecated("Starting from version 6.0. Use ACCList.")))
              
@interface BMA4SList : NSObject <NSCoding>

//------------------------------------------------------------------------------
/** @name Properties */
//------------------------------------------------------------------------------

/**
 *  The list ID
 */
@property (nonatomic, copy) NSString * listId;

/**
 *  The expiration date of the subscription to the list
 */
@property (nonatomic, copy, nullable) NSDate * expirationDate;

/**
 *  The name of the list
 */
@property (nonatomic, copy, readonly, nullable) NSString * name;

/**
 *  The subscription status
 */
@property (nonatomic, assign, readonly) BMA4SListSubscriptionStatus subscriptionStatus;


//------------------------------------------------------------------------------
/** @name Creating and Initializing List */
//------------------------------------------------------------------------------

/**
 *  Returns an BMA4SList object initialized with the given id.
 *
 *  @param arg The list id.
 *
 *  @return An initialized BMA4SList object.
 *
 *  @since Available in SDK 5.4.0 and later
 */
- (instancetype)initWithId:(NSString*)arg;

/**
 *  Returns an BMA4SList object initialized with the given id.
 *
 *  @param arg The list id.
 *
 *  @return An initialized BMA4SList object.
 *
 *  @since Available in SDK 5.4.0 and later
 */
+ (instancetype)listWithId:(NSString*)arg;

/**
 *  Returns an BMA4SList object initialized with the given id and 
 *  the expiration date.
 *
 *  @param arg1 The list id
 *  @param arg2 The expiration date
 *
 *  @return An initialized BMA4SList object.
 *
 *  @since Available in SDK 5.4.0 and later
 */
- (instancetype)initWithId:(NSString*)arg1
            expirationDate:(nullable NSDate*)arg2 NS_DESIGNATED_INITIALIZER;

/**
 *  Returns an BMA4SList object initialized with the given id and
 *  the expiration date.
 *
 *  @param arg1 The list id
 *  @param arg2 The expiration date
 *
 *  @return An initialized BMA4SList object.
 *
 *  @since Available in SDK 5.4.0 and later
 */
+ (instancetype)listWithId:(NSString*)arg1
            expirationDate:(nullable NSDate*)arg2;

@end

@interface BMA4STracker (Lists)

/**
 Subscribe the device to the given lists.

 @param lists The list of the lists to which we want to be subscribed.

 @since Available in SDK 5.4.0 and later

 Example : 
 
      BMA4SList *listA = [BMA4SList listWithId:@"list_A"
                                expirationDate:[NSDate dateWithTimeIntervalSinceNow:365*24*60*60]];

      BMA4SList *listB = [BMA4SList listWithId:@"list_B"];

      [BMA4STracker subscribeToLists:@[listA, listB]];

 */
+ (void) subscribeToLists:(NSArray*)lists;

/**
 Unsubscribe the device from the given lists. 
 
 @param lists The list of the lists from which we want to be unsubscribed.
 
 @since Available in SDK 5.4.0 and later
 
 Example :
 
     BMA4SList *listA = [BMA4SList listWithId:@"list_A"];
 
     BMA4SList *listB = [BMA4SList listWithId:@"list_B"];
 
     [BMA4STracker unsubscribeFromLists:@[listA, listB]];
 
 */
+ (void) unsubscribeFromLists:(NSArray*)lists;

/**
 Get the device's subscription status to the given lists.

 @param lists             The list of the lists for which we want to check the subscription status.
 @param completionHandler The completion handler

 @since Available in SDK 5.4.0 and later
 
 Example :

     BMA4SList *listA = [BMA4SList listWithId:@"list_A"];
 
     BMA4SList *listB = [BMA4SList listWithId:@"list_B"];

     [BMA4STracker getSubscriptionStatusForLists:@[listA, listB]
                               completionHandler:^(id  _Nullable result, NSError * _Nullable error) {
       if (error) {
         NSLog(@"getSubscriptionStatusForLists failed with error %@",error);
       }
       else if (result) {
         for (BMA4SList *list in result) {
           if (list.subscriptionStatus == BMA4SListSubscriptionStatusSubscribed) {
             // Do something ...
           }
           else if (list.subscriptionStatus == BMA4SListSubscriptionStatusUnsubscribed) {
             // Do something ...
           }
         }
        }
      }];
 */
+ (void) getSubscriptionStatusForLists:(NSArray*)lists
                     completionHandler:(void (^)(id _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Get the list of the device's subscriptions.

 @param completionHandler The completion handler
 
 @since Available in SDK 5.4.0 and later
 
 Example :

     [BMA4STracker getListOfSubscriptions:^(id  _Nullable result, NSError * _Nullable error) {
       if (error) {
         NSLog(@"getListOfSubscriptions failed with error %@",error);
       }
       else if (result) {
         for (BMA4SList *list in result) {
           // Do something ...
         }
       }
     }];
 */
+ (void) getListOfSubscriptions:(void (^)(id _Nullable result, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
