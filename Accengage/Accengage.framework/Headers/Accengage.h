/*!
 * @file Accengage.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.0.0
 */

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

//! Project version number for Accengage.
FOUNDATION_EXPORT double AccengageVersionNumber;

//! Project version string for Accengage.
FOUNDATION_EXPORT const unsigned char AccengageVersionString[];

#import <Accengage/ACCList.h>
#import <Accengage/ACCPush.h>
#import <Accengage/ACCCartItem.h>
#import <Accengage/ACCConfiguration.h>
#import <Accengage/ACCWKWebView.h>
#import <Accengage/UIViewController+Accengage.h>

/**
 * Old Headers
 */
#import <Accengage/A4SWebView.h>
#import <Accengage/BMA4SInAppView.h>
#import <Accengage/BMA4SInAppMessage.h>
#import <Accengage/BMA4SInAppNotification.h>
#import <Accengage/BMA4SInAppNotificationDataSource.h>
#import <Accengage/BMA4SInBox.h>
#import <Accengage/BMA4SInBoxButton.h>
#import <Accengage/BMA4SInBoxMessage.h>
#import <Accengage/BMA4SInBoxMessageContent.h>
#import <Accengage/BMA4SNotification.h>
#import <Accengage/BMA4STracker.h>
#import <Accengage/BMA4STracker+Analytics.h>
#import <Accengage/BMA4STracker+Lists.h>
#import <Accengage/BMA4SBeaconsService.h>
#import <Accengage/BMA4SLocationServices.h>

NS_ASSUME_NONNULL_BEGIN

/*! The startWithConfig: method must be called on the main thread. */
FOUNDATION_EXPORT NSString *const ACCStartMainThreadException;

typedef NS_ENUM(NSUInteger, ACCWebViewTrackingFramework) {
    ACCUIWebViewFramework,
    ACCWKWebViewFramework
};

/*!
 *  @brief Provides all Accengage available services and methods.
 *
 *  @details Accengage::startWithConfig: should be called from within your @n
 *  application delegate's @c didFinishLaunchingWithOptions: method to initialize and setup all services.
 *
 *  @note For information on how to use Accengage framework see <a href="http://docs.accengage.com/display/IOS/iOS">The online documentation</a>.
 *
 *  @author 2010 - present Accengage, Inc. All rights reserved.
 *  @version 6.0.0
 */
@interface Accengage : NSObject

///-----------------------------------------------------------------------------
/// @name  Properties
///-----------------------------------------------------------------------------

/*!
 *  @brief The application configuration.
 *  @since 6.0.0
 */
@property (nonatomic, nullable, readonly) ACCConfiguration *config;

/*!
 *  @brief  Accengage internal device ID
 *  @since 6.0.0
 */
@property (nonatomic, nullable, readonly) NSString *accengageId;

///-----------------------------------------------------------------------------
/// @name Shared Instances
///-----------------------------------------------------------------------------

/*!
 *  @brief Returns the @c Accengage instance.
 *  @since 6.0.0
 *
 *  @return The @c Accengage instance.
 */
+ (nullable instancetype)shared;

/*!
 *  @brief Returns the shared @c ACCPush instance.
 *  @since 6.0.0
 *
 *  @return The shared @c ACCPush instance.
 */
+ (ACCPush *)push;

///-----------------------------------------------------------------------------
/// @name Lifecycle
///-----------------------------------------------------------------------------

/*!
 *  @brief Simplified @c startWithConfig: method that uses @c ACCConfiguration::defaultConfig for initialization.
 *  @since 6.0.0
 *
 *  @code
 *  - (BOOL)application:(UIApplication *)application
 *          didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
 *
 *     [Accengage start];
 *  }
 *  @endcode
 *
 *  @see startWithConfig:
 */
+ (void)start;

/*!
 *  @brief Initializes and starts all @c Accengage services and performs all necessary setup.
 *  @since 6.0.0
 *
 *  @details This method serves as the entry point to @c Accengage services. It @b must be
 *  called in the scope of @c applicationDidFinishLaunching method, and it may be called only once.
 *  @code
 *  - (BOOL)application:(UIApplication *)application
 *          didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
 *     
 *     ACCConfiguration *config = [ACCConfiguration defaultConfig]; // [ACCConfiguration config];
 *     // Edit some config properties if needed
 *     // config.IDFACollectionEnabled = NO;
 *     
 *     [Accengage startWithConfig:config];
 *  }
 *  @endcode
 *
 *  @warning This method @b must be called on the @b main @b thread. Otherwise it will throw
 *  an exception.
 *
 *  @throw ACCStartMainThreadException
 *
 *  @see start
 *
 *  @param config The configuration to use.
 */
+ (void)startWithConfig:(ACCConfiguration *)config;

/*!
 *  @brief Suspends or resumes all Accengage services.
 *  @since 6.0.0
 *
 *  @details The suspension is persistent. If you suspend all the activities
 *  in session A, the suspension will be kept in session B even if the app was relaunched.
 *
 *  To terminate the suspension, you must call:
 *  @code
 *    [Accengage suspendAllServices:NO];
 *  @endcode
 *
 *  @see isSuspended
 *
 *  @param suspended If @c YES, all Accengage services will be stopped.
 */
+ (void)suspendAllServices:(BOOL)suspended;

/*!
 *  @brief Checks if all services are suspended and returns the status.
 *  @since 6.0.0
 *
 *  @see suspendAllServices:
 *
 *  @return @c YES if Accengage services are suspended.
 */
+ (BOOL)isSuspended;

///-----------------------------------------------------------------------------
/// @name Logging
///-----------------------------------------------------------------------------

/*!
 *  @brief Enables or disables logging. Logging is disabled by default.
 *  @since 6.0.0
 *
 *  @param enabled If @c YES, console logging is enabled.
 */
+ (void)setLoggingEnabled:(BOOL)enabled;

///-----------------------------------------------------------------------------
/// @name Network
///-----------------------------------------------------------------------------

/*!
 *  @brief Enables or disables the network calls.
 *  @since 6.0.0
 *
 *  @see areNetworkCallsDisabled
 *
 *  @param enabled If @c YES, all requests managed by @c Accengage services will be disabled.
 */
+ (void)setNetworkCallsDisabled:(BOOL)enabled;

/*!
 *  @brief Returns @c YES if @c Accengage requests are disabled.
 *  @since 6.0.0
 *
 *  @see setNetworkCallsDisabled:
 *
 *  @return @c YES if @c Accengage requests are disabled.
 */
+ (BOOL)areNetworkCallsDisabled;

///-----------------------------------------------------------------------------
/// @name Device Fields
///-----------------------------------------------------------------------------

/*!
 *  @brief Synchronizes new value of the device profile.
 *  @since 6.0.0
 *
 *  @see normalizedStringForDate:
 *
 *  @param fields The @c NSDictionary with values that you want to synchronize.
 */
+ (void)updateDeviceInfo:(NSDictionary<NSString *, NSString *> *)fields;

///-----------------------------------------------------------------------------
/// @name Track Events
///-----------------------------------------------------------------------------

/*!
 *  @brief Track an simple event with a type.
 *  @since 6.0.0
 *
 *  @param eventType   The type of the event to record. The event type is a @c NSUInteger. @n
 *  The values below @c 1000 are reserved for Accengage internal usage. You can use custom event type starting from @c 1001.
 */
+ (void)trackEvent:(NSUInteger)eventType;

/*!
 *  @brief Tracks an event with a type and a and a list of NSString parameters.
 *  @since 6.0.0
 *
 *  @param eventType   The type of the event to record. The event type is a @c NSUInteger. @n
 *  The values below @c 1000 are reserved for Accengage internal usage. You can use custom event type starting from @c 1001.
 *
 *  @param parameters  Arbitrary parameter array of characteristics. The values are expected to be @c NSString
 */
+ (void)trackEvent:(NSUInteger)eventType
    withParameters:(NSArray<NSString *>  *)parameters;

/*!
 *  @brief Tracks a purchase of the specified amount and items, in the specified currency.
 *  @since 6.0.0
 *
 *  @warning @c purchaseAmount and @c purchasedItems @b mustn't be @c nil at the same time.
 *
 *  @param purchaseId      The purchase's identifier.
 *
 *  @param currency        Currency, is denoted as, e.g. "USD", "EUR", "GBP".  See ISO-4217 for @n
 *  specific values.  One reference for these is <http://en.wikipedia.org/wiki/ISO_4217> or @c [NSLocale ISOCurrencyCodes].
 *
 *  @param purchasedItems  An array of the purchased items.
 *
 *  @param purchaseAmount  The purchase amount, as expressed in the specified currency.
 */
+ (void)trackPurchase:(NSString *)purchaseId
             currency:(NSString *)currency
                items:(nullable NSArray<ACCCartItem *> *)purchasedItems
               amount:(nullable NSNumber *)purchaseAmount;

/*!
 *  @brief Tracks every item added to a specific cart.
 *  @since 6.0.0
 *
 *  @param cartId       The cart's identifier.
 *
 *  @param currency     Currency, is denoted as, e.g. "USD", "EUR", "GBP".  See ISO-4217 for @n
 *  specific values.  One reference for these is <http://en.wikipedia.org/wiki/ISO_4217> or @c [NSLocale ISOCurrencyCodes].
 *
 *  @param cartItem    The item.
 */

+ (void)trackCart:(NSString *)cartId
         currency:(NSString *)currency
             item:(ACCCartItem *)cartItem;

/*!
 *  @brief Tracks a lead (special event).
 *  @since 6.0.0
 *
 *  @param leadId  The lead's identifier.
 *
 *  @param value   Arbitrary value of the lead.
 */

+ (void)trackLead:(NSString *)leadId
            value:(NSString *)value;

///-----------------------------------------------------------------------------
/// @name  Track Screens
///-----------------------------------------------------------------------------

/*!
 *  @brief Allows to track the display of a screen with id.
 *  @since 6.0.0
 *
 *  @details If you want to trigger some In-App notifications only on some specific 
 *  screens, you'll have to track the display and the dismiss of those screens. @n
 *  To track the display of a screen, call this method with the screen's id 
 *  as a parameter in your controller's viewDidAppear method .
 *  @code
 *    - (void)viewDidAppear:(BOOL)animated {
 *      [super viewDidAppear:animated];
 *
 *      [Accengage trackScreenDisplay:@"controller_id"];
 *    }
 *  @endcode
 *
 *  @note You can simply @c import the @c UIViewController+Accengage.h category to your
 *  controller and set the @c accengageAlias in your controller's @c viewDidLoad method. @n
 *  It will automatically track the display and the dismiss of the screen.
 *  @code
 *    #import <Accengage/Accengage.h>
 *    
 *    @implementation MyCustomController
 *
 *      - (void)viewDidLoad {
 *        [super viewDidLoad];
 *
 *        self.accengageAlias = @"controller_id";
 *      }
 *
 *    @end
 *  @endcode
 *
 *  @see trackScreenDismiss:
 *
 *  @param screenID The screen's identifier as an @c NSString
 */
+ (void)trackScreenDisplay:(NSString *)screenID;

/*!
 *  @brief Allows to track the dismiss of a screen with id.
 *  @since 6.0.0
 *
 *  @details If you want to trigger some In-App notifications only on some specific
 *  screens, you'll have to track the display and the dismiss of those screens. @n
 *  To track the dismiss of a screen, call this method with the screen's id
 *  as a parameter in your controller's viewDidDisappear method .
 *  @code
 *    - (void)viewDidDisappear:(BOOL)animated {
 *      [super viewDidDisappear:animated];
 *
 *      [Accengage trackScreenDismiss:@"controler_id"];
 *    }
 *  @endcode
 *
 *  @note You can simply @c import the @c UIViewController+Accengage.h category to your
 *  controller and set the @c accengageAlias in your controller's @c viewDidLoad method. @n
 *  It will automatically track the display and the dismiss of the screen.
 *  @code
 *    #import <Accengage/Accengage.h>
 *
 *    @implementation MyCustomController
 *
 *      - (void)viewDidLoad {
 *        [super viewDidLoad];
 *
 *        self.accengageAlias = @"controller_id";
 *      }
 *
 *    @end
 *  @endcode
 *
 *  @see trackScreenDisplay:
 *
 *  @param screenID The screen's identifier as an @c NSString
 */
+ (void)trackScreenDismiss:(NSString *)screenID;

///-----------------------------------------------------------------------------
/// @name  Web Tracking
///-----------------------------------------------------------------------------

/*!
 *  @brief Returns the Accengage script message names.
 *  @since 6.1.0
 *
 *  @details Used for the manual script injection with WKWebView component.
 *  @code
 *  WKUserContentController *contentController = [WKUserContentController new];
 *
 *  WKUserScript *script = [[WKUserScript alloc] initWithSource:[Accengage trackingScriptForWebView:ACCWKWebViewFramework]
 *                                                injectionTime:WKUserScriptInjectionTimeAtDocumentEnd
 *                                             forMainFrameOnly:YES];
 *
 *  [contentController addUserScript:script];
 *
 *  NSSet *scripts = [Accengage scriptMessagesNames];
 *  for (NSString *name in scripts) {
 *      [contentController addScriptMessageHandler:self name:name];
 *  }
 *
 *  WKWebViewConfiguration *configuration = [WKWebViewConfiguration new];
 *  configuration.userContentController = contentController;
 *
 *  WKWebView *webView = [[WKWebView alloc] initWithFrame:self.view.bounds configuration:configuration];
 *  @endcode
 *
 *  @return The Accengage script message names.
 */
+ (NSSet<NSString *> *)scriptMessagesNames;

/*!
 *  @brief Returns the Accengage tracking script.
 *  @since 6.1.0
 *
 *  @details Used for the manual script injection with WKWebView component.
 *  @code
 *  WKUserContentController *contentController = [WKUserContentController new];
 *
 *  WKUserScript *script = [[WKUserScript alloc] initWithSource:[Accengage trackingScriptForWebView:ACCWKWebViewFramework]
 *                                                injectionTime:WKUserScriptInjectionTimeAtDocumentEnd
 *                                             forMainFrameOnly:YES];
 *
 *  [contentController addUserScript:script];
 *
 *  NSSet *scripts = [Accengage scriptMessagesNames];
 *  for (NSString *name in scripts) {
 *      [contentController addScriptMessageHandler:self name:name];
 *  }
 *
 *  WKWebViewConfiguration *configuration = [WKWebViewConfiguration new];
 *  configuration.userContentController = contentController;
 *
 *  WKWebView *webView = [[WKWebView alloc] initWithFrame:self.view.bounds configuration:configuration];
 *  @endcode
 *
 *  @param component The list of the lists to which we want to be subscribed.
 *
 *  @return The Accengage tracking script.
 */
+ (nullable NSString *)trackingScriptForWebView:(ACCWebViewTrackingFramework)component;

/*!
 *  @brief Handle received script message.
 *  @since 6.1.0
 *
 *  @details Call it from
 *  @code
 *  - (void)userContentController:(WKUserContentController *)userContentController
 *        didReceiveScriptMessage:(WKScriptMessage *)message {
 *      if ([Accengage didReceiveScriptMessageWithName:message.name body:message.body]) {
 *          return;
 *      }
 *  }
 *  @endcode
 *
 *  @param name The Message's name.
 *  @param body The Message's body.
 *
 *  @return @c YES if the message was triggered by the Accengage script.
 */
+ (BOOL)didReceiveScriptMessageWithName:(NSString *)name body:(id)body;

///-----------------------------------------------------------------------------
/// @name  Lists
///-----------------------------------------------------------------------------

/*!
 *  @brief Subscribe the device to the given lists.
 *  @since 6.0.0
 *
 *  @param lists The list of the lists to which we want to be subscribed.
 */
+ (void)subscribeToLists:(NSArray<ACCList *> *)lists;

/*!
 *  @brief Unsubscribe the device from the given lists.
 *  @since 6.0.0
 *
 *  @param lists The list of the lists from which we want to be unsubscribed.
 */
+ (void)unsubscribeFromLists:(NSArray<ACCList *> *)lists;

/*!
 *  @brief Get the device's subscription status to the given lists.
 *  @since 6.0.0
 *
 *  @param lists             The list of the lists for which we want to check the subscription status.
 *  @param completionHandler The completion handler
 */
+ (void)subscriptionStatusForLists:(NSArray<ACCList *> *)lists
                 completionHandler:(void (^)(NSArray<ACCList *> * _Nullable result,
                                             NSError * _Nullable error))completionHandler;

/*!
 *  @brief Get the list of the device's subscriptions.
 *  @since 6.0.0
 *
 *  @param completionHandler The completion handler
 */
+ (void)listOfSubscriptions:(void (^)(NSArray<ACCList *> * _Nullable result,
                                      NSError * _Nullable error))completionHandler;


///-----------------------------------------------------------------------------
/// @name  Opening a URL
///-----------------------------------------------------------------------------

/*!
 *  @brief Handle incoming URL schemes.
 *  @since 6.0.0
 *
 *  @param url The URL to handle
 */
+ (BOOL)handleOpenURL:(NSURL *)url;

///-----------------------------------------------------------------------------
/// @name Helpers
///-----------------------------------------------------------------------------

/*!
 *  @brief Returns the current version of the Accengage Kit.
 *  @since 6.0.0
 *
 *  @return The current version of the Accengage Kit.
 */
+ (NSString *)version;

/*!
 *  @brief Converts @c NSDate object to normalized string for an updateDeviceInfo: use and returns it.
 *  @since 6.0.0
 *
 *  @code
 *    NSString *normalizedDate = [Accengage normalizedStringForDate:dateObject];
 *    [Accengage updateDeviceInfo:@{@"custom_date":normalizedDate}];
 *  @endcode
 *
 *  @see updateDeviceInfo:
 *
 *  @return A normalized string of specific @c NSDate.
 *
 *  @param date Arbitrary @c NSDate object to normalize.
 */
+ (NSString *)normalizedStringForDate:(NSDate *)date;

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

NS_ASSUME_NONNULL_END
