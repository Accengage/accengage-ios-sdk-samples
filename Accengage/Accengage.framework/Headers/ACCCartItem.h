/*!
 * @file ACCCartItem.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.0.0
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @brief The @c ACCCartItem class represents a purchase or a cart item.
 *  @since 6.0.0
 */
@interface ACCCartItem : NSObject

///-----------------------------------------------------------------------------
/// @name  Properties
///-----------------------------------------------------------------------------

/*!
 *  @brief The product identifier.
 *  @since 6.0.0
 */
@property (nonatomic, copy) NSString *identifier;

/*!
 *  @brief The name of the product.
 *  @since 6.0.0
 */
@property (nonatomic, copy, nullable) NSString *name;

/*!
 *  @brief The brand of the product.
 *  @since 6.0.0
 */
@property (nonatomic, copy, nullable) NSString *brand;

/*!
 *  @brief The category of the product.
 *  @since 6.0.0
 */
@property (nonatomic, copy, nullable) NSString *category;

/*!
 *  @brief The price of the product.
 *  @since 6.0.0
 */
@property (nonatomic, assign) double price;

/*!
 *  @brief The quantity of the product.
 *  @since 6.0.0
 */
@property (nonatomic, assign) NSInteger quantity;

///-----------------------------------------------------------------------------
/// @name  Factory Methods
///-----------------------------------------------------------------------------

/*!
 *  @brief Constructs and returns a cart item.
 *  @since 6.0.0
 *
 *  @return A cart item.
 *
 *  @param itemId The product id
 *  @param itemName The name of the product
 *  @param itemBrand The brand of the product
 *  @param itemCategory The category of the product
 *  @param price The price of the product
 *  @param quantity The quantity of the product
 */
+ (instancetype)itemWithId:(NSString *)itemId
                      name:(nullable NSString *)itemName
                     brand:(nullable NSString *)itemBrand
                  category:(nullable NSString *)itemCategory
                     price:(double)price
                  quantity:(NSInteger)quantity;
@end

NS_ASSUME_NONNULL_END
