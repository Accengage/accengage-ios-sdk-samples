//
//  SampleHelpers.h
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SampleHelpers : NSObject

//------------------------------------------------------------------------------
/** @name Geofencing */
//------------------------------------------------------------------------------

+ (void)setGeofenceServiceEnabled:(BOOL)arg;

+ (BOOL)isGeofenceServiceEnabled;

//------------------------------------------------------------------------------
/** @name Beacons */
//------------------------------------------------------------------------------

+ (void)setBeaconServiceEnabled:(BOOL)arg;

+ (BOOL)isBeaconServiceEnabled;


@end
