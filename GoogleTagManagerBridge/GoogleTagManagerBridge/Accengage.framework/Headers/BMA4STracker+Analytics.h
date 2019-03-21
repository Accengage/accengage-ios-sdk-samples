//
//  BMA4STracker+Analytics.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

#import <Accengage/BMA4STracker.h>
/**
 You can track purchase after purchase validation. You have to create one purchase item for each item of the purchase list.
 */
 __attribute__((deprecated("Starting from version 6.0. Use ACCCartItem.")))
@interface BMA4SPurchasedItem : NSObject <NSCoding>

/**
 ID of the product that you want to track (ex: AB310)
 */
@property (nonatomic, strong) NSString *itemId;

/**
  Label of the product that you want to track (ex: Nike)
 */
@property (nonatomic, strong) NSString *label;

/**
 Category of the product that you want to track (ex: Shoes)
 */
@property (nonatomic, strong) NSString *category;

/**
 Price of the product that you want to track (ex: 123.0)
 */
@property (nonatomic, assign) double price;

/**
 Quantity of the product that you want to track (ex: 2)
 */
@property (nonatomic, assign) NSInteger quantity;


/**
 Creates an article that will be track after purchase (see trackPurchaseWithId...).
 Call this class method to create your BMA4SPurchasedItem (Constructor).
 
 Example:
 
    BMA4SPurchasedItem *item = [BMA4SPurchasedItem itemWithId:@"120" label:@"Nike 230"
    category:@"Shoes" price:120.00 quantity:1];
 
 @param itemId ID of the product that you want to track (ex: AB310)
 @param label Label of the product that you want to track (ex: Nike)
 @param category Category of the product that you want to track (ex: Shoes)
 @param price Price of the product that you want to track (ex: 123.0)
 @param quantity Quantity of the product that you want to track (ex: 2)

 */
+(BMA4SPurchasedItem*)itemWithId:(NSString*)itemId label:(NSString*)label category:(NSString*)category price:(double)price quantity:(long)quantity;

@end



// Specialized analytics events
@interface BMA4STracker (Analytics)


/**
 Call this method to track each item added to a cart
 @param cartId The cartID is managed by the developer (case of timeout, he is changed? / you can have 2 cartID in the same app...).
 @param articleId The ID of the article added to cart (ex:AB123).
 @param label The ID of the article added to cart (ex:Nike).
 @param category The category of the article added to cart (ex:shoes).
 @param price The price of the article added to cart (ex:123).
 @param currency The currency of the article added to cart (ex:EUR).
 @param quantity The quantity of the article added to cart (ex:12).
 
    [BMA4STracker trackCartWithId:@"121" modificationWithLabel:@"Nike 420" forArticleWithId:@"445425" category:@"Shoes" 
    price:123.01 currency:@"Eur" quantity:1];
 
 */
+ (void) trackCartWithId:(NSString*)cartId
        forArticleWithId:(NSString*)articleId
                andLabel:(NSString*)label
                category:(NSString*)category
                   price:(double)price
                currency:(NSString*)currency
                quantity:(long)quantity;

// call one of this  method to track purchase

/**
 One of the three method to track Purchase
 @param purchaseId The ID of the purchase.
 @param currency The currency of the article added to cart (ex:EUR).
 @param items NSArray of BMA4SPurchasedItem.
 
    [BMA4STracker trackPurchaseWithId:@"1220564654131" currency:@"EUR"
    items:@[item, item2];
 
 */
+ (void) trackPurchaseWithId:(NSString*)purchaseId
                    currency:(NSString*)currency
                       items:(NSArray*)items;
/**
 One of the three method to track Purchase
 @param purchaseId The ID of the purchase.
 @param currency The currency of the article added to cart (ex:EUR).
 @param totalPrice The price of the purchase.
 
 [BMA4STracker trackPurchaseWithId:@"1220564654131" currency:@"EUR"
 items:@[item, item2];
 
 */
+ (void) trackPurchaseWithId:(NSString*)purchaseId
                    currency:(NSString*)currency
                  totalPrice:(double)totalPrice;

/**
 One of the three method to track Purchase
 @param purchaseId The ID of the purchase.
 @param currency The currency of the article added to cart (ex:EUR).
 @param items NSArray of BMA4SPurchasedItem.
 @param totalPrice The price of the purchase.
 
 [BMA4STracker trackPurchaseWithId:@"1220564654131" currency:@"EUR"
 items:@[item, item2];
 
 */
+ (void) trackPurchaseWithId:(NSString*)purchaseId
                    currency:(NSString*)currency
                       items:(NSArray*)items
                  totalPrice:(double)totalPrice;



/**
 Call this class method to track a lead
 @param label As you want.
 @param value As you want.
 
    [BMA4STracker trackLeadWithLabel:@"Customer registered" value:@"YES"];
 
 */
+ (void) trackLeadWithLabel:(NSString*)label
                      value:(NSString*)value;

@end
