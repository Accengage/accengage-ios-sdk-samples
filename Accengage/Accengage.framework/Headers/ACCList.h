/*!
 * @file ACCList.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.0.0
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @typedef ACCListSubscriptionStatus
 *
 *  @brief Subscription status options
 *  @since 6.0.0
 */
typedef NS_ENUM(NSInteger, ACCListSubscriptionStatus) {
    /*! Unknown status */
    ACCListSubscriptionStatusUnknown,
    
    /*! Device is subscribed to the list */
    ACCListSubscriptionStatusSubscribed,
    
    /* !Device is unsubscripted from the list */
    ACCListSubscriptionStatusUnsubscribed
};

/*!
 *  @brief The @c ACCList class represents a static list.
 *  @since 6.0.0
 */
@interface ACCList : NSObject <NSCoding>

///-----------------------------------------------------------------------------
/// @name  Properties
///-----------------------------------------------------------------------------

/*!
 *  @brief The list identifier
 *  @since 6.0.0
 */
@property (nonatomic, copy) NSString *identifier;

/*!
 *  The expiration date of the subscription to the list
 *  @since 6.0.0
 */
@property (nonatomic, copy, nullable) NSDate *expirationDate;

/*!
 *  The name of the list
 *  @since 6.0.0
 */
@property (nonatomic, copy, readonly, nullable) NSString *name;

/*!
 *  The subscription status
 *  @since 6.0.0
 */
@property (nonatomic, assign, readonly) ACCListSubscriptionStatus subscriptionStatus;

///-----------------------------------------------------------------------------
/// @name  Factory Methods
///-----------------------------------------------------------------------------

/*!
 *  @brief Returns an @c ACCList object initialized with the given id.
 *  @since 6.0.0
 *
 *  @return An initialized @c ACCList object.
 *
 *  @param identifier The list id.
 */
- (instancetype)initWithId:(NSString *)identifier;

/*!
 *  @brief Returns an @c ACCList object initialized with the given id.
 *  @since 6.0.0
 *
 *  @return An initialized @c ACCList object.
 *
 *  @param identifier The list id.
 */
+ (instancetype)listWithId:(NSString *)identifier;

/*!
 *  @brief Returns an @c ACCList object initialized with the given id and the expiration date.
 *  @since 6.0.0
 *
 *  @return An initialized @c ACCList object.
 *
 *  @param identifier The list id
 *  @param date The expiration date
 */
- (instancetype)initWithId:(NSString *)identifier
            expirationDate:(nullable NSDate *)date NS_DESIGNATED_INITIALIZER;

/*!
 *  @brief Returns an @c ACCList object initialized with the given id and the expiration date.
 *  @since 6.0.0
 *
 *  @return An initialized @c ACCList object.
 *
 *  @param identifier The list id
 *  @param date The expiration date
 */
+ (instancetype)listWithId:(NSString *)identifier expirationDate:(nullable NSDate *)date;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
