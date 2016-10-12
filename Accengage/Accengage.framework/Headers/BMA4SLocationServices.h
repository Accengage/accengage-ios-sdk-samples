//
//  BMA4SLocationServices.h
//  Accengage SDK |version|
//
//  Copyright (c) 2010-2015 Accengage. All rights reserved.
//

@class CLLocation;

@interface BMA4SLocationServices : NSObject

/**
 *  Allow or not location services to ask needed authorization.
 *
 *  Beacons and geofence monitoring requires the Always Authorization access.
 *  By default and  if needed, the SDK pushes the location authorization.
 *
 *  You can prevent the SDK from asking for the needed authorization by setting
 *  the value to NO. If you disable the automated authorization request,
 *  you will need to ask Always Authorization manually, otherwise beacons/geofence
 *  service will not be activated.
 *
 *  @param arg YES to enable asking authorization by the SDK (Default),
 *  No to disable it.
 *
 *  @see [requestAlwaysAuthorization](https://developer.apple.com/library/ios/documentation/CoreLocation/Reference/CLLocationManager_Class/#//apple_ref/occ/instm/CLLocationManager/requestAlwaysAuthorization)
 */
+ (void)setCanRequestLocationAccess:(BOOL)arg;


/**
 *  Returns YES if the SDK can ask needed authorization NO if it can't.
 *
 *  @return YES if the SDK can ask needed authorization NO if it can't.
 *
 *  @see setCanRequestLocationAccess:
 */
+ (BOOL)canRequestLocationAccess;


//------------------------------------------------------------------------------
/** @name Geolocation */
//------------------------------------------------------------------------------

/**
 *  If your application uses geolocation (GPS), you can use the user's location to target your message based on location criteria.
 *
 * To update the location on our server you can call this instance method.
 *  @param location `CLLocation` object which represents the location of the user
 */
+ (void)updateLocation:(CLLocation*)location;


//------------------------------------------------------------------------------
/** @name Geofencing */
//------------------------------------------------------------------------------

/**
 *  Enable or disable the geofence service of the SDK. By default the service
 *  is disabled.
 *
 *  @param arg YES to enable the service, No to disable it (Default).
 */
+ (void)setGeofenceServiceEnabled:(BOOL)arg;

/**
 *  Returns the current state of geofence service.
 *
 *  @return YES if the service is enabled or NO if it is not.
 *
 *  @see setGeofenceServiceEnabled:
 */
+ (BOOL)isGeofenceServiceEnabled;


//------------------------------------------------------------------------------
/** @name Beacons */
//------------------------------------------------------------------------------

/**
 *  Enable or disable the beacons service of the SDK. By default the service
 *  is disabled.
 *
 *  @param arg YES to enable the service, No to disable it (Default).
 */
+ (void)setBeaconServiceEnabled:(BOOL)arg;

/**
 *  Returns the current state of beacons service.
 *
 *  @return YES if the service is enabled or NO if it is not.
 *
 *  @see setBeaconServiceEnabled:
 */
+ (BOOL)isBeaconServiceEnabled;

/**
 *  Returns a Boolean indicating whether the device supports beacon monitoring.
 *
 *  Beacons monitoring requires iOS 7 (or a more recent version of iOS) and at
 *  least an iPhone 4S, iPod touch (5th generation),
 *  iPad (3rd generation or later), or iPad mini.
 *
 *  @return YES if the device is capable of monitoring beacons or NO if it is not.
 */
+ (BOOL)isBeaconMonitoringAvailible;

@end
