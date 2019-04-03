/*!
 * @file ACCDeviceTag.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.3.0
 */

#import <Foundation/Foundation.h>
#import "ACCDataFormatting.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @brief The @c ACCDeviceTag class represents a device tag.
 *  @since 6.3.0
 */

@interface ACCDeviceTag : NSObject <ACCDataFormatting>

/*!
 *  @brief The identifier of the tag.
 *  @since 6.3.0
 */

@property (readonly, strong, nonatomic) NSString *identifier;

/*!
 *  @brief The category of the tag.
 *  @since 6.3.0
 */

@property (readonly, strong, nonatomic) NSString *category;

/*!
 *  @brief The data of the tag which contains all the parameters you add with the provided methods.
 *  You are limited to 5 parameters per device tag, if you try to add a new parameter, it will be ignored.
 *  @since 6.3.0
 */

@property (readonly, copy, nonatomic) NSDictionary <NSString *, id> *parameters;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 *  @brief Creates a new device tag
 *  @since 6.3.0
 *
 *  @details Call this method to create a new device tag with a category and identifier.
 *
 *  @param category The category of the device tag
 *  @param identifier The identifier of the device tag
 *
 *  @return A new ACCDeviceTag instance
 */

- (nullable instancetype)initWithCategory:(NSString *)category identifier:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
