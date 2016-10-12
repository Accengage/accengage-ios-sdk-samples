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

@property (nonatomic, strong) CLLocationManager *locationManager;

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    ACCConfiguration *config = [ACCConfiguration defaultConfig];
    
    [Accengage startWithConfig:config];
    
    // Enable logs
    [Accengage setLoggingEnabled:YES];
    
    // Set Accengage push delegate
    [Accengage push].delegate = self;
    
    // Register for notifications
    [[Accengage push] registerForUserNotificationsWithOptions:ACCNotificationOptionAlert|ACCNotificationOptionBadge|ACCNotificationOptionSound|ACCNotificationOptionCarPlay];
    
    // Enable Geofence service if needed
    [BMA4SLocationServices setGeofenceServiceEnabled:[SampleHelpers isGeofenceServiceEnabled]];
    
    // Enable Beacon service if needed
    [BMA4SLocationServices setBeaconServiceEnabled:[SampleHelpers isBeaconServiceEnabled]];
    
    //init géoloc
    self.locationManager = [[CLLocationManager alloc] init];
    self.locationManager.delegate = self;
    self.locationManager.distanceFilter = kCLDistanceFilterNone;
    self.locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    [self.locationManager requestAlwaysAuthorization];
    [self.locationManager startUpdatingLocation];
    
    return YES;
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    [self.locationManager stopUpdatingLocation];
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    [self.locationManager startUpdatingLocation];
}


- (void)applicationWillTerminate:(UIApplication *)application {
    [self.locationManager stopUpdatingLocation];
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
