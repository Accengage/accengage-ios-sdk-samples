//
//  BMA4SInAppNotificationDataSource.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

/**
 *  Options for overlay inApp position.
 *  @since Available in SDK 5.2.0 and later.
 */
typedef NS_ENUM(NSInteger, BMA4SOverlayInAppPosition){
  /**
   Default position
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleBottomMargin 
   | UIViewAutoresizingFlexibleRightMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionDefault = 0,
  
  /**
   Top.
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleBottomMargin
   | UIViewAutoresizingFlexibleRightMargin 
   | UIViewAutoresizingFlexibleLeftMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionTop = 1,
  
  /**
   Top left corner.
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleBottomMargin 
   | UIViewAutoresizingFlexibleRightMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionTopLeft = 2,
  
  /**
   Top right corner.
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleBottomMargin 
   | UIViewAutoresizingFlexibleLeftMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionTopRight = 3,
  
  /**
   Centred.
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleBottomMargin
   | UIViewAutoresizingFlexibleTopMargin 
   | UIViewAutoresizingFlexibleRightMargin 
   | UIViewAutoresizingFlexibleLeftMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionCenter = 4,
  
  /**
   Left.
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleBottomMargin 
   | UIViewAutoresizingFlexibleTopMargin 
   | UIViewAutoresizingFlexibleRightMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionCenterLeft = 5,
  
  /**
   Right.
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleBottomMargin 
   | UIViewAutoresizingFlexibleTopMargin 
   | UIViewAutoresizingFlexibleLeftMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionCenterRight = 6,
  
  /**
   Bottom
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleTopMargin 
   | UIViewAutoresizingFlexibleRightMargin 
   | UIViewAutoresizingFlexibleLeftMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionBottom = 7,
  
  /**
   Bottom left corner.
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleTopMargin 
   | UIViewAutoresizingFlexibleRightMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionBottomLeft = 8,
  
  /**
   Bottom right corner.

   AutoresizingMask : 
   UIViewAutoresizingFlexibleTopMargin 
   | UIViewAutoresizingFlexibleLeftMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionBottomRight = 9,
  
  /**
   Custom position returned by BMA4SOverlayInAppCustomPositionForTemplate:size:
   
   AutoresizingMask : 
   UIViewAutoresizingFlexibleBottomMargin 
   | UIViewAutoresizingFlexibleRightMargin
   
   @since Available in SDK 5.2.0 and later.
   */
  BMA4SOverlayInAppPositionCustom = 10
};

/**
 The data source of an inApp notifications position object must adopt the 
 BMA4SInAppNotificationDataSource protocol. Optional methods of the protocol 
 allow the data source to choose the default position, some predefined positions
 or a custom position of an inApp.
 
 @since Available in SDK 5.2.0 and later.
 */
@class BMA4SInAppMessage;
@protocol BMA4SInAppNotificationDataSource <NSObject>
@optional

//------------------------------------------------------------------------------
/** @name Configuring the InApp View */
//------------------------------------------------------------------------------

/**
 Ask the data source for the view of an inapp.
 
 By Default the SDK loads the view from the NIB file.
 You can custom the loaded view programmatically.
 You **must not modify the subviews references and tags**.
 
     - (UIView *)BMA4SViewForInAppMessage:(BMA4SInAppMessage *)message
                              defaultView:(UIView *)view {
 
       NSString * radiusString = message.displayCustomParams[@"radius"];
       if (radiusString) {
         view.layer.cornerRadius = radiusString.floatValue;
       }
 
       return view;
     }


 You can also create the inApp view programmatically. **To do this you need to
 respect the following requirements.**
 
 First of all, there are two types of inApp messages :
 ***TextMessage*** & ***WebMessage***. You can check the type by this way :
 
     - (UIView *)BMA4SViewForInAppMessage:(BMA4SInAppMessage *)message
                              defaultView:(UIView *)view {

       if ([message isKindOfClass:[BMA4SInAppTextMessage class]]) {
         // Some code ...
       }
       else if ([message isKindOfClass:[BMA4SInAppWebMessage class]]) {
         // Some code ...
       }
     }

Here is the list of the required/optional subviews of each message type :

 <table>
 <tr>
 <th></th>
 <th>Required subviews</th>
 <th>Optional subviews</th>
 </tr>
 <tr>
 <td>BMA4SInAppTextMessage</td>
 <td>__Text label__ : <b>UILabel</b> with tag <i>BMA4SInAppOverlayViewBodyTag</i></td>
 <td>__Close button__ : <b>UIButton</b> with tag <i>BMA4SInAppOverlayViewCloseTag</i> </td>
 </tr>
 <tr>
 <td rowspan="8">BMA4SInAppWebMessage</td>
 <td rowspan="8">__Web view__ : <b>UIWebView</b> with tag <i>BMA4SInAppOverlayViewBodyTag</i></td>
 <td>__Close button__ : <b>UIButton</b> with tag <i>BMA4SInAppOverlayViewCloseTag</i></td>
 </tr>
 <tr>
 <td>__Go Back Button__ : <b>UIButton</b> with tag <i>BMA4SInAppOverlayViewBackTag</i></td>
 </tr>
 <tr>
 <td>__Go Forward Button__ : <b>UIButton</b> with tag <i>BMA4SInAppOverlayViewForwardTag</i></td>
 </tr>
 <tr>
 <td>__Reload Button__ : <b>UIButton</b> with tag <i>BMA4SInAppOverlayViewReloadTag</i></td>
 </tr>
 <tr>
 <td>__Stop loading Button__ : <b>UIButton</b> with tag <i>BMA4SInAppOverlayViewStopTag</i></td>
 </tr>
 <tr>
 <td>__Open in Safari Button__ : <b>UIButton</b> with tag <i>BMA4SInAppOverlayViewSafariTag</i></td>
 </tr>
 <tr>
 <td>__Loader__ : <b>UIActivityIndicatorView</b> with tag <i>BMA4SInAppOverlayViewActivityTag</i></td>
 </tr>
 <tr>
 <td>__Toolbar__ : <b>UIToolbar</b> with tag <i>BMA4SInAppOverlayViewToolbarTag</i></td>
 </tr>
 </table>

 
 ###Example :###
 
      - (UIView *)BMA4SViewForInAppMessage:(BMA4SInAppMessage *)message
                               defaultView:(UIView *)view {
        if ([message isKindOfClass:[BMA4SInAppTextMessage class]]) {
          BMA4SInAppView *customView = [[BMA4SInAppView alloc] initWithFrame:CGRectInset(view.frame, 20, 0)];
          customView.layer.masksToBounds = YES;
          customView.layer.cornerRadius = 5.;
          customView.backgroundColor = [UIColor colorWithWhite:0 alpha:0.7];
          customView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
 
          // Set auto sizing desabled
          customView.autosizingDisabled = YES;
 
          UILabel *label = [[UILabel alloc] initWithFrame:CGRectInset(customView.bounds, 10, 10)];
          label.backgroundColor = [UIColor clearColor];
          label.textColor = [UIColor whiteColor];
          label.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
          label.tag = BMA4SInAppOverlayViewBodyTag;
          label.text = [(BMA4SInAppTextMessage*)message body];
          label.numberOfLines = 0;
 
          UIButton *close = [UIButton buttonWithType:UIButtonTypeCustom];
          close.frame = customView.bounds;
          close.tag = BMA4SInAppOverlayViewCloseTag;
 
          [customView addSubview:label];
          [customView addSubview:close];
          return customView;
        }
 
      return view;
    }

 @param message The object containing the inapp informations
 @param view    The default loaded view

 @return An object inheriting from BMA4SInAppView or UIView that can be used
 as an inApp View.
 
 @since Available in SDK 5.3.0 and later.
 */

- (UIView*)BMA4SViewForInAppMessage:(BMA4SInAppMessage*)message
                        defaultView:(UIView*)view;

//------------------------------------------------------------------------------
/** @name Managing the InApp dipslay */
//------------------------------------------------------------------------------

/**
 *  Send before SDK begins displaying an inApp.
 *
 *  @param message The object containing the inapp informations
 *
 *  @return YES if the SDK can begin displaying content; otherwise, NO.
 *
 *  @since Available in SDK 5.3.0 and later.
 */
- (BOOL)BMA4SCanDisplayInAppMessage:(BMA4SInAppMessage*)message;


/**
 *  Allow to enable/desable default displaying animation.
 *
 *  @param message The object containing the inapp informations
 *
 *  @return YES if the SDK can apply the default animation; otherwise, NO.
 *
 *  @since Available in SDK 5.3.0 and later.
 */
- (BOOL)BMA4SEnableDefaultDisplayAnimationForInAppMessage:(BMA4SInAppMessage*)message;

/**
 Notifies the application that the in-app view is about to be added to the view hierarchy
 

 @param message The object containing inapp information
 @param view    The inapp view
 @since Available in SDK 5.3.0 and later.
 */
- (void)BMA4SWillDisplayInAppMessage:(BMA4SInAppMessage*)message
                                view:(UIView*)view;

/**
   Notifies the application that the in-app view was added to the view hierarchy

   You can use this method to apply a custom animation to the in-app view.

    Example:
 
    - (void)BMA4SDidDisplayInAppMessage:(BMA4SInAppMessage *)message
                                   view:(UIView *)view {
 
        // Save the inApp final frame
        CGRect frame = view.frame;
 
        // Change the frame
        view.frame = CGRectMake(0, -frame.size.height, frame.size.width, frame.size.height);
 
        // Apply your animation
        [UIView animateWithDuration:0.3
                         animations:^{
            view.frame = frame;
        }];
    }

   @param message The object containing in-app information. You can use it to differentiate between different in-app message types
   @param view    The in-app view.
   @since Available in SDK 5.3.0 and later.
*/
- (void)BMA4SDidDisplayInAppMessage:(BMA4SInAppMessage*)message
                               view:(UIView*)view;


/**
 Tells that a specified inApp is about to be dismissed.
 
 This method can be used to apply a custom dismissing animation to an inApp.
 Your implementation of this method should execute the completion block in the
 completionHandler of your animation or in the end of your treatment.

     - (void)BMA4SWillDismissInAppMessage:(BMA4SInAppMessage *)message
                                     view:(UIView *)view
                        completionHandler:(void (^)())completionHandler {
 
        [UIView animateWithDuration:0.3
                         animations:^{
          CGRect frame = view.frame;
          view.frame.origin.y = -frame.size.height;
          view.frame = frame;
        } completion:^(BOOL finished) {
          // Call the completionHandler
          if (completionHandler) {
            completionHandler();
          }
        }];
    }
 
 @param message The object containing the inapp informations
 @param view    The inapp view
 @param completionHandler A block to call when you are finished performing the animation.
 @since Available in SDK 5.3.0 and later.
 */
- (void)BMA4SWillDismissInAppMessage:(BMA4SInAppMessage*)message
                                view:(UIView*)view
                   completionHandler:(void (^)())completionHandler;

/**
 *  Tells that the specified inapp is now dismissed.
 *
 *  @param message The object containing the inapp informations
 *  @param view    The inapp view
 *  @since Available in SDK 5.3.0 and later.
 */
- (void)BMA4SDidDismissInAppMessage:(BMA4SInAppMessage*)message
                               view:(UIView*)view;


//------------------------------------------------------------------------------
/** @name The Overlay InApp position */
//------------------------------------------------------------------------------

/**
 *  Asks the data source the position of an inApp.
 *
 *
 *  @param message inApp message.
 *  @param templateSize inApp size.
 *
 *  @return position option.
 *  @see BMA4SOverlayInAppPosition
 *  @since Available in SDK 5.3.0 and later.
 */
- (BMA4SOverlayInAppPosition)BMA4SOverlayInAppMessagePosition:(BMA4SInAppMessage*)message
                                                         size:(CGSize)templateSize;


/**
 *  Asks the data source the custom origin point of an inApp 
 *  if BMA4SOverlayInAppMessagePosition:size: returned 
 *  BMA4SOverlayInAppPositionCustom.
 *
 *  @param message inApp message.
 *  @param templateSize inApp size.
 *
 *  @return A point that specifies the coordinates of the in-app view's origin 
 *  is the `window` view.
 *
 *  @since Available in SDK 5.3.0 and later.
 */

- (CGPoint)BMA4SOverlayInAppMessageCustomPosition:(BMA4SInAppMessage*)message
                                             size:(CGSize)templateSize;

//------------------------------------------------------------------------------
/** @name Deprecated */
//------------------------------------------------------------------------------

/**
 *  Asks the data source the position of an inApp.
 *
 *
 *  @param templateName inApp template name without extension (.XIB).
 *  @param templateSize inApp size.
 *
 *  @return position option. 
 *
 *  @see BMA4SOverlayInAppPosition
 *
 *  @deprecated in SDK 5.3.0
 *
 *  @since Available in SDK 5.2.0, deprecated in SDK 5.3.0.
 *
 *  @see BMA4SOverlayInAppMessagePosition:size:
 */
- (BMA4SOverlayInAppPosition)BMA4SOverlayInAppPositionForTemplate:(NSString *)templateName
                                                             size:(CGSize)templateSize __attribute__((deprecated("This method is deprecated starting from version 5.3.0.")));


/**
 *  Asks the data source the custom origin point of an inApp 
 *  if BMA4SOverlayInAppPositionForTemplate:size: returned 
 *  BMA4SOverlayInAppPositionCustom.
 *
 *  @param templateName inApp template name without extension (.XIB).
 *  @param templateSize inApp size.
 *
 *  @return A point that specifies the coordinates of the in-app view's origin 
 *  is the `window` view.
 *
 *  @deprecated in SDK 5.3.0
 *
 *  @since Available in SDK 5.2.0, deprecated in SDK 5.3.0.
 *
 *  @see BMA4SOverlayInAppMessageCustomPosition:size:
 */
- (CGPoint)BMA4SOverlayInAppCustomPositionForTemplate:(NSString *)templateName
                                                 size:(CGSize)templateSize __attribute__((deprecated("This method is deprecated starting from version 5.3.0.")));

@end
