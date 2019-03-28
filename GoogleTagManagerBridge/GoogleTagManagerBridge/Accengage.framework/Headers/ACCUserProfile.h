/*!
 * @file ACCUserProfile.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.3.0
 */

#import <Foundation/Foundation.h>

@class ACCDeviceTag, ACCDeviceInformationSet;

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @brief Provides an interface to change informations relative to a user.
 *
 *  @author 2010 - present Accengage, Inc. All rights reserved.
 *  @version 6.3.0
 */

@interface ACCUserProfile : NSObject

///-----------------------------------------------------------------------------
/// @name Device tag
///-----------------------------------------------------------------------------

/*!
 *  @brief Set a device tag
 *  @since 6.3.0
 *
 *  @param tag The tag to set
 */

- (void)setDeviceTag:(ACCDeviceTag *)tag;

/*!
 *  @brief Delete a device tag
 *  @since 6.3.0
 *
 *  @param tag The tag to delete
 */

- (void)deleteDeviceTag:(ACCDeviceTag *)tag;

///-----------------------------------------------------------------------------
/// @name Update device informations
///-----------------------------------------------------------------------------

/*!
 *  @brief Update device informations
 *  @since 6.3.0
 *
 *  @param deviceInformation A @c ACCDeviceInformationSet object containing all informations to update
 *
 *  @see ACCDeviceInformationSet
 */

- (void)updateDeviceInformation:(ACCDeviceInformationSet *)deviceInformation withCompletionHandler:(nullable void(^)(NSError *__nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
