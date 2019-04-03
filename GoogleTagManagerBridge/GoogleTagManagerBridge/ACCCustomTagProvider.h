/*!
 * @file ACCCustomTagProvider.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 */


#import <Foundation/Foundation.h>
#import "Firebase/Firebase.h"
#import "GoogleTagManager/GoogleTagManager.h"

NS_ASSUME_NONNULL_BEGIN

/* Accengage Actions */
FOUNDATION_EXPORT NSString *const ACTION_TRACK_EVENT;
FOUNDATION_EXPORT NSString *const ACTION_TRACK_LEAD;
FOUNDATION_EXPORT NSString *const ACTION_TRACK_ADD_TO_CART;
FOUNDATION_EXPORT NSString *const ACTION_TRACK_PURCHASE;
FOUNDATION_EXPORT NSString *const ACTION_SET_UDI;
FOUNDATION_EXPORT NSString *const ACTION_DELETE_UDI;
FOUNDATION_EXPORT NSString *const ACTION_INCREMENT_UDI;
FOUNDATION_EXPORT NSString *const ACTION_DECREMENT_UDI;

/* Track Event */
FOUNDATION_EXPORT NSString *const KEY_EVENT_ID;

/* Track Lead */
FOUNDATION_EXPORT NSString *const KEY_LEAD_LABEL;
FOUNDATION_EXPORT NSString *const KEY_LEAD_VALUE;

/* Track Add To Cart */
FOUNDATION_EXPORT NSString *const KEY_CART_ID;
FOUNDATION_EXPORT NSString *const KEY_ITEM_ID;
FOUNDATION_EXPORT NSString *const KEY_ITEM_NAME;
FOUNDATION_EXPORT NSString *const KEY_ITEM_CATEGORY;
FOUNDATION_EXPORT NSString *const KEY_ITEM_CURRENCY;
FOUNDATION_EXPORT NSString *const KEY_ITEM_PRICE;
FOUNDATION_EXPORT NSString *const KEY_ITEM_QUANTITY;
FOUNDATION_EXPORT NSString *const KEY_ITEM_BRAND;

/* Track Purchase */
FOUNDATION_EXPORT NSString *const KEY_PURCHASE_ID;
FOUNDATION_EXPORT NSString *const KEY_PURCHASE_CURRENCY;
FOUNDATION_EXPORT NSString *const KEY_PURCHASE_TOTAL_PRICE;
FOUNDATION_EXPORT NSString *const KEY_PURCHASE_ITEMS;

@interface ACCCustomTagProvider : NSObject <TAGCustomFunction>


/**
 Convert date to string format.

 @param date the given NSDate
 @return the formatted data in format string.
 * The used format is "yyyy-MM-dd HH:mm:ss zzz"
 */
+ (NSString *)stringFromDate:(NSDate *)date;


/**
 Serialize a given array of ACCCartItem.

 @param cartItems An array of ACCCartItem.
 @return serialized cartItems.
 */
+ (NSString *)jsonFromCartItems:(NSArray *)cartItems;

@end

NS_ASSUME_NONNULL_END
