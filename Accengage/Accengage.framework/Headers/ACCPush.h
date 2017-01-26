/*!
 * @file ACCPush.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.0.0
 */

#import <Foundation/Foundation.h>
#import <UserNotifications/UserNotifications.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @typedef ACCNotificationOptions
 *
 *  @brief  Notifications authorization options.
 *  @since 6.0.0
 */
typedef NS_OPTIONS(NSUInteger, ACCNotificationOptions) {
    /*! The ability to update the app’s badge. */
    ACCNotificationOptionBadge   = (1 << 0),
    /*! The ability to play sounds. */
    ACCNotificationOptionSound   = (1 << 1),
    /*! The ability to display alerts. */
    ACCNotificationOptionAlert   = (1 << 2),
    /*! The ability to display notifications in a CarPlay environment. */
    ACCNotificationOptionCarPlay = (1 << 3)
};

@protocol ACCPushDelegate;

/*!
 *  @brief Provides an interface the functionality provided by the Accengage iOS Push service.
 *
 *  @author 2010 - present Accengage, Inc. All rights reserved.
 *  @version 6.0.0
 */
@interface ACCPush : NSObject

///-----------------------------------------------------------------------------
/// @name  Properties
///-----------------------------------------------------------------------------


/*!
 *  @brief The current ACCPush service supension status. Defaults to @c NO.
 *  @since 6.0.0
 *
 *  @details If ACCPush service is suspended, it will prevent incoming notification handling.
 */
@property (nonatomic, assign, getter=isSuspended) BOOL suspended;

/*!
 *  @brief The device push token, as a hex string.
 *  @since 6.0.0
 */
@property (nonatomic, readonly, nullable) NSString *deviceToken;

/*!
 *  @brief Set a delegate that implements the ACCPushDelegate protocol.
 *  @since 6.0.0
 */
@property (nonatomic, weak, nullable) id<ACCPushDelegate> delegate;

/*!
 *  @brief The current authorized notification options.
 *  @since 6.0.0
 */
@property (nonatomic, assign, readonly) ACCNotificationOptions authorizedNotificationOptions;


///-----------------------------------------------------------------------------
/// @name  Categories
///-----------------------------------------------------------------------------

/*!
 *  @brief The Accengage default provided categories.
 *  @since 6.0.0
 *
 *  @details Use this set @b only if you want to register for notifications without using
 *  registerForUserNotificationsWithOptions: method.
 *
 *  @see customCategories
 *  @see registerForUserNotificationsWithOptions
 */
@property (nonatomic, readonly) NSSet *accengageCategories;

/*!
 *  @brief Custom notification categories.
 *  @since 6.0.0
 *
 *  @details The custom notification categories you want to use in your app as a parameter.
 *
 *  @note Always set your custom categories set before calling registerForUserNotificationsWithOptions: method.
 *
 *  @see accengageCategories
 *  @see registerForUserNotificationsWithOptions:
 */
@property (nonatomic, copy, nullable) NSSet *customCategories;

///-----------------------------------------------------------------------------
/// @name  Badge Management
///-----------------------------------------------------------------------------

/*!
 *  @brief Allows ACCPush service to reset the application badge to @c 0. Defaults to @ YES.
 *  @since 6.0.0
 *
 *  @details If the badge auto-reset enabled, the ACCPush service will reset the application badge
 *  every time the app is started or foregrounded or received a notification.
 */
@property (nonatomic, assign, getter=isBadgeAutoResetEnabled) BOOL badgeAutoResetEnabled;

/*!
 *  @brief Resets the badge to zero @c 0
 *  @since 6.0.0
 */
- (void)resetBadge;

///-----------------------------------------------------------------------------
/// @name  Registering for User Notifications
///-----------------------------------------------------------------------------

/*!
 *  @brief Notifications registration simplifier.
 *  @since 6.0.0
 *
 *  @details Call this method to initiate the registration process with Apple Push Notification service.
 *  It will request for notifications authorization with the given options and combined set of notification 
 *  categories from customCategories set by the app and the accengageCategories default categories.
 *
 *  @param options The authorization options your app is requesting.
 *
 *  @see accengageCategories
 *  @see customCategories
 */
- (void)registerForUserNotificationsWithOptions:(ACCNotificationOptions)options;

/*!
 *  @brief Posts the token to Accengage servers. 
 *  @since 6.0.0
 * 
 *  @param token A token that identifies the device to APNs.
 °
 *  @details Call it from
 *  @code
 *  - (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
 *
 *      [[Accengage push] didRegisterForUserNotificationsWithDeviceToken:deviceToken];
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (void)didRegisterForUserNotificationsWithDeviceToken:(NSData *)token;

///-----------------------------------------------------------------------------
/// @name  Handling Local & Remote Notifications (iOS 8-9)
///-----------------------------------------------------------------------------

/*!
 *  @brief Handle received remote notification.
 *  @since 6.0.0
 *
 *  @param notification A dictionary that contains information related to the remote notification.
 *
 *  @details Call it from
 *  @code
 *  - (void)application:(UIApplication *)application 
 *          didReceiveRemoteNotification:(NSDictionary *)userInfo 
 *          fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
 *
 *      [[Accengage push] didReceiveRemoteNotification:userInfo];
 *      completionHandler(UIBackgroundFetchResultNoData);
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (void)didReceiveRemoteNotification:(NSDictionary *)notification;

/*!
 *  @brief Handle custom action from remote notification.
 *  @since 6.0.0
 *
 *  @param identifier The identifier associated with the custom action.
 *  @param notification A dictionary that contains information related to the remote notification.
 *
 *  @details Call it from
 *  @code
 *  - (void)application:(UIApplication *)application 
 *          handleActionWithIdentifier:(nullable NSString *)identifier 
 *          forRemoteNotification:(NSDictionary *)userInfo 
 *          completionHandler:(void(^)())completionHandler {
 *
 *      [[Accengage push] handleActionWithIdentifier:identifier forRemoteNotification:userInfo];
 *      completionHandler();
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (void)handleActionWithIdentifier:(NSString *)identifier
             forRemoteNotification:(NSDictionary *)notification;

/*!
 *  @brief Handle custom action from remote notification.
 *  @since 6.0.0
 *
 *  @param identifier The identifier associated with the custom action.
 *  @param notification A dictionary that contains information related to the remote notification.
 *  @param responseInfo The data dictionary sent by the action.
 *
 *  @details Call it from
 *  @code
 *  - (void)application:(UIApplication *)application 
 *          handleActionWithIdentifier:(nullable NSString *)identifier 
 *          forRemoteNotification:(NSDictionary *)userInfo 
 *          withResponseInfo:(NSDictionary *)responseInfo 
 *          completionHandler:(void(^)())completionHandler {
 *
 *      [[Accengage push] handleActionWithIdentifier:identifier forRemoteNotification:userInfo withResponseInfo:responseInfo];
 *      completionHandler();
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (void)handleActionWithIdentifier:(nullable NSString *)identifier
             forRemoteNotification:(NSDictionary *)notification
                  withResponseInfo:(NSDictionary *)responseInfo;

/*!
 *  @brief Handle default action from local notification.
 *  @since 6.0.0
 *
 *  @param notification The received local notification.
 *
 *  @details Call it from
 *  @code
 *  - (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
 *
 *      [[Accengage push] didReceiveLocalNotification:notification];
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (void)didReceiveLocalNotification:(UILocalNotification *)notification;

/*!
 *  @brief Handle custom action from local notification.
 *  @since 6.0.0
 *
 *  @param identifier The identifier associated with the custom action.
 *  @param notification The local notification object that was triggered.
 *
 *  @details Call it from
 *  @code
 *  - (void)application:(UIApplication *)application 
 *          handleActionWithIdentifier:(nullable NSString *)identifier 
 *          forLocalNotification:(UILocalNotification *)notification 
 *          completionHandler:(void(^)())completionHandler {
 *
 *      [[Accengage push] handleActionWithIdentifier:identifier forLocalNotification:notification];
 *      completionHandler();
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (void)handleActionWithIdentifier:(nullable NSString *)identifier
              forLocalNotification:(UILocalNotification *)notification;

/*!
 *  @brief Handle custom action from local notification.
 *  @since 6.0.0
 *
 *  @param identifier The identifier for the custom action.
 *  @param notification The local notification object that was triggered.
 *  @param responseInfo The data dictionary sent by the action.
 *
 *  @details Call it from
 *  @code
 *  - (void)application:(UIApplication *)application
 *          handleActionWithIdentifier:(nullable NSString *)identifier
 *          forLocalNotification:(UILocalNotification *)notification
 *          withResponseInfo:(NSDictionary *)responseInfo
 *          completionHandler:(void(^)())completionHandler {
 *
 *      [[Accengage push] handleActionWithIdentifier:identifier forLocalNotification:notification withResponseInfo:responseInfo];
 *      completionHandler();
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (void)handleActionWithIdentifier:(nullable NSString *)identifier
              forLocalNotification:(UILocalNotification *)notification
                  withResponseInfo:(NSDictionary *)responseInfo;

///-----------------------------------------------------------------------------
/// @name  Handling User Notifications (iOS 10)
///-----------------------------------------------------------------------------

/*!
 *  @brief Called when a notification is delivered to a foreground app.
 *  @since 6.0.0
 *
 *  @param notification The notification that is about to be delivered.
 *
 *  @return a UNNotificationPresentationOptions enum value indicating the presentation options for the notification.
 *
 *  @details Call it from
 *  @code
 *  - (void)userNotificationCenter:(UNUserNotificationCenter *)center 
 *         willPresentNotification:(UNNotification *)notification 
 *           withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler {
 *
 *      completionHandler([[Accengage push] willPresentNotification:notification]);
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (UNNotificationPresentationOptions)willPresentNotification:(UNNotification *)notification __IOS_AVAILABLE(10.0);

/*!
 *  @brief Forwards the response of the notification.
 *  @since 6.0.0
 *
 *  @param response The response of the notification.
 *
 *  @details Call it from
 *  @code
 *  - (void)userNotificationCenter:(UNUserNotificationCenter *)center
 *  didReceiveNotificationResponse:(UNNotificationResponse *)response
 *           withCompletionHandler:(void (^)())completionHandler {
 *
 *      [[Accengage push] didReceiveNotificationResponse:response];
 *      completionHandler();
 *  }
 *  @endcode
 *
 *  @note Call this method @b only if you set @c ACCConfiguration::automaticPushDelegateEnabled to @c NO
 */
- (void)didReceiveNotificationResponse:(UNNotificationResponse *)response __IOS_AVAILABLE(10.0);

///-----------------------------------------------------------------------------
/// @name  Helpers
///-----------------------------------------------------------------------------

/*!
 *  @brief Checks if the given notigation was provided by Accengage.
 *  @since 6.0.0
 *
 *  @param notification The received notification.
 *
 *  @return @c YES if the given notification was provided by Accengage.
 */
- (BOOL)isAccengageNotification:(id)notification;

///-----------------------------------------------------------------------------
/// @name  Factory Methods
///-----------------------------------------------------------------------------

/*!
 *  @brief Initializes a new instance.
 *  @warning This method is unavaialble. Please use @c Accengage::push.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 *  @brief Allocates memory and initializes a new instance into it.
 *  @warning This method is unavaialble. Please use @c Accengage::push.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

@protocol ACCPushDelegate <NSObject>

@optional
/*!
 *  @brief Called when your app has received a remote notification sended by our platform.
 *  @since 6.0.0
 *
 *  @param notifId The identifier of the notification
 *  @param params  The additional parameters
 *
 *  @note This method is called only if the application is in forgeround.
 */
- (void)didReceiveNotificationWithId:(NSString *)notifId
                          parameters:(NSDictionary *)params;

/*!
 *  @brief Called when the user has clicked on remote notification.
 *  @since 6.0.0
 *
 *  @param notifId The identifier of the notification
 *  @param params  The additional parameters
 */
- (void)didOpenNotificationWithId:(NSString *)notifId
                       parameters:(NSDictionary *)params;

/*!
 *  @brief Called when the user taps an action button in an alert displayed
 *  in response to a remote notification.
 *  @since 6.0.0
 *
 *  @param actionId The identifier associated with the custom action.
 *  @param notifId  The identifier of the notification
 *  @param params1  The additional parameters associated with the notification
 *  @param params2  The additional parameters associated with the action
 */
- (void)didClickOnActionWithIdentifier:(NSString *)actionId
           forRemoteNotificationWithId:(NSString *)notifId
                notificationParameters:(NSDictionary *)params1
                      actionParameters:(NSDictionary *)params2;

@end

NS_ASSUME_NONNULL_END
