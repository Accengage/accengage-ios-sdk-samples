/*!
 * @file ACCDataFormatting.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.3.0
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ACCDataFormatting <NSObject>

/*!
 *  @brief Set a string parameter to the data
 *  @since 6.3.0
 *
 *  @param string The string parameter
 *  @param key The key of your string parameter
 */

- (void)setString:(NSString *)string forKey:(NSString *)key;

/*!
 *  @brief Set a number parameter to the data
 *  @since 6.3.0
 *
 *  @param number The number parameter
 *  @param key The key of your number parameter
 */

- (void)setNumber:(NSNumber *)number forKey:(NSString *)key;

/*!
 *  @brief Set a boolean parameter to the data
 *  @since 6.3.0
 *
 *  @param boolean The boolean parameter
 *  @param key The key of your boolean parameter
 */

- (void)setBoolean:(BOOL)boolean forKey:(NSString *)key;

/*!
 *  @brief Set a date parameter to the data
 *  @since 6.3.0
 *
 *  @param date The date parameter
 *  @param key The key of your date parameter
 */

- (void)setDate:(NSDate *)date forKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
