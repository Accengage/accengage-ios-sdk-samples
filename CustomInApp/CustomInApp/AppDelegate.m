//
//  AppDelegate.m
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "AppDelegate.h"
#import <Accengage/Accengage.h>
#import "CustomizableTextInterstitial.h"
#import "UIView+Helper.h"
@interface AppDelegate () <BMA4SInAppNotificationDataSource>

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [Accengage setLoggingEnabled:YES];
    [Accengage start];
    
    [BMA4SInAppNotification setDataSource:self];
    
    return YES;
}

///--------------------------------------
#pragma mark - BMA4SInAppNotification
///--------------------------------------

- (UIView *)BMA4SViewForInAppMessage:(BMA4SInAppMessage *)message defaultView:(UIView *)view {
    
    if ([message.templateNibName isEqualToString:@"CustomizableTextInterstitial"]) {
        
        CustomizableTextInterstitial *customView = (CustomizableTextInterstitial*)([UIView ci_viewFromNib:@"CustomizableTextInterstitial"]);
        [customView setupWithMessage:message];
        return customView;
    }
    
    return view;
}

@end
