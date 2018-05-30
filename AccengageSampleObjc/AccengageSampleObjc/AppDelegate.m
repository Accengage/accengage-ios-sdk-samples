//
//  AppDelegate.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "AppDelegate.h"
#import "MainViewController.h"
#import <CoreLocation/CoreLocation.h>

@interface AppDelegate () <CLLocationManagerDelegate, ACCPushDelegate>

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    ACCConfiguration *config = [ACCConfiguration defaultConfig];
    [Accengage startWithConfig:config optIn:ACCOptInEnabled];
    
    // Set Accengage push delegate
    [Accengage push].delegate = self;
    
    NSNumber *optin = [[NSUserDefaults standardUserDefaults] objectForKey:@"optin"];
    
    if (!optin) {
        
        // Creating the popup optin data
        UIAlertController *popupDataOptin = [UIAlertController alertControllerWithTitle:[NSString stringWithFormat:NSLocalizedString(@"TITLE_DATA_COLLECTION_POPUP", nil),    [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleNameKey]]
                                                                                message:NSLocalizedString(@"MESSAGE_DATA_COLLECTION_POPUP", nil)
                                                                         preferredStyle:UIAlertControllerStyleAlert];
        
        
        // Creating the button to refuse the data collection
        UIAlertAction *refuseDataOptinAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"DECLINE_DATA_COLLECTION_POPUP", nil) style:UIAlertActionStyleDefault
                                                                      handler:^(UIAlertAction *action) {
                                                                          
                                                                          // In the case where the user accept the data collection : persist the var "optin" in standardUserDefaults with value "NO" and set the associated variables to its appropriate values.
                                                                          [[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"optin"];
                                                                          [Accengage setGeolocOptInEnabled:NO];
                                                                          [Accengage setDataOptInEnabled:NO];
                                                                          [SampleHelpers setBeaconServiceEnabled:NO];
                                                                          [SampleHelpers setGeofenceServiceEnabled:NO];
                                                                      }];
        
        // Creating the button to accept the data collection
        UIAlertAction *acceptDataOptinAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"ACCEPT_DATA_COLLECTION_POPUP", nil) style:UIAlertActionStyleDefault
                                                                      handler:^(UIAlertAction *action) {
                                                                          
//                                                                          In the case where the user accept the data collection : persist the var "optin" in standardUserDefaults with value "YES" and set the associated variables to its appropriate values.
//                                                                          Also displaying the iOS Push Notification popup and Gelolocation popup.
                                                                
                                                                          [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"optin"];
                                                                          [Accengage setDataOptInEnabled:YES];
                                                                          [Accengage setGeolocOptInEnabled:YES];
                                                                          [Accengage setLoggingEnabled:YES];
                                                                          
                                                                          [[Accengage push] registerForUserNotificationsWithOptions:ACCNotificationOptionAlert|ACCNotificationOptionBadge|ACCNotificationOptionSound];
                                                                          
                                                                          [SampleHelpers setBeaconServiceEnabled:YES];
                                                                          [SampleHelpers setGeofenceServiceEnabled:YES];
                                                                          
                                                                          [BMA4SInAppNotification setDataSource:self];
                                                                          
                                                                      }];
        
        // Adding the buttons accept/decline data collection to the popup
        [popupDataOptin addAction:refuseDataOptinAction];
        [popupDataOptin addAction:acceptDataOptinAction];
        [popupDataOptin setPreferredAction:acceptDataOptinAction];
        
        // Display asynchronously the popup optin data
        dispatch_async(dispatch_get_main_queue(), ^{
            [[[[UIApplication sharedApplication] keyWindow] rootViewController] presentViewController:popupDataOptin animated:YES completion:nil];
        });
    } else {
        
        // Case where the user has already answered to the popup optin data
        
        if (optin.intValue == 1) {
            [Accengage setDataOptInEnabled:YES];
            [Accengage setGeolocOptInEnabled:YES];
        } else {
            [Accengage setDataOptInEnabled:NO];
            [Accengage setGeolocOptInEnabled:NO];
        }
    }
    
    return YES;
}

///--------------------------------------
#pragma mark - Handle incoming URLS
///--------------------------------------

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    [self handleURL:url];
    return YES;
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
    [self handleURL:url];
    return YES;
}

///--------------------------------------
#pragma mark - Accengage push delegate
///--------------------------------------

- (void)didOpenNotificationWithId:(NSString *)notifId
                       parameters:(NSDictionary *)params{
    [self handlePush:params];
}

///--------------------------------------
#pragma mark - Location manager delegate
///--------------------------------------

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations{
    // do not update with old location
    CLLocation *newLocation = locations.lastObject;
    NSTimeInterval locationAge = -(newLocation.timestamp).timeIntervalSinceNow;
    
    if (locationAge > 5.0)
        return;
    
    // test that the horizontal accuracy does not indicate an invalid measurement
    if (newLocation.horizontalAccuracy < 0)
        return;
    
    // update location on A4S server
    [BMA4SLocationServices updateLocation:newLocation];
}

#pragma mark - Private

- (void)handlePush:(NSDictionary *)infos{
    if (!infos) return ;
    
    if (infos[@"p"]) {
        [self goToScreen:infos[@"p"]];
    }
}

- (void)handleURL:(NSURL *)url{
    
    if (!url) return ;
    
    if ([url.host isEqualToString:@"p"]) {
        NSArray* array = url.pathComponents;
        
        if (array.count == 2 )
            [self goToScreen:array[1]];
    }
}

- (void)goToScreen:(NSString *)name{
    
    UITabBarController *tabBarController = (UITabBarController*)self.window.rootViewController;
    
    if ([name isEqualToString:@"2"]) {
        tabBarController.selectedIndex = 1;
    }
    else {
        tabBarController.selectedIndex = 0;
        
        UINavigationController *nav = tabBarController.viewControllers[0];
        MainViewController *controller = nav.viewControllers[0];
        
        if ([name isEqualToString:@"1"]) {
            [controller performSegueWithIdentifier:@"goToSettings" sender:controller];
        }
        else if ([name isEqualToString:@"3"]) {
            [controller performSegueWithIdentifier:@"goToProductsList" sender:controller];
        }
    }
}

@end
