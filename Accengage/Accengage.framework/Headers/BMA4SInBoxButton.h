//
//  BMA4SInBoxButton.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXTERN NSString *const BMA4SInBoxButtonWillInteract;


/**
 Define the structure of a BMA4SInBoxButton object
 */
@interface BMA4SInBoxButton : NSObject

/**
 This property define the title of BMA4SInBoxButton object
 */
@property (nonatomic, readonly) NSString *title;

/** 
 Call 'interact' method on appropriate BMA4SInBoxButton object
 */
-(void)interact;

/**
 Call this method to track the click on the button
 */

- (void)trackClick;

@end
