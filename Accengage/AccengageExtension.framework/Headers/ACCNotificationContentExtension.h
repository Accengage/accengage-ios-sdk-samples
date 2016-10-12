/*!
 * @file ACCNotificationContentExtension.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version   1.0.0
 */

#import <Foundation/Foundation.h>
#import <UserNotifications/UserNotifications.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @brief Accengage notification content extension helpers.
 *
 *  @author 2010 - present Accengage, Inc. All rights reserved.
 *  @version 1.0.0
 */
@interface ACCNotificationContentExtension : NSObject

/*!
 *  @brief Check if we need to delay dismiss of a notification as defined in the message button options in Accengage BO.
 *  @since 1.0.0
 *
 *  @param response The response of the notification.
 *
 *  @discussion Call it from
 *  @code
 *  - (void)didReceiveNotificationResponse:(UNNotificationResponse *)response
 *                       completionHandler:(void (^)(UNNotificationContentExtensionResponseOption))completion {
 *
 *      if (![ACCNotificationContentExtension shouldDelayDismissForNotificationResponse:response]) {
 *          completion(UNNotificationContentExtensionResponseOptionDismissAndForwardAction);
 *      }
 *      else {
 *          // do something
 *
 *          // Then close
 *          completion(UNNotificationContentExtensionResponseOptionDismissAndForwardAction);
 *      }
 *  }
 *  @endcode
 *
 *  @return @c YES if you check the @c Delay @c push @c dismiss in the action options.
 *
 *  @warning If you need to handle the notification actions in your @c UNNotificationContentExtension,
 *  @b you should always @b forward @b the action to application after the dismiss by using
 *  @c UNNotificationContentExtensionResponseOptionDismissAndForwardAction.
 */
+ (BOOL)shouldDelayDismissForNotificationResponse:(UNNotificationResponse *)response;

/*!
 *  @brief Retrieve the custom parameters associated with the notification.
 *  @since 1.0.0
 *
 *  @param notification The notification that arrived.
 *
 *  @return A dictionary of the custom parameters associated with the notification.
 *
 *  @note The @c notification parameter can be kind of @c Class @c UNNotification or @c UNNotificationResponse.
 */
+ (nullable NSDictionary *)customParamsForNotification:(id)notification;

/*!
 *  @brief Retrieve the custom parameters associated with a custom action from a response.
 *  @since 1.0.0
 *
 *  @param identifier The identifier for the custom action.
 *  @param response The response of the notification.
 *
 *  @return A dictionary of the custom parameters associated with a custom action from notification.
 */
+ (nullable NSDictionary *)actionCustomParams:(NSString *)identifier forNotificationResponse:(UNNotificationResponse *)response;

@end



NS_ASSUME_NONNULL_END
