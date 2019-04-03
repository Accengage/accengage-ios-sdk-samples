/*!
 * @file ACCWKWebView.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 * @version    6.1.0
 */

#import <WebKit/WebKit.h>

/*!
 *  @brief Use WKWebView for web tracking with WebKit.
 *
 *  Please, contact Accengage to get more info in order to finish tracked webview integration.
 *
 *  @author 2010 - present Accengage, Inc. All rights reserved.
 *  @version 6.1.0
 */
@interface ACCWKWebView : WKWebView
@end

/*!
 *  @brief The Accengage WebKit message handler.
 *
 *  @author 2010 - present Accengage, Inc. All rights reserved.
 *  @version 6.1.0
 */
@interface ACCWKScriptMessageHandler : NSObject<WKScriptMessageHandler>
@end
