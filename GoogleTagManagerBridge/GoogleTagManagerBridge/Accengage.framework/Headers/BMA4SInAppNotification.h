//
//  BMA4SInAppNotification.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

@protocol BMA4SInAppNotificationDataSource;

FOUNDATION_EXTERN NSString *const BMA4SInAppNotification_Clicked;
FOUNDATION_EXTERN NSString *const BMA4SInAppNotification_DidAppear;
FOUNDATION_EXTERN NSString *const BMA4S_InAppNotification_Closed;
FOUNDATION_EXTERN NSString *const BMA4S_InAppNotification_DataAvailable;
// Key used to store NSData received as an inAppNotification
FOUNDATION_EXTERN NSString *const BMA4S_InAppNotification_DataKey;

/**
 You can use this class to manage inApp notification
 */
@interface BMA4SInAppNotification : NSObject

/**
 You can prevent the display of any inApp notification, by calling this class method.
 This value can be changed at any time.
 @param locked Boolean value:
 
    - YES: if you want to disable inAppNotification
    - NO: to enable inAppNotification

 */
+ (void) setNotificationLock:(BOOL)locked;


/**
 Call this class method to get the status of notificationLock
 @return Return the state of notificationLock
 */
+ (BOOL) notificationLock;

/**
 *  Set the object that acts as position data source of in-app notifications.
 *  The date source must adopt the `BMA4SInAppNotificationDataSource` protocol. The data source is not retained.
 *
 *  @param datasource The object that acts as data source of in-app notifications.
 *  @since Available in SDK 5.2.0 and later.
 *  @see BMA4SInAppNotificationDataSource
 */
+ (void) setDataSource:(id<BMA4SInAppNotificationDataSource>)datasource;

/** ----------------------------------------------------------------------------
 * @name Deprecated
 * -----------------------------------------------------------------------------
 */

/**
 By default, the notifications are displayed at the bottom of the screen in Portrait mode.
 @param position CGPoint value for the position (x,y) of the banner in the screen.
 
 To change this position, you have to call setDefaultBannerOriginForPortrait with the required CGPoint.
 
 [BMA4SInAppNotification setDefaultBannerOriginForPortrait:CGPointMake(0, 200)];
 
 @deprecated in SDK 5.2.0
 
 @since Deprecated in SDK 5.2.0.
 
 @see setDataSource:
 
 @see BMA4SInAppNotificationDataSource
 */
+ (void) setDefaultBannerOriginForPortrait:(CGPoint)position __attribute__((deprecated("This method is deprecated starting from version 5.2.0.")));

/**
 By default, the notifications are displayed at the bottom of the screen in Landscape mode.
 @param position CGPoint value for the position (x,y) of the banner in the screen.
 
 To change this position, you have to call setDefaultBannerOriginForPortrait with the required CGPoint.
 
 [BMA4SInAppNotification setDefaultBannerOriginForLandscape(0, 200)];
 
 @deprecated in SDK 5.2.0
 
 @since Deprecated in SDK 5.2.0.
 
 @see setDataSource:
 
 @see BMA4SInAppNotificationDataSource
 */
+ (void) setDefaultBannerOriginForLandscape:(CGPoint)position __attribute__((deprecated("This method is deprecated starting from version 5.2.0.")));

/**
 Reset the default position of banner in the screen in portrait mode.
 
 @deprecated in SDK 5.2.0
 
 @since Deprecated in SDK 5.2.0.
 
 @see setDataSource:
 
 @see BMA4SInAppNotificationDataSource
 */
+ (void) resetDefaultBannerOriginForPortrait __attribute__((deprecated("This method is deprecated starting from version 5.2.0.")));

/**
 Reset the default position of banner in the screen in landscape mode.
 
 @deprecated in SDK 5.2.0
 
 @since Deprecated in SDK 5.2.0.
 
 @see setDataSource:
 
 @see BMA4SInAppNotificationDataSource
 */
+ (void) resetDefaultBannerOriginForLandscape __attribute__((deprecated("This method is deprecated starting from version 5.2.0.")));

/**
 Change the position of banners in the screen for a given view controller in portrait mode.
 @param position        CGPoint value for the position (x,y) of the banner in the screen.
 @param viewController  the view controller where you want to set a special position for banners
 
 Example : [BMA4SInAppNotification setBannerOriginForPortrait(0, 200) forViewController:self];
 
 @deprecated in SDK 5.2.0
 
 @since Deprecated in SDK 5.2.0.
 
 @see setDataSource:
 
 @see BMA4SInAppNotificationDataSource
 */
+ (void) setBannerOriginForPortrait:(CGPoint)position forViewController:(UIViewController *)viewController __attribute__((deprecated("This method is deprecated starting from version 5.2.0.")));

/**
 Change the position of banners in the screen for a given view controller in landscape mode.
 @param position        CGPoint value for the position (x,y) of the banner in the screen.
 @param viewController  the view controller where you want to set a special position for banners
 
 Example : [BMA4SInAppNotification setBannerOriginForLandscape(0, 200) forViewController:self];
 
 @deprecated in SDK 5.2.0
 
 @since Deprecated in SDK 5.2.0.
 
 @see setDataSource:
 
 @see BMA4SInAppNotificationDataSource
 */
+ (void) setBannerOriginForLandscape:(CGPoint)position forViewController:(UIViewController *)viewController __attribute__((deprecated("This method is deprecated starting from version 5.2.0.")));

/**
 Remove specific position for a given view controller in portrait mode
 @note  After calling this method, banners will appear at the default position you may have set in
 setDefaultBannerOriginForPortrait: or if not, at the bottom of the screen.
 
 @deprecated in SDK 5.2.0
 
 @since Deprecated in SDK 5.2.0.
 
 @see setDataSource:
 
 @see BMA4SInAppNotificationDataSource
 */
+ (void) resetOriginForPortraitForViewController:(UIViewController *)viewController __attribute__((deprecated("This method is deprecated starting from version 5.2.0.")));

/**
 Remove specific position for a given view controller in landscape mode
 @note  After calling this method, banners will appear at the default position you may have set in
 setDefaultBannerOriginForPortrait: or if not, at the bottom of the screen.
 
 @deprecated in SDK 5.2.0
 
 @since Deprecated in SDK 5.2.0.
 
 @see setDataSource:
 
 @see BMA4SInAppNotificationDataSource
 */
+ (void) resetOriginForLandscapeForViewController:(UIViewController *)viewController __attribute__((deprecated("This method is deprecated starting from version 5.2.0.")));

/**
 Set minimum time interval between display of 2 inApp notifications in a session
 
 @param minimumTimeInterval Minimum time interval between display of 2 inApp notifications
 
 @deprecated in SDK 5.2.0
 */
+ (void) setNotificationTimeInterval:(NSTimeInterval)minimumTimeInterval __attribute__((deprecated("This method is deprecated starting from version 5.6.0.")));

@end
