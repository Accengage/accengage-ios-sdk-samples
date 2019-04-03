//
//  BMA4SBeaconsService.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  This Class is deprecated starting from version 5.5.0. Use `BMA4SLocationServices` instead.
 */
@interface BMA4SBeaconsService : NSObject

/**
 *  Enable or disable the beacons service of the SDK. By default the service 
 *  is disabled.
 *
 *  @param arg YES to enable the service, No to disable it (Default).
 *  @deprecated This method is deprecated starting from version 5.5.0
 *  @note Please use `[BMA4SLocationServices setBeaconServiceEnabled:]` instead.
 */
+ (void)setBeaconServiceEnabled:(BOOL)arg __attribute__((deprecated("This method is deprecated starting from version 5.5.0. Use [BMA4SLocationServices setBeaconServiceEnabled:] instead")));

/**
 *  Returns the current state of beacons service.
 *
 *  @return YES if the service is enabled or NO if it is not.
 *
 *  @see setBeaconServiceEnabled:
 *  @deprecated This method is deprecated starting from version 5.5.0
 *  @note Please use `[BMA4SLocationServices isBeaconServiceEnabled]` instead.
 */
+ (BOOL)isBeaconServiceEnabled __attribute__((deprecated("This method is deprecated starting from version 5.5.0. Use [BMA4SLocationServices isBeaconServiceEnabled] instead")));

/**
 *  Allow or not beacons service to ask needed authorization.
 *
 *  Beacons monitoring requires the Always Authorization access. 
 *  By default and  if needed, the SDK beacon service pushes the 
 *  location authorization.
 *
 *  You can prevent the SDK from asking for the needed authorization by setting
 *  the value to NO. If you disable the automated authorization request, 
 *  you will need to ask Always Authorization manually, otherwise beacons 
 *  service will not be activated.
 *
 *  @param arg YES to enable asking authorization by the SDK (Default), 
 *  No to disable it.
 *
 *  @see [requestAlwaysAuthorization](https://developer.apple.com/library/ios/documentation/CoreLocation/Reference/CLLocationManager_Class/#//apple_ref/occ/instm/CLLocationManager/requestAlwaysAuthorization)
 *  @deprecated This method is deprecated starting from version 5.5.0
 *  @note Please use `[BMA4SLocationServices setCanRequestLocationAccess:]` instead.
 */
+ (void)setCanRequestLocationAccess:(BOOL)arg __attribute__((deprecated("This method is deprecated starting from version 5.5.0. Use [BMA4SLocationServices setCanRequestLocationAccess:] instead")));

/**
 *  Returns YES if the SDK can ask needed authorization NO if it can't.
 *
 *  @return YES if the SDK can ask needed authorization NO if it can't.
 *
 *  @see setCanRequestLocationAccess:
 *  @deprecated This method is deprecated starting from version 5.5.0
 *  @note Please use `[BMA4SLocationServices canRequestLocationAccess]` instead.
 */
+ (BOOL)canRequestLocationAccess __attribute__((deprecated("This method is deprecated starting from version 5.5.0. Use [BMA4SLocationServices canRequestLocationAccess] instead")));

/**
 *  Returns a Boolean indicating whether the device supports beacon monitoring.
 *
 *  Beacons monitoring requires iOS 7 (or a more recent version of iOS) and at 
 *  least an iPhone 4S, iPod touch (5th generation), 
 *  iPad (3rd generation or later), or iPad mini.
 *
 *  @return YES if the device is capable of monitoring beacons or NO if it is not.
 *  @deprecated This method is deprecated starting from version 5.5.0
 *  @note Please use `[BMA4SLocationServices isBeaconMonitoringAvailible]` instead.
 */
+ (BOOL)isBeaconMonitoringAvailible __attribute__((deprecated("This method is deprecated starting from version 5.5.0. Use [BMA4SLocationServices isBeaconMonitoringAvailible] instead")));

@end
