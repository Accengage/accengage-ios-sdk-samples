//
//  SampleHelpers.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "SampleHelpers.h"

@implementation SampleHelpers

#pragma mark - Geofencing

+ (void)setGeofenceServiceEnabled:(BOOL)arg{
    [BMA4SLocationServices setGeofenceServiceEnabled:arg];
    [[NSUserDefaults standardUserDefaults] setObject:@(arg)
                                              forKey:kSampleGeofencingServiceKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

+ (BOOL)isGeofenceServiceEnabled {
    NSNumber *status = [[NSUserDefaults standardUserDefaults] objectForKey:kSampleGeofencingServiceKey];
    return status ? status.boolValue : YES;
}

#pragma mark - Beacons

+ (void)setBeaconServiceEnabled:(BOOL)arg {
    [BMA4SLocationServices setBeaconServiceEnabled:arg];
    [[NSUserDefaults standardUserDefaults] setObject:@(arg)
                                              forKey:kSampleBeaconsServiceKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
}


+ (BOOL)isBeaconServiceEnabled {
    NSNumber *status = [[NSUserDefaults standardUserDefaults] objectForKey:kSampleBeaconsServiceKey];
    return status ? status.boolValue : YES;
}

@end
