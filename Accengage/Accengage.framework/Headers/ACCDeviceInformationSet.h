/*!
 * @file ACCDeviceInformationSet.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.3.0
 */

#import <Foundation/Foundation.h>
#import "ACCDataFormatting.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @brief The @c ACCDeviceInformationSet represents a set of information related to the user's device.
 *  @since 6.3.0
 *
 *  @details The @c ACCDeviceInformationSet object provides an interface for updating the user data and update it on Accengage servers.
 *  You can set a value of different types (string, number, date), delete (reset the value), increment and decrement numbers.
 *  You update the information with the method @m updateDeviceInformation: of the @c ACCUserProfile class.
 *  @see ACCUserProfile
 */

@interface ACCDeviceInformationSet : NSObject <ACCDataFormatting>

/*!
 *  @brief Deletes (resets) the value for the given key
 *  @since 6.3.0
 *
 *  @param key The key of the value to reset
 */

- (void)deleteValueForKey:(NSString *)key;

/*!
 *  @brief Increments the value for the given key
 *  @since 6.3.0
 *
 *  @param incrementValue The value to add
 *  @param key The key of the value to increment
 */

- (void)incrementValueBy:(NSNumber *)incrementValue forKey:(NSString *)key;

/*!
 *  @brief Decrements the value for the given key
 *  @since 6.3.0
 *
 *  @param decrementValue The value to substract
 *  @param key The key of the value to decrement
 */

- (void)decrementValueBy:(NSNumber *)decrementValue forKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
