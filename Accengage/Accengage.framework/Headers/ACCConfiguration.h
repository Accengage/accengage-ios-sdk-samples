/*!
 * @file ACCConfiguration.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.0.0
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! The Accengage SDK default session timeout. 5 minutes.*/
FOUNDATION_EXTERN NSTimeInterval const ACCConfigDefaultSessionTimeout;

/*! The Accengage SDK default flush interval for pending requests. */
FOUNDATION_EXTERN NSTimeInterval const ACCConfigDefaultPendingRequestsFlushInterval;

/*!
 *  @typedef ACCConfigTrackingMode
 *
 *  @brief  Accengage tracking mode options.
 *  @since 6.0.0
 */
typedef NS_ENUM(NSUInteger, ACCConfigTrackingMode) {
    /*! Default */
    ACCConfigTrackingModeDefault = 0,
    
    /*! Restricted, more respectful of user's privacy. */
    ACCConfigTrackingModeRestricted = 1
};


/*!
 *  @brief The @c ACCConfiguration object allows you to start Accengage services with a custom configuration.
 *  @since 6.0.0
 *
 *  @details The @c ACCConfiguration object provides an interface for passing common configurable
 *  values to @c Accengage::startWithConfig:. @n
 *  You can simply add an @c AccengageConfig.plist file in your app's bundle and set the desired options.
 *  The plist keys use the same names as the properties of this class.
 */
@interface ACCConfiguration : NSObject <NSCopying>

///-----------------------------------------------------------------------------
/// @name  Properties
///-----------------------------------------------------------------------------

/*!
 *  @brief  Accengage app ID.
 *  @since 6.0.0
 */
@property (nonatomic, copy) NSString *appId;

/*!
 *  @brief  Accengage app private key.
 *  @since 6.0.0
 */
@property (nonatomic, copy) NSString *appPrivateKey;

/*!
 *  @brief  Allow the choice of tracking mode. Default is @c ACCConfigTrackingModeDefault.
 *  @since 6.0.0
 *
 *  @note Note that if you use the @c ACCConfigTrackingModeRestricted, some advanced 
 *  targeting functionalities may not be available. This is not needed for most integrations.
 */
@property (nonatomic, assign) ACCConfigTrackingMode trackingMode;

/*!
 *  @brief Allow collection of IDFA and related fields if set to @c YES. Default is @c YES.
 *  @since 6.0.0
 */
@property (nonatomic, assign, getter=isIDFACollectionEnabled) BOOL IDFACollectionEnabled;

/*!
 *  @brief Allow Accengage SDK to automatically intercept notification-related app delegate calls. Default is @c YES.
 *  @since 6.0.0
 *
 *  @details If enabled, the Accengage SDK will automatically intercepts all notification-related app delegate calls. @n
 *  Defaults to @c YES. If this is disabled, you will forward all notification-related app delegate
 *  calls to Accengage.
 */
@property (nonatomic, assign, getter=isAutomaticPushDelegateEnabled) BOOL automaticPushDelegateEnabled;

/*!
 *  @brief The time interval after which an Accengage session expires
 *  @since 6.0
 *
 *  @details The Accengage SDK provides automated session management. 
 *  This value indicates how long, in seconds, the app may be in the
 *  background before starting a new session upon resume.
 *  A default implementation has a session timeout period of @c 5 @c minutes. @n
 *  If the app remains in the background for longer than the session timeout period,
 *  the next time it's opened a new session will be started.
 *
 *  @warning The value @b must be positive, otherwise the SDK will use the @c ACCConfigDefaultSessionTimeout value.
 *
 *  @see @c ACCConfigDefaultSessionTimeout
 */
@property (nonatomic, assign) NSTimeInterval sessionTimeout;

/*!
 *  @brief Controls the interval at which pending common requests are sent. Default is @c 10s.
 *  @since 6.0
 *
 *  @note Some services (like In-App) will flush the pending requests queue immediately if needed.
 *
 *  @warning The value @b must be positive, otherwise the SDK will use the @c ACCConfigDefaultPendingRequestsFlushInterval value.
 *
 *  @see @c ACCConfigDefaultPendingRequestsFlushInterval
 */
@property (nonatomic, assign) NSTimeInterval pendingRequestsFlushInterval;

/*!
 *  @brief The custom @c JavaScript URL @c used for @c WebView tracking.
 *  @since 6.0
 *
 *  @warning Use it only if you <b>really really really know what you're doing</b>.
 */
@property (nonatomic, copy, nullable) NSString *webTrackingJSURL;

///-----------------------------------------------------------------------------
/// @name  Factory Methods
///-----------------------------------------------------------------------------

/*!
 *  @brief Creates configuration with default/empty values.
 *  @since 6.0.0
 *
 *  @return Configuration with default/empty values.
 *
 *  @see defaultConfig
 */
+ (instancetype)config;

/*!
 *  @brief Creates configuration using the values set in the @c AccengageConfig.plist file.
 *  @since 6.0.0
 *
 *  @return Cconfiguration with @c AccengageConfig.plist file values.
 *
 *  @see config
 */
+ (instancetype)defaultConfig;

///-----------------------------------------------------------------------------
/// @name  Helpers
///-----------------------------------------------------------------------------

/*!
 *  @brief Validates the current configuration and logs warnings and common configuration errors.
 *  @since 6.0.0
 *
 *  @return @c YES if the current configuration is valid, otherwise @c NO.
 */
- (BOOL)isValid;
@end

NS_ASSUME_NONNULL_END
