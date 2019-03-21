/*!
 * @file UIViewController+Accengage.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.0.0
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @brief An @c UIViewController category which simplify the screens tracking.
 *  @since 6.0.0
 *
 *  @details To track a screen display and dismiss, you can simply @c import the @c Accengage.h 
 *  to your controller and set the @c accengageAlias in your controller's @c viewDidLoad method. @n
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
 *  @see Accengage::trackScreenDisplay:
 *  @see Accengage::trackScreenDismiss:
 */
@interface UIViewController (Accengage)

/**
 *  @brief The Alias of the screen.
 *  @since 6.0.0
 */
@property(nonatomic, copy, nullable) NSString *accengageAlias;

@end

NS_ASSUME_NONNULL_END
