/*!
 * @file ACCNotificationServiceExtension.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version   1.0.0
 */

#import <UserNotifications/UserNotifications.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @brief Accengage notification service extension for downloading and attaching media.
 *
 *  @author 2010 - present Accengage, Inc. All rights reserved.
 *  @version 1.0.0
 */
@interface ACCNotificationServiceExtension : UNNotificationServiceExtension

/*!
 *  @brief Returns the best attempt content.
 *  @since 1.0.0
 */
@property (nonatomic, readonly, nullable) UNNotificationContent *accBestAttemptContent;

@end

NS_ASSUME_NONNULL_END
