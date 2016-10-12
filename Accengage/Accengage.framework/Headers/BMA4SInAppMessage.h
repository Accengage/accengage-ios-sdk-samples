//
//  BMA4SInAppMessage.h
//  BMA4SSDK
//
//  Created by Yassir BARCHI on 22/06/2015.
//  Copyright (c) 2015 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewBodyTag;
FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewCloseTag;
FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewBackTag;
FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewForwardTag;
FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewToolbarTag;
FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewActivityTag;
FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewReloadTag;
FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewStopTag;
FOUNDATION_EXTERN NSInteger const BMA4SInAppOverlayViewSafariTag;

typedef void(^BMA4SInAppClickCompletionHandler)(NSString *buttonID);

typedef void(^BMA4SInAppDismissCompletionHandler)();

typedef void(^BMA4SInAppDisplayCompletionHandler)();

@interface BMA4SInAppMessage : NSObject

/**
 *  Returns the in-app message id.
 */
@property (nonatomic, copy, readonly) NSString* messageID;

/**
 *  Returns the in-app message template name.
 */
@property (nonatomic, copy, readonly) NSString* templateNibName;

/**
 *  Returns the in-app message additional display parameters.
 */
@property (nonatomic, copy, readonly) NSDictionary* displayCustomParams;

/**
 *  Returns `YES` if the template is an interstitial, `NO` otherwise.
 */
@property (nonatomic, assign, readonly, getter=isInterstitial) BOOL interstitial;

/**
 *  The block to execute when your custom button is clicked.
 */
@property (nonatomic, copy) BMA4SInAppClickCompletionHandler clickCompletionHandler;

/**
 *  Execute this block to simply dismiss the in-app.
 *
 *  @warning Call it only for the custom dismiss action that is not managed by the SDK.
 */
@property (nonatomic, copy) BMA4SInAppDismissCompletionHandler dismissCompletionHandler;

/**
 *  Execute this block to track manually the in-app display.
 *
 *  @warning Call it only if you manage all the in-app display lifecycle.
 */
@property (nonatomic, copy) BMA4SInAppDisplayCompletionHandler displayCompletionHandler;

@end


@interface BMA4SInAppTextMessage : BMA4SInAppMessage
/**
 *  Returns the text in-app message body.
 */
@property (nonatomic, copy, readonly) NSString* body;

@end

@interface BMA4SInAppWebMessage : BMA4SInAppMessage
/**
 *  Returns the web in-app message url.
 */
@property (nonatomic, strong, readonly) NSURL* url;
@end

